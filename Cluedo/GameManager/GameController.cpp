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
    m_gameRunner = std::make_shared<GameRunner>(m_players);

    emit playersList_updated();
    emit gameController_ready();
}

void GameController::askPlayer()
{
    if (m_gameRunner)
    {
        m_gameRunner->askPlayer(m_currentPlayerIndex);
    }
}

void GameController::askPlayer(int p_murderIndex, int p_weaponIndex, int p_roomIndex)
{
    if (m_gameRunner)
    {
        m_gameRunner->askPlayer(m_currentPlayerIndex, p_murderIndex, p_weaponIndex, p_roomIndex);
    }
}

bool GameController::tellSuspicion(int p_murderIndex, int p_weaponIndex, int p_roomIndex)
{
    bool isSuspicionCorrect = true;

    std::vector<CluedoObject*>& murders = CluedoObjectLoader::getInstance().getMurders();
    if (murders.at(p_murderIndex) != m_effectiveMurder)
    {
        isSuspicionCorrect = false;
    }

    if (isSuspicionCorrect)
    {
        std::vector<CluedoObject*>& weapons = CluedoObjectLoader::getInstance().getWeapons();
        if (weapons.at(p_weaponIndex) != m_effectiveWeapon)
        {
            isSuspicionCorrect = false;
        }
    }

    if (isSuspicionCorrect)
    {
        std::vector<CluedoObject*>& rooms = CluedoObjectLoader::getInstance().getRooms();
        if (rooms.at(p_roomIndex) != m_effectiveRoom)
        {
            isSuspicionCorrect = false;
        }
    }

    if (isSuspicionCorrect)
    {
        m_gameEnd = true;
    }

    return isSuspicionCorrect;
}

bool GameController::shouldTellSuspicion()
{
    bool shouldTellSuspicion = false;

    Player* currentPlayer = getCurrentPlayer();
    PlayerSet* currentPlayerSet = currentPlayer->getPlayerSet().get();

    return currentPlayerSet->getShouldTellSuspicion();
}

void GameController::selectAndDistributeCluedoObjects()
{
    selectEffectiveMurderWeaponRoom();
    distributeCluedoObjects();
}

RemotePlayer* GameController::createNewRemotePlayerOnServer(SOCKET p_clientSocket)
{
    std::shared_ptr<PlayerSet> playerSet = createNewPlayerSet();

    RemotePlayer* remotePlayer = new RemotePlayer(p_clientSocket, playerSet);
    m_players.push_back(remotePlayer);

    return remotePlayer;
}

void GameController::sendPlayersListToClients() {
    std::vector<RemotePlayer*> remotePlayers = getRemotePlayers();
    for (RemotePlayer* remotePlayer : remotePlayers) {
        std::stringstream ss;
        ss << MessageIds::PlayersList << ":";
        for (Player* anyPlayer : getPlayers()) {
            if (remotePlayer != anyPlayer) {
                ss << anyPlayer->getName() << ";";
            }
        }
        m_tcpWinSocketServer->sendData(remotePlayer->getClientSocket(), ss.str());
     }
}

void GameController::registerRemoteServerMessages() {
    auto receiveRemoteCluedoObjectCallback = [this](const std::string& p_message) { receiveRemoteCluedoObject(p_message); };
    MessageHandler::getInstance().registerMessageHandler(MessageIds::DistributeCluedoObject, receiveRemoteCluedoObjectCallback);

    auto receiveRemoteAllCluedoObjectsDistributedCallback = [this](const std::string&) { receiveRemoteAllCluedoObjectsDistributed(); };
    MessageHandler::getInstance().registerMessageHandler(MessageIds::AllCluedoObjectsDistributed, receiveRemoteAllCluedoObjectsDistributedCallback);

    auto receiveRemotePlayersListCallback = [this](const std::string& p_message) { receiveRemotePlayersList(p_message); };
    MessageHandler::getInstance().registerMessageHandler(MessageIds::PlayersList, receiveRemotePlayersListCallback);
}

Player* GameController::createNewPlayer(std::string p_name, Player::EPlayerType p_playerType)
{
    std::shared_ptr<PlayerSet> playerSet = createNewPlayerSet();

    Player* player = new Player(std::move(p_name), playerSet, p_playerType);
    m_players.push_back(player);

    return player;
}

Player* GameController::getCurrentPlayer()
{
    Player* currentPlayer{ nullptr };

    if (m_currentPlayerIndex >= 0)
    {
        currentPlayer = m_players.at(m_currentPlayerIndex);
    }

    return currentPlayer;
}

std::shared_ptr<PlayerSet> GameController::createNewPlayerSet()
{
    int numberOfPlayers = static_cast<int>(m_players.size());

    std::shared_ptr<PlayerSet> playerSet = std::make_shared<PlayerSet>(numberOfPlayers + 1);
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

RemotePlayer* GameController::createNewRemotePlayerOnClient(std::string p_name) {
    std::shared_ptr<PlayerSet> playerSet = createNewPlayerSet();

    RemotePlayer* remotePlayer = new RemotePlayer(std::move(p_name), playerSet);
    m_players.push_back(remotePlayer);

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
        SOCKET clientSocket = remotePlayer->getClientSocket();
        printf("Send all cluedo objects are distributed\n");
        std::stringstream ss;
        ss << MessageIds::AllCluedoObjectsDistributed << ":";
        m_tcpWinSocketServer->sendData(clientSocket, ss.str());
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
                SOCKET clientSocket = remotePlayer->getClientSocket();
                printf("Send cluedo object: %s\n", p_cluedoObjects.at(cluedoObjectIndex)->getName().c_str());
                std::stringstream ss;
                ss << MessageIds::DistributeCluedoObject << ":";
                ss << p_cluedoObjects.at(cluedoObjectIndex)->getNumber();
                m_tcpWinSocketServer->sendData(clientSocket, ss.str());
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

void GameController::receiveRemoteCluedoObject(const std::string& message) {
    std::stringstream ss{ message };
    int number;
    ss >> number;

    PlayerSet* playerSet = getSelfPlayer()->getPlayerSet().get();
    CluedoObject* cluedoObject = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(number);
    if (cluedoObject) {
        printf("Add cluedo object to client: %s\n", cluedoObject->getName().c_str());
        playerSet->addCluedoObject(cluedoObject);
    }
}

void GameController::receiveRemoteAllCluedoObjectsDistributed() {
    printf("All cluedo objects distributed, ready for starting.");
    emit allCluedoObjects_distributed();
}

void GameController::receiveRemotePlayersList(const std::string& message) {
    std::size_t delimiterPos = std::string::npos;
    std::size_t startPos = 0;

    while(std::string::npos != (delimiterPos = message.find(";", startPos))) {
        std::string name = message.substr(startPos, delimiterPos - startPos);
        printf("Add remote player: %s\n", name.c_str());
        createNewRemotePlayerOnClient(std::move(name));
        startPos = delimiterPos + 1;
    }

    emit playersList_updated();
}