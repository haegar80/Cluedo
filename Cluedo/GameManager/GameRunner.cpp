#include "GameRunner.h"
#include "../Model/Player.h"
#include <map>
#include <algorithm>
#include <random>

GameRunner::GameRunner(std::vector<Player*>& p_players) : m_players(p_players)
{
}

void GameRunner::askPlayer(int p_currentPlayerIndex)
{
    CluedoObject* murderToAsk{ nullptr };
    CluedoObject* weaponToAsk{ nullptr };
    CluedoObject* roomToAsk{ nullptr };
    getObjectsToAsk(p_currentPlayerIndex, &murderToAsk, &weaponToAsk, &roomToAsk);

    checkObjectsAtOtherPlayers(p_currentPlayerIndex, murderToAsk, weaponToAsk, roomToAsk);
}

void GameRunner::askPlayer(int p_currentPlayerIndex, int p_murderIndex, int p_weaponIndex, int p_roomIndex)
{
    CluedoObjectLoader& cluedoObjectLoader = CluedoObjectLoader::getInstance();
    std::vector<CluedoObject*> murders = cluedoObjectLoader.getMurders();
    CluedoObject* murder = murders.at(p_murderIndex);

    std::vector<CluedoObject*> weapons = cluedoObjectLoader.getWeapons();
    CluedoObject* weapon = weapons.at(p_weaponIndex);

    std::vector<CluedoObject*> rooms = cluedoObjectLoader.getRooms();
    CluedoObject* room = rooms.at(p_roomIndex);

    checkObjectsAtOtherPlayers(p_currentPlayerIndex, murder, weapon, room);
}

void GameRunner::checkObjectsAtOtherPlayers(int p_currentPlayerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room)
{
    int playerIndexToAsk = p_currentPlayerIndex + 1;

    PlayerSet* currentPlayerSet = m_players.at(p_currentPlayerIndex)->getPlayerSet().get();
    currentPlayerSet->setLastAskedMurder(p_murder);
    currentPlayerSet->setLastAskedWeapon(p_weapon);
    currentPlayerSet->setLastAskedRoom(p_room);
    currentPlayerSet->resetPlayerIndicesWithNoShownCluedoObjects();

    CluedoObject* foundObject = nullptr;
    while ((playerIndexToAsk != p_currentPlayerIndex) && (nullptr == foundObject))
    {
        if (m_players.size() == playerIndexToAsk)
        {
            playerIndexToAsk = 0;
            if (playerIndexToAsk == p_currentPlayerIndex)
            {
                break;
            }
        }
        foundObject = askObjectsAtOtherPlayer(playerIndexToAsk, p_murder, p_weapon, p_room);

        if (nullptr == foundObject)
        {
            currentPlayerSet->addPlayerIndexWithNoShownCluedoObjects(playerIndexToAsk);
            currentPlayerSet->addMissingCluedoObjectsAtOtherPlayers(playerIndexToAsk, p_murder);
            currentPlayerSet->addMissingCluedoObjectsAtOtherPlayers(playerIndexToAsk, p_weapon);
            currentPlayerSet->addMissingCluedoObjectsAtOtherPlayers(playerIndexToAsk, p_room);
        }

        playerIndexToAsk++;
    }

    if (nullptr != foundObject)
    {
        int playerIndex = --playerIndexToAsk;
        currentPlayerSet->setLastShownCluedoObject(foundObject);
        currentPlayerSet->setLastPlayerIndexWhoShowedCluedoObject(playerIndex);
        currentPlayerSet->addCluedoObjectFromOtherPlayers(playerIndex, foundObject);
    }
    else
    {
        currentPlayerSet->setLastShownCluedoObject(nullptr);
    }
}

CluedoObject* GameRunner::askObjectsAtOtherPlayer(int p_otherPlayerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room)
{
    CluedoObject* foundObject = nullptr;

    PlayerSet* playerSet = m_players.at(p_otherPlayerIndex)->getPlayerSet().get();
    std::vector<CluedoObject*>& cluedoObjects = playerSet->getCluedoObjects();

    for (CluedoObject* cluedoObject : cluedoObjects)
    {
        if (cluedoObject == p_murder)
        {
            foundObject = p_murder;
            break;
        }
        else if (cluedoObject == p_weapon)
        {
            foundObject = p_weapon;
            break;
        }
        else if (cluedoObject == p_room)
        {
            foundObject = p_room;
            break;
        }
    }

    return foundObject;
}

void GameRunner::getObjectsToAsk(int p_currentPlayerIndex, CluedoObject** p_murder, CluedoObject** p_weapon, CluedoObject** p_room)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    CluedoObjectLoader& cluedoObjectLoader = CluedoObjectLoader::getInstance();
    std::vector<CluedoObject*>murders = cluedoObjectLoader.getMurders();
    auto randomEngineMurders = std::default_random_engine(seed);
    std::shuffle(std::begin(murders), std::end(murders), randomEngineMurders);

    std::vector<CluedoObject*>weapons = cluedoObjectLoader.getWeapons();
    auto randomEngineWeapons = std::default_random_engine(seed);
    std::shuffle(std::begin(weapons), std::end(weapons), randomEngineWeapons);

    std::vector<CluedoObject*>rooms = cluedoObjectLoader.getRooms();
    auto randomEngineRooms = std::default_random_engine(seed);
    std::shuffle(std::begin(rooms), std::end(rooms), randomEngineRooms);

    findUnknownObject(p_currentPlayerIndex, murders, p_murder);
    findUnknownObject(p_currentPlayerIndex, weapons, p_weapon);
    findUnknownObject(p_currentPlayerIndex, rooms, p_room);
}

void GameRunner::findUnknownObject(int p_currentPlayerIndex, std::vector<CluedoObject*>& p_cluedoObjectsToCheck, CluedoObject** p_foundObject)
{
    bool foundUnknownObject = false;

    PlayerSet* currentPlayerSet = m_players.at(p_currentPlayerIndex)->getPlayerSet().get();
    std::vector<CluedoObject*>& cluedoObjects = currentPlayerSet->getCluedoObjects();
    std::multimap<int, CluedoObject*>& cluedoObjectsFromOtherPlayers = currentPlayerSet->getCluedoObjectsFromOtherPlayers();

    for (CluedoObject* cluedoObject : p_cluedoObjectsToCheck)
    {
        auto resultObjectsFromCurrentPlayer = std::find_if(
            cluedoObjects.begin(),
            cluedoObjects.end(),
            [cluedoObject](const CluedoObject* vectorObject) {return vectorObject == cluedoObject; });

        if (cluedoObjects.end() == resultObjectsFromCurrentPlayer)
        {
            *p_foundObject = cluedoObject;
            foundUnknownObject = true;
        }

        if(foundUnknownObject)
        {
            foundUnknownObject = false;

            auto resultObjectsFromOtherPlayers = std::find_if(
                cluedoObjectsFromOtherPlayers.begin(),
                cluedoObjectsFromOtherPlayers.end(),
                [cluedoObject](const auto& mapObject) {return mapObject.second == cluedoObject; });

            if (cluedoObjectsFromOtherPlayers.end() == resultObjectsFromOtherPlayers)
            {
                *p_foundObject = cluedoObject;
                foundUnknownObject = true;
                break;
            }
        }
    }
}