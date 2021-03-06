#include "GameController.h"
#include "CluedoObjectLoader.h"
#include "../Message/MessageHandler.h"
#include "../Message/MessageIds.h"
#include "../Model/PlayerSet.h"
#include "../Utils/Utils.h"
#include <sstream>

GameController& GameController::getInstance()
{
    static GameController instance;
    return instance;
}

GameController::GameController()
{
    srand(time(NULL));
}

GameController::~GameController()
{
    for (Player* player : m_players)
    {
        delete player;
    }
}

void GameController::reset()
{
    m_players.clear();
}

void GameController::startGame()
{
    emit playersList_updated();

    m_gameRunner = std::make_shared<GameRunner>(m_players);
    m_gameRunner->registerShowObjectCallback([this](int p_murderNumber, int p_weaponNumber, int p_roomNumber) { showObjectCallback(p_murderNumber, p_weaponNumber, p_roomNumber); });
    m_gameRunner->registerObjectShownCallback([this]() {objectShownCallback(); });
    m_gameRunner->registerNoObjectCanBeShownCallback([this]() {noObjectCanBeShownCallback(); });
    m_gameRunner->registerAskPlayerResponseInformNotInvolvedServerCallback([this]() {askplayerResponseInformNotInvolvedServerCallback(); });
    m_gameRunner->registerTellSuspicionCallback([this]() {tellSuspicionCallback(); });
    m_gameRunner->startGame();

    emit gameController_ready();
}

void GameController::askPlayer()
{
    if (m_gameRunner)
    {
        m_gameRunner->askPlayer();
    }
}

void GameController::askPlayer(int p_murderIndex, int p_weaponIndex, int p_roomIndex)
{
    CluedoObjectLoader& cluedoObjectLoader = CluedoObjectLoader::getInstance();
    std::vector<CluedoObject*> murders = cluedoObjectLoader.getMurders();
    CluedoObject* murder = murders.at(p_murderIndex);

    std::vector<CluedoObject*> weapons = cluedoObjectLoader.getWeapons();
    CluedoObject* weapon = weapons.at(p_weaponIndex);

    std::vector<CluedoObject*> rooms = cluedoObjectLoader.getRooms();
    CluedoObject* room = rooms.at(p_roomIndex);

    if (m_gameRunner)
    {
        m_gameRunner->askPlayer(murder, weapon, room);
    }
    else {
#if WIN32
        if (m_tcpWinSocketClient) {
            // Assume that the server is played by another player
            std::stringstream ss;
            ss << MessageIds::AskOtherPlayer << ":";
            ss << getSelfPlayerIndex();
            ss << ";";
            ss << murder->getNumber();
            ss << ";";
            ss << weapon->getNumber();
            ss << ";";
            ss << room->getNumber();
            ss << ";";
            m_tcpWinSocketClient->sendData(ss.str());
        }
#endif
    }
}

void GameController::askPlayerResponse(int p_cluedoObjectNumber) {
    if (m_gameRunner)
    {
        if (p_cluedoObjectNumber > CluedoObjectNumberInitValue) {
            CluedoObject* cluedoObject = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(p_cluedoObjectNumber);
            m_gameRunner->askPlayerResponse(true, cluedoObject);
        }
        else {
            m_gameRunner->askPlayerResponse(false, nullptr);
        }
    }
    else {
        // Assume that the server is played by another player
#if WIN32
        if (m_tcpWinSocketClient) {
            std::stringstream ss;
            ss << MessageIds::AskOtherPlayerResponse << ":";
            ss << getSelfPlayerIndex();
            ss << ";";
            ss << p_cluedoObjectNumber;
            ss << ";";
            m_tcpWinSocketClient->sendData(ss.str());
        }
#endif
    }
}

bool GameController::tellSuspicion(int p_murderIndex, int p_weaponIndex, int p_roomIndex)
{
    std::vector<CluedoObject*>& murders = CluedoObjectLoader::getInstance().getMurders();
    std::vector<CluedoObject*>& weapons = CluedoObjectLoader::getInstance().getWeapons();
    std::vector<CluedoObject*>& rooms = CluedoObjectLoader::getInstance().getRooms();

    return tellSuspicion(murders.at(p_murderIndex), weapons.at(p_weaponIndex), rooms.at(p_roomIndex));
}

bool GameController::tellSuspicion(CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room) {
    if ((nullptr == p_murder) || (nullptr == p_weapon) || (nullptr == p_room)) {
        return false;
    }

    bool isSuspicionCorrect = true;

    if (p_murder->getNumber() != m_effectiveMurder->getNumber())
    {
        isSuspicionCorrect = false;
    }

    if (isSuspicionCorrect)
    {
        if (p_weapon->getNumber() != m_effectiveWeapon->getNumber())
        {
            isSuspicionCorrect = false;
        }
    }

    if (isSuspicionCorrect)
    {
        if (p_room->getNumber() != m_effectiveRoom->getNumber())
        {
            isSuspicionCorrect = false;
        }
    }

    if (isSuspicionCorrect)
    {
        m_gameEnd = true;
    }

    std::vector<RemotePlayer*> remotePlayers = getRemotePlayers();
    for (RemotePlayer* remotePlayer : remotePlayers) {
        std::stringstream ss;
        ss << MessageIds::InformToldSuspicion << ":";
        ss << isSuspicionCorrect;
        ss << ";";
        ss << p_murder->getNumber();
        ss << ";";
        ss << p_weapon->getNumber();
        ss << ";";
        ss << p_room->getNumber();
        ss << ";";

        m_tcpWinSocketServer->sendData(remotePlayer->getRemoteSocket(), ss.str());
    }

    return isSuspicionCorrect;
}

void GameController::selectAndDistributeCluedoObjects()
{
    selectEffectiveMurderWeaponRoom();
    distributeCluedoObjects();
}

void GameController::sendPlayersListToClients() {
    std::vector<RemotePlayer*> remotePlayers = getRemotePlayers();
    for (RemotePlayer* remotePlayer : remotePlayers) {
        std::stringstream ss;
        ss << MessageIds::PlayersList << ":";
        int indexNumber = 0;
        for (Player* anyPlayer : getPlayers()) {
            if (remotePlayer != anyPlayer) {
                ss << indexNumber;
                ss << anyPlayer->getName() << ";";
            }
            indexNumber++;
        }
        m_tcpWinSocketServer->sendData(remotePlayer->getRemoteSocket(), ss.str());
     }
}

void GameController::sendCurrentPlayerIndexToClients() {
    std::vector<RemotePlayer*> remotePlayers = getRemotePlayers();
    for (RemotePlayer* remotePlayer : remotePlayers) {
        std::stringstream ss;
        ss << MessageIds::CurrentPlayerIndex << ":";
        ss << getCurrentPlayerIndex();
        m_tcpWinSocketServer->sendData(remotePlayer->getRemoteSocket(), ss.str());
    }
}

void GameController::registerRemoteServerMessages(bool p_client) {
    if (p_client) {
        auto receiveRemoteCluedoObjectCallback = [this](SOCKET, const std::string& p_message) { receiveRemoteCluedoObject(p_message); };
        MessageHandler::getInstance().registerMessageHandler(MessageIds::DistributeCluedoObject, receiveRemoteCluedoObjectCallback);

        auto receiveRemoteInformEffectiveCluedoObjectCallback = [this](SOCKET, const std::string& p_message) { receiveRemoteInformEffectiveCluedoObject(p_message); };
        MessageHandler::getInstance().registerMessageHandler(MessageIds::InformEffectiveCluedoObject, receiveRemoteInformEffectiveCluedoObjectCallback);

        auto receiveRemoteAllCluedoObjectsDistributedCallback = [this](SOCKET, const std::string&) { receiveRemoteAllCluedoObjectsDistributed(); };
        MessageHandler::getInstance().registerMessageHandler(MessageIds::AllCluedoObjectsDistributed, receiveRemoteAllCluedoObjectsDistributedCallback);

        auto receiveRemoteCurrentPlayerIndexCallback = [this](SOCKET, const std::string& p_message) { receiveRemoteCurrentPlayerIndex(p_message); };
        MessageHandler::getInstance().registerMessageHandler(MessageIds::CurrentPlayerIndex, receiveRemoteCurrentPlayerIndexCallback);

        auto receiveRemoteAskOtherPlayerCallback = [this](SOCKET, const std::string& p_message) { receiveRemoteAskOtherPlayer(p_message); };
        MessageHandler::getInstance().registerMessageHandler(MessageIds::AskOtherPlayer, receiveRemoteAskOtherPlayerCallback);

        auto receiveRemoteInformNotInvolvedPlayerResponseCallback = [this](SOCKET, const std::string& p_message) { receiveRemoteInformNotInvolvedPlayerResponse(p_message); };
        MessageHandler::getInstance().registerMessageHandler(MessageIds::InformNotInvolvedPlayer, receiveRemoteInformNotInvolvedPlayerResponseCallback);
    }
    else {
        auto receiveRemoteMoveToNextPlayerResponseCallback = [this](SOCKET, const std::string& p_message) { receiveRemoteMoveToNextPlayerResponse(p_message); };
        MessageHandler::getInstance().registerMessageHandler(MessageIds::MoveToNextPlayer, receiveRemoteMoveToNextPlayerResponseCallback);
    }

    auto receiveRemotePlayersListCallback = [this](SOCKET p_sourceSocket, const std::string& p_message) { receiveRemotePlayersList(p_sourceSocket, p_message); };
    MessageHandler::getInstance().registerMessageHandler(MessageIds::PlayersList, receiveRemotePlayersListCallback);

    auto receiveRemoteAskOtherPlayerCallback = [this](SOCKET, const std::string& p_message) { receiveRemoteAskOtherPlayer(p_message); };
    MessageHandler::getInstance().registerMessageHandler(MessageIds::AskOtherPlayer, receiveRemoteAskOtherPlayerCallback);

    auto receiveRemoteAskOtherPlayerResponseCallback = [this](SOCKET, const std::string& p_message) { receiveRemoteAskOtherPlayerResponse(p_message); };
    MessageHandler::getInstance().registerMessageHandler(MessageIds::AskOtherPlayerResponse, receiveRemoteAskOtherPlayerResponseCallback);

    auto receiveRemoteNoCluedoObjectCanBeShownResponseCallback = [this](SOCKET, const std::string&) { receiveRemoteNoCluedoObjectCanBeShownResponse(); };
    MessageHandler::getInstance().registerMessageHandler(MessageIds::NoCluedoObjectCanBeShown, receiveRemoteNoCluedoObjectCanBeShownResponseCallback);

    auto receiveRemoteInformToldSuspicionCallback = [this](SOCKET, const std::string& p_message) { receiveRemoteInformToldSuspicion(p_message); };
    MessageHandler::getInstance().registerMessageHandler(MessageIds::InformToldSuspicion, receiveRemoteInformToldSuspicionCallback);
}

Player* GameController::createNewPlayer(std::string p_name, Player::EPlayerType p_playerType)
{
    std::shared_ptr<PlayerSet> playerSet = createNewPlayerSet();

    Player* player = new Player(std::move(p_name), playerSet, p_playerType);
    m_players.push_back(player);

    if (Player::PlayerType_Computer != p_playerType) {
        m_humanPlayersReadyToMoveToNextPlayer.insert(std::make_pair(player, false));
    }

    return player;
}

Player* GameController::getSelfPlayer() {
    Player* selfPlayer = nullptr;

    for (Player* player : m_players)
    {
        if ((Player::PlayerType_SelfServer == player->getPlayerType()) || (Player::PlayerType_SelfClient == player->getPlayerType())) {
            selfPlayer = player;
            break;
        }
    }

    return selfPlayer;
}

int GameController::getCurrentPlayerIndex() {
    if (m_gameRunner) {
        return m_gameRunner->getCurrentPlayerIndex();
    }
    else {
        // Assume that the server is played by another player and the current player index is received from this server
        return m_currentPlayerIndexFromServer;
    }
}

Player* GameController::getCurrentPlayer()
{
    Player* currentPlayer{ nullptr };

    int currentPlayerIndex = getCurrentPlayerIndex();
    if (currentPlayerIndex >= 0)
    {
        currentPlayer = m_players.at(currentPlayerIndex);
    }

    return currentPlayer;
}

std::vector<Player*> GameController::getComputerPlayers() {
    std::vector<Player*> computerPlayers;

    for (Player* player : m_players)
    {
        if (Player::PlayerType_Computer == player->getPlayerType()) {
            if (player) {
                computerPlayers.push_back(player);
            }
        }
    }

    return computerPlayers;
}

std::vector<RemotePlayer*> GameController::getRemotePlayers() {
    std::vector<RemotePlayer*> remotePlayers;

    for (Player* player : m_players)
    {
        if (Player::PlayerType_Remote == player->getPlayerType()) {
            RemotePlayer* remotePlayer = dynamic_cast<RemotePlayer*>(player);
            if (remotePlayer) {
                remotePlayers.push_back(remotePlayer);
            }
        }
    }

    return remotePlayers;
}

void GameController::moveToNextPlayer(bool p_externalCall) {
    if (m_gameRunner) {
        if (p_externalCall) {
            m_humanPlayersReadyToMoveToNextPlayer[getSelfPlayer()] = true;
        }

        bool allPlayersReadyToMoveToNextPlayer = true;
        for (auto playerReadyPair : m_humanPlayersReadyToMoveToNextPlayer) {
            if (!playerReadyPair.second) {
                allPlayersReadyToMoveToNextPlayer = false;
                break;
            }
        }

        if (allPlayersReadyToMoveToNextPlayer) {
            m_gameRunner->moveToNextPlayer();
            sendCurrentPlayerIndexToClients();
            emit currentPlayerIndex_updated();

            // reset values
            for (auto& playerReadyPair : m_humanPlayersReadyToMoveToNextPlayer) {
                playerReadyPair.second = false;
            }
        }
    }
    else {
        // Assume that the server is played by another player
#if WIN32
        if (m_tcpWinSocketClient) {
            std::stringstream ss;
            ss << MessageIds::MoveToNextPlayer << ":";
            ss << getSelfPlayerIndex();
            m_tcpWinSocketClient->sendData(ss.str());
        }
#endif
    }
}

std::shared_ptr<PlayerSet> GameController::createNewPlayerSet()
{
    int numberOfPlayers = static_cast<int>(m_players.size());

    std::shared_ptr<PlayerSet> playerSet = std::make_shared<PlayerSet>(numberOfPlayers);
    initPlayerSet(playerSet);

    return playerSet;
}

void GameController::initPlayerSet(std::shared_ptr<PlayerSet> playerSet)
{
    std::vector<CluedoObject*>& murders = CluedoObjectLoader::getInstance().getMurders();
    for (CluedoObject* murder : murders)
    {
        playerSet->addUnknownCluedoObjects(murder);
    }

    std::vector<CluedoObject*>& weapons = CluedoObjectLoader::getInstance().getWeapons();
    for (CluedoObject* weapon : weapons)
    {
        playerSet->addUnknownCluedoObjects(weapon);
    }

    std::vector<CluedoObject*>& rooms = CluedoObjectLoader::getInstance().getRooms();
    for (CluedoObject* room : rooms)
    {
        playerSet->addUnknownCluedoObjects(room);
    }
}

int GameController::getSelfPlayerIndex() {
    int index = 0;
    
    for (Player* player : m_players)
    {
        if ((Player::PlayerType_SelfServer == player->getPlayerType()) || (Player::PlayerType_SelfClient == player->getPlayerType())) {
            break;
        }

        index++;
    }

    return index;
}

RemotePlayer* GameController::createNewRemotePlayer(int p_indexNumber, std::string p_name, SOCKET p_remoteSocket) {
    std::shared_ptr<PlayerSet> playerSet = createNewPlayerSet();

    RemotePlayer* remotePlayer = new RemotePlayer(std::move(p_name), playerSet, p_remoteSocket);
    m_players.insert(m_players.begin() + p_indexNumber, remotePlayer);
    m_humanPlayersReadyToMoveToNextPlayer.insert(std::make_pair(remotePlayer, false));

    return remotePlayer;
}

void GameController::selectEffectiveMurderWeaponRoom()
{
    std::vector<CluedoObject*>& murders = CluedoObjectLoader::getInstance().getMurders();
    int effectiveMurderIndex = Utils::generateRandomNumber(0, static_cast<int>(murders.size() - 1));
    m_effectiveMurder = murders.at(effectiveMurderIndex);
    addCluedoObjectsToDistribute(murders, CluedoObject::Murder);

    std::vector<CluedoObject*>& weapons = CluedoObjectLoader::getInstance().getWeapons();
    int effectiveWeaponIndex = Utils::generateRandomNumber(0, static_cast<int>(weapons.size() - 1));
    m_effectiveWeapon = weapons.at(effectiveWeaponIndex);
    addCluedoObjectsToDistribute(weapons, CluedoObject::Weapon);

    std::vector<CluedoObject*>& rooms = CluedoObjectLoader::getInstance().getRooms();
    int effectiveRoomIndex = Utils::generateRandomNumber(0, static_cast<int>(rooms.size() - 1));
    m_effectiveRoom = rooms.at(effectiveRoomIndex);
    addCluedoObjectsToDistribute(rooms, CluedoObject::Room);

    for (RemotePlayer* remotePlayer : getRemotePlayers()) {
        SOCKET remoteSocket = remotePlayer->getRemoteSocket();
        std::stringstream ss;
        ss << MessageIds::InformEffectiveCluedoObject << ":";
        ss << m_effectiveMurder->getNumber();
        ss << ";";
        ss << m_effectiveWeapon->getNumber();
        ss << ";";
        ss << m_effectiveRoom->getNumber();
        ss << ";";
        m_tcpWinSocketServer->sendData(remoteSocket, ss.str());
    }
}

void GameController::addCluedoObjectsToDistribute(std::vector<CluedoObject*>& p_cluedoObjects, CluedoObject::CluedoObjectType p_type)
{
    CluedoObject* cluedoObjectToIgnore = nullptr;
    if (CluedoObject::Murder == p_type)
    {
        cluedoObjectToIgnore = m_effectiveMurder;
    }
    else if (CluedoObject::Weapon == p_type)
    {
        cluedoObjectToIgnore = m_effectiveWeapon;
    }
    else if (CluedoObject::Room == p_type)
    {
        cluedoObjectToIgnore = m_effectiveRoom;
    }

    for (CluedoObject* cluedoObject : p_cluedoObjects)
    {
        if (cluedoObject != cluedoObjectToIgnore)
        {
            if (CluedoObject::Murder == p_type)
            {
                m_murdersToDistribute.push_back(cluedoObject);
            }
            else if (CluedoObject::Weapon == p_type)
            {
                m_weaponsToDistribute.push_back(cluedoObject);
            }
            else if (CluedoObject::Room == p_type)
            {
                m_roomsToDistribute.push_back(cluedoObject);
            }
        }
    }
}

void GameController::distributeCluedoObjects()
{
    distributeMurders();
    distributeWeapons();
    distributeRooms();

    for (RemotePlayer* remotePlayer : getRemotePlayers()) {
        SOCKET remoteSocket = remotePlayer->getRemoteSocket();
        printf("Send all cluedo objects are distributed\n");
        std::stringstream ss;
        ss << MessageIds::AllCluedoObjectsDistributed << ":";
        m_tcpWinSocketServer->sendData(remoteSocket, ss.str());
    }

    emit allCluedoObjects_distributed();
}

void GameController::distributeCluedoObjects(std::vector<CluedoObject*>& p_cluedoObjects)
{
    int playerSetIndex = m_lastDistributedPlayerSetIndex;

    auto it = p_cluedoObjects.begin();
    while(p_cluedoObjects.end() != it)
    {
        int cluedoObjectIndex = Utils::generateRandomNumber(0, static_cast<int>(p_cluedoObjects.size() - 1));
        Player* player = m_players.at(playerSetIndex);
        if (Player::PlayerType_Remote == player->getPlayerType()) {
            RemotePlayer* remotePlayer = dynamic_cast<RemotePlayer*>(player);
            if (remotePlayer) {
                SOCKET remoteSocket = remotePlayer->getRemoteSocket();
                printf("Send cluedo object: %s\n", p_cluedoObjects.at(cluedoObjectIndex)->getName().c_str());
                std::stringstream ss;
                ss << MessageIds::DistributeCluedoObject << ":";
                ss << p_cluedoObjects.at(cluedoObjectIndex)->getNumber();
                m_tcpWinSocketServer->sendData(remoteSocket, ss.str());
            }
        }
        else {
            PlayerSet* playerSet = player->getPlayerSet().get();
            playerSet->addCluedoObject(p_cluedoObjects.at(cluedoObjectIndex));
        }

        it = p_cluedoObjects.begin() + cluedoObjectIndex;
        it = p_cluedoObjects.erase(it);

        playerSetIndex++;
        if (m_players.size() == playerSetIndex)
        {
            playerSetIndex = 0;
        }
    };

    m_lastDistributedPlayerSetIndex = playerSetIndex;
}

void GameController::distributeMurders()
{
    distributeCluedoObjects(m_murdersToDistribute);
}

void GameController::distributeWeapons()
{
    distributeCluedoObjects(m_weaponsToDistribute);
}

void GameController::distributeRooms()
{
    distributeCluedoObjects(m_roomsToDistribute);
}

void GameController::showObjectCallback(int p_murderNumber, int p_weaponNumber, int p_roomNumber) {
    emit showObject_requested(p_murderNumber, p_weaponNumber, p_roomNumber);
}

void GameController::objectShownCallback() {
    emit askPlayerResponse_ready();
}

void GameController::noObjectCanBeShownCallback() {
    emit askPlayerResponse_ready();
}

void GameController::askplayerResponseInformNotInvolvedServerCallback() {
    Player* currentPlayer = getCurrentPlayer();
    PlayerSet* currentPlayerSet = currentPlayer->getPlayerSet().get();

    emit askPlayerFromOtherPlayer_finished(currentPlayerSet->getLastAskedMurder()->getNumber(), currentPlayerSet->getLastAskedWeapon()->getNumber(), currentPlayerSet->getLastAskedRoom()->getNumber());
}

void GameController::tellSuspicionCallback() {
    Player* currentPlayer = getCurrentPlayer();
    PlayerSet* currentPlayerSet = currentPlayer->getPlayerSet().get();

    CluedoObject* suspectedMurder = currentPlayerSet->getSuspectedMurder();
    CluedoObject* suspectedWeapon = currentPlayerSet->getSuspectedWeapon();
    CluedoObject* suspectedRoom = currentPlayerSet->getSuspectedRoom();
    bool isSuspicionCorrect = tellSuspicion(currentPlayerSet->getSuspectedMurder(), currentPlayerSet->getSuspectedWeapon(), currentPlayerSet->getSuspectedRoom());

    emit otherPlayerToldSuspicion(isSuspicionCorrect, suspectedMurder->getNumber(), suspectedWeapon->getNumber(), suspectedRoom->getNumber());
}

void GameController::receiveRemoteCluedoObject(const std::string& message) {
    std::stringstream ss{ message };
    int number;
    ss >> number;

    CluedoObject* cluedoObject = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(number);
    if (cluedoObject) {
        printf("Add cluedo object to client: %s\n", cluedoObject->getName().c_str());
        PlayerSet* playerSet = getSelfPlayer()->getPlayerSet().get();
        playerSet->addCluedoObject(cluedoObject);
    }
}

void GameController::receiveRemoteInformEffectiveCluedoObject(const std::string& message) {
    std::size_t delimiterPos = std::string::npos;
    std::size_t startPos = 0;

    while (std::string::npos != (delimiterPos = message.find(";", startPos))) {
        std::string cluedoObjectNumberString = message.substr(startPos, delimiterPos - startPos);
        std::stringstream ss;
        int cluedoObjectNumber;
        ss << cluedoObjectNumberString;
        ss >> cluedoObjectNumber;

        CluedoObject* cluedoObject = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(cluedoObjectNumber);
        if (cluedoObject) {
            if (CluedoObject::Murder == cluedoObject->getCluedoObjectType()) {
                m_effectiveMurder = cluedoObject;
            }
            else if (CluedoObject::Weapon == cluedoObject->getCluedoObjectType()) {
                m_effectiveWeapon = cluedoObject;
            }
            else if (CluedoObject::Room == cluedoObject->getCluedoObjectType()) {
                m_effectiveRoom = cluedoObject;
            }
        }

        startPos = delimiterPos + 1;
    }
}

void GameController::receiveRemoteAllCluedoObjectsDistributed() {
    printf("All cluedo objects distributed, ready for starting.");
    emit allCluedoObjects_distributed();
}

void GameController::receiveRemotePlayersList(SOCKET p_sourceSocket, const std::string& message) {
    std::size_t delimiterPos = std::string::npos;
    std::size_t startPos = 0;

    while(std::string::npos != (delimiterPos = message.find(";", startPos))) {
        std::string indexString = message.substr(startPos, 1);
        std::stringstream ss;
        int indexNumber;
        ss << indexString;
        ss >> indexNumber;

        std::string name = message.substr(startPos + 1, delimiterPos - (startPos + 1));
        if (std::string::npos != name.find("Computer")) {
            printf("Add computer player: %s with index number: %d\n", name.c_str(), indexNumber);
            createNewPlayer(std::move(name), Player::PlayerType_Computer);
        }
        else {
            printf("Add remote player: %s with index number: %d\n", name.c_str(), indexNumber);
            createNewRemotePlayer(indexNumber, std::move(name), p_sourceSocket);
        }

        emit remotePlayer_added();

        startPos = delimiterPos + 1;
    }

    emit playersList_updated();
}

void GameController::receiveRemoteCurrentPlayerIndex(const std::string& message) {
    std::stringstream ss{ message };
    ss >> m_currentPlayerIndexFromServer;
    printf("Current player index received from server: %d\n", m_currentPlayerIndexFromServer);

    emit currentPlayerIndex_updated();
}

void GameController::receiveRemoteAskOtherPlayer(const std::string& message) {
    std::size_t startPos = 0;
    std::size_t delimiterPos = message.find(";", startPos);

    if (std::string::npos != delimiterPos) {
        std::string playerIndexString = message.substr(startPos, delimiterPos - startPos);
        std::stringstream ssPlayerIndex;
        int playerIndex;
        ssPlayerIndex << playerIndexString;
        ssPlayerIndex >> playerIndex;

        startPos = delimiterPos + 1;
        std::vector<CluedoObject*> cluedoObjectsToAsk;

        while (std::string::npos != (delimiterPos = message.find(";", startPos))) {
            std::string cluedoObjectString = message.substr(startPos, delimiterPos - startPos);
            std::stringstream ssCluedoObject;
            int cluedoObjectNumber;
            ssCluedoObject << cluedoObjectString;
            ssCluedoObject >> cluedoObjectNumber;

            CluedoObject* cluedoObject = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(cluedoObjectNumber);
            if (cluedoObject) {
                cluedoObjectsToAsk.push_back(cluedoObject);
                printf("Cluedo Object to ask: %s\n", cluedoObject->getName().c_str());
            }

            startPos = delimiterPos + 1;
        }

        if (m_gameRunner) {
            m_gameRunner->askPlayer(cluedoObjectsToAsk.at(0), cluedoObjectsToAsk.at(1), cluedoObjectsToAsk.at(2));
        }
        else {
            // Assume that we are a remote client
            QString playerName = QString(m_players.at(playerIndex)->getName().c_str());
            int murderNumber = cluedoObjectsToAsk.at(0)->getNumber();
            int weaponNumber = cluedoObjectsToAsk.at(1)->getNumber();
            int roomNumber = cluedoObjectsToAsk.at(2)->getNumber();

            emit showObject_requested(murderNumber, weaponNumber, roomNumber);
        }
    }
}

void GameController::receiveRemoteAskOtherPlayerResponse(const std::string& message) {
    std::size_t startPos = 0;
    std::size_t delimiterPos = message.find(";", startPos);

    if (std::string::npos != delimiterPos) {
        std::string askedPlayerIndexString = message.substr(startPos, delimiterPos - startPos);
        std::stringstream ssAskedPlayerIndex;
        int askedPlayerIndex;
        ssAskedPlayerIndex << askedPlayerIndexString;
        ssAskedPlayerIndex >> askedPlayerIndex;

        startPos = delimiterPos + 1;

        delimiterPos = message.find(";", startPos);
        if (std::string::npos != delimiterPos) {
            std::string cluedoObjectString = message.substr(startPos, delimiterPos - startPos);
            std::stringstream ssCluedoObject;
            int cluedoObjectNumber;
            ssCluedoObject << cluedoObjectString;
            ssCluedoObject >> cluedoObjectNumber;

            bool objectCouldBeShown = false;
            CluedoObject* shownCluedoObject = nullptr;

            if (cluedoObjectNumber > CluedoObjectNumberInitValue) {
                objectCouldBeShown = true;
                shownCluedoObject = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(cluedoObjectNumber);
                printf("Cluedo Object shown upon asking: %s\n", shownCluedoObject->getName().c_str());
            }

            if (m_gameRunner)
            {
                m_gameRunner->askPlayerResponse(objectCouldBeShown, shownCluedoObject);
            }
            else {
                // Assume that we are a remote client
                PlayerSet* playerSet = getSelfPlayer()->getPlayerSet().get();
                playerSet->setLastShownCluedoObject(shownCluedoObject);
                
                if (objectCouldBeShown) {
                    playerSet->setLastPlayerIndexWhoShowedCluedoObject(askedPlayerIndex);
                    emit askPlayerResponse_ready();
                }
                else {
                    playerSet->addPlayerIndexWithNoShownCluedoObjects(askedPlayerIndex);
                }
            }
        }
    }
}

void GameController::receiveRemoteInformNotInvolvedPlayerResponse(const std::string& message) {
    std::size_t delimiterPos = std::string::npos;
    std::size_t startPos = 0;
    std::vector<CluedoObject*> cluedoObjectsToAsk;

    constexpr int TotalNumberOfCluedoObjectLoops = 3;
    int numberOfCluedoObjectLoops = 0;

    while ((numberOfCluedoObjectLoops < TotalNumberOfCluedoObjectLoops) && (std::string::npos != (delimiterPos = message.find(";", startPos)))) {
        std::string cluedoObjectString = message.substr(startPos, delimiterPos - startPos);
        std::stringstream ssCluedoObject;
        int cluedoObjectNumber;
        ssCluedoObject << cluedoObjectString;
        ssCluedoObject >> cluedoObjectNumber;

        CluedoObject* cluedoObject = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(cluedoObjectNumber);
        if (cluedoObject) {
            numberOfCluedoObjectLoops++;
            cluedoObjectsToAsk.push_back(cluedoObject);
        }

        startPos = delimiterPos + 1;
    }

    int murderNumber = cluedoObjectsToAsk.at(0)->getNumber();
    int weaponNumber = cluedoObjectsToAsk.at(1)->getNumber();
    int roomNumber = cluedoObjectsToAsk.at(2)->getNumber();

    delimiterPos = std::string::npos;
    PlayerSet* playerSet = getSelfPlayer()->getPlayerSet().get();
    playerSet->resetPlayerIndicesWithNoShownCluedoObjects();
    playerSet->setLastPlayerIndexWhoShowedCluedoObject(-1);

    while (std::string::npos != (delimiterPos = message.find(";", startPos))) {
        std::string playerIndexString = message.substr(startPos, delimiterPos - startPos);
        std::stringstream ssPlayerIndex;
        int playerIndex;
        ssPlayerIndex << playerIndexString;
        ssPlayerIndex >> playerIndex;

        startPos = delimiterPos + 1;

        delimiterPos = message.find(";", startPos);
        if (std::string::npos != delimiterPos) {
            std::string hasObjectString = message.substr(startPos, delimiterPos - startPos);
            std::stringstream ssHasObject;
            int hasObject;
            ssHasObject << hasObjectString;
            ssHasObject >> hasObject;

            if (hasObject > 0) {
                playerSet->setLastPlayerIndexWhoShowedCluedoObject(playerIndex);
            }
            else {
                playerSet->addPlayerIndexWithNoShownCluedoObjects(playerIndex);
            }

            startPos = delimiterPos + 1;
        }
    }

    emit askPlayerFromOtherPlayer_finished(murderNumber, weaponNumber, roomNumber);
}

void GameController::receiveRemoteNoCluedoObjectCanBeShownResponse() {
    printf("No Cluedo object can be shown!\n");
    emit askPlayerResponse_ready();
}

void GameController::receiveRemoteMoveToNextPlayerResponse(const std::string& message) {
    std::stringstream ssPlayerIndex{ message };
    int playerIndex;
    ssPlayerIndex >> playerIndex;
    printf("Move to next player, player index: %d\n", playerIndex);
    m_humanPlayersReadyToMoveToNextPlayer[m_players.at(playerIndex)] = true;

    moveToNextPlayer(false);
}

void GameController::receiveRemoteInformToldSuspicion(const std::string& message) {
    std::size_t startPos = 0;
    std::size_t delimiterPos = message.find(";", startPos);

    if (std::string::npos != delimiterPos) {
        std::string isSuspicionCorrectString = message.substr(startPos, delimiterPos - startPos);
        std::stringstream ssIsSuspicionCorrect;
        int isSuspicionCorrect;
        ssIsSuspicionCorrect << isSuspicionCorrectString;
        ssIsSuspicionCorrect >> isSuspicionCorrect;

        startPos = delimiterPos + 1;
        std::vector<CluedoObject*> suspectedCluedoObjects;

        while (std::string::npos != (delimiterPos = message.find(";", startPos))) {
            std::string cluedoObjectString = message.substr(startPos, delimiterPos - startPos);
            std::stringstream ssCluedoObject;
            int cluedoObjectNumber;
            ssCluedoObject << cluedoObjectString;
            ssCluedoObject >> cluedoObjectNumber;

            CluedoObject* cluedoObject = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(cluedoObjectNumber);
            if (cluedoObject) {
                suspectedCluedoObjects.push_back(cluedoObject);
            }

            startPos = delimiterPos + 1;
        }

        int murderNumber = suspectedCluedoObjects.at(0)->getNumber();
        int weaponNumber = suspectedCluedoObjects.at(1)->getNumber();
        int roomNumber = suspectedCluedoObjects.at(2)->getNumber();

        Player* selfPlayer = getSelfPlayer();

        if (Player::PlayerType_SelfServer == selfPlayer->getPlayerType()) {
            std::vector<RemotePlayer*> remotePlayers = getRemotePlayers();
            Player* currentPlayer = getCurrentPlayer();
            for (RemotePlayer* remotePlayer : remotePlayers) {
                if (remotePlayer != currentPlayer) {
                    std::stringstream ss;
                    ss << MessageIds::InformToldSuspicion << ":";
                    ss << isSuspicionCorrect;
                    ss << ";";
                    ss << murderNumber;
                    ss << ";";
                    ss << weaponNumber;
                    ss << ";";
                    ss << roomNumber;
                    ss << ";";
                    m_tcpWinSocketServer->sendData(remotePlayer->getRemoteSocket(), ss.str());
                }
            }
        }

        emit otherPlayerToldSuspicion(isSuspicionCorrect, murderNumber, weaponNumber, roomNumber);
    }
}