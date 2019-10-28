#include "GameController.h"
#include "CluedoObjectLoader.h"
#include "../Model/Player.h"
#include "../Model/PlayerSet.h"
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

GameController& GameController::getInstance()
{
    static GameController instance;
    return instance;
}

GameController::~GameController()
{
    for (Player* player : m_players)
    {
        delete player;
    }

    for (PlayerSet* playerSet : m_playerSets)
    {
        delete playerSet;
    }
}

void GameController::reset()
{
    m_players.clear();
    m_playerSets.clear();
}

void GameController::startGameRounds()
{
    for (auto callback : m_playerUpdateCallbacks)
    {
        callback();
    }
}

void GameController::selectAndDistributeCluedoObjects()
{
    selectEffectiveMurderWeaponRoom();
    distributeCluedoObjects();
}

Player* GameController::createNewPlayer(std::string p_name)
{
    Player* player = new Player(std::move(p_name));
    m_players.push_back(player);

    return player;
}

PlayerSet* GameController::createNewPlayerSet()
{
    int numberOfPlayerSets = static_cast<int>(m_playerSets.size());

    PlayerSet* playerSet = new PlayerSet(numberOfPlayerSets + 1);
    m_playerSets.push_back(playerSet);

    return playerSet;
}

void GameController::registerPlayerUpdateCallback(std::function<void(void)> p_callback)
{
    m_playerUpdateCallbacks.push_back(p_callback);
}

void GameController::selectEffectiveMurderWeaponRoom()
{
    std::vector<CluedoObject*>& murders = CluedoObjectLoader::getInstance().getMurders();
    int effectiveMurderIndex = generateRandomNumber(0, static_cast<int>(murders.size() - 1));
    m_effectiveMurder = murders.at(effectiveMurderIndex);
    addCluedoObjectsToDistribute(murders, CluedoObject::Murder);

    std::vector<CluedoObject*>& weapons = CluedoObjectLoader::getInstance().getWeapons();
    int effectiveWeaponIndex = generateRandomNumber(0, static_cast<int>(weapons.size() - 1));
    m_effectiveWeapon = weapons.at(effectiveWeaponIndex);
    addCluedoObjectsToDistribute(weapons, CluedoObject::Weapon);

    std::vector<CluedoObject*>& rooms = CluedoObjectLoader::getInstance().getRooms();
    int effectiveRoomIndex = generateRandomNumber(0, static_cast<int>(rooms.size() - 1));
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
    srand(time(NULL));

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
        int cluedoObjectIndex = generateRandomNumber(0, static_cast<int>(p_cluedoObjects.size() - 1));
        m_playerSets.at(playerSetIndex)->addCluedoObject(p_cluedoObjects.at(cluedoObjectIndex));
        it = p_cluedoObjects.begin() + cluedoObjectIndex;
        it = p_cluedoObjects.erase(it);

        playerSetIndex++;
        if (m_playerSets.size() == playerSetIndex)
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

int GameController::generateRandomNumber(int p_minNumber, int p_maxNumber)
{
    /* generate secret number between 1 and 10: */
    int randomNumber = 0;
    if (p_maxNumber > 0)
    {
        randomNumber = rand() % p_maxNumber + p_minNumber;
    }

    return randomNumber;
}