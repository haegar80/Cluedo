#include "GameController.h"
#include "CluedoObjectLoader.h"
#include "../Model/PlayerSet.h"
#include "../Utils/Utils.h"

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

    for (auto callback : m_playerUpdateCallbacks)
    {
        callback();
    }

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

RemotePlayer* GameController::createNewRemotePlayer(std::string p_name) 
{
    std::shared_ptr<PlayerSet> playerSet = createNewPlayerSet();
    
    RemotePlayer* remotePlayer = new RemotePlayer(std::move(p_name), playerSet);
    m_players.push_back(remotePlayer);

    return remotePlayer;
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

void GameController::registerPlayerUpdateCallback(std::function<void(void)> p_callback)
{
    m_playerUpdateCallbacks.push_back(p_callback);
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
}

void GameController::distributeCluedoObjects(std::vector<CluedoObject*>& p_cluedoObjects)
{
    int playerSetIndex = m_lastDistributedPlayerSetIndex;

    auto it = p_cluedoObjects.begin();
    while(p_cluedoObjects.end() != it)
    {
        int cluedoObjectIndex = Utils::generateRandomNumber(0, static_cast<int>(p_cluedoObjects.size() - 1));
        PlayerSet* playerSet = m_players.at(playerSetIndex)->getPlayerSet().get();
        playerSet->addCluedoObject(p_cluedoObjects.at(cluedoObjectIndex));
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