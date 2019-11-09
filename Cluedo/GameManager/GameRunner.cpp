#include "GameRunner.h"
#include "../Model/Player.h"
#include <map>

GameRunner::GameRunner(std::vector<Player*>& p_players) : m_players(p_players)
{
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

    CluedoObject* foundObject = nullptr;
    while ((playerIndexToAsk != p_currentPlayerIndex) && (nullptr == foundObject))
    {
        if (m_players.size() == playerIndexToAsk)
        {
            playerIndexToAsk = 0;
        }
        foundObject = askObjectsAtOtherPlayer(playerIndexToAsk, p_murder, p_weapon, p_room);

        playerIndexToAsk++;
    }

    PlayerSet* currentPlayerSet = m_players.at(p_currentPlayerIndex)->getPlayerSet().get();
    if (nullptr != foundObject)
    {
        currentPlayerSet->setLastShownCluedoObject(foundObject);
        currentPlayerSet->addCluedoObjectFromOtherPlayers(--playerIndexToAsk, foundObject);
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

void GameRunner::getObjectsToAsk(int p_currentPlayerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room)
{
    CluedoObjectLoader& cluedoObjectLoader = CluedoObjectLoader::getInstance();
    std::vector<CluedoObject*>& murders = cluedoObjectLoader.getMurders();
    std::vector<CluedoObject*>& weapons = cluedoObjectLoader.getWeapons();
    std::vector<CluedoObject*>& rooms = cluedoObjectLoader.getRooms();

    bool foundUnknownMurder = findUnknownObject(p_currentPlayerIndex, murders, p_murder);
    if (!foundUnknownMurder)
    {
        (void) findKnownObject(p_currentPlayerIndex, CluedoObject::Murder, p_murder);
    }

    bool foundUnknownWeapon = findUnknownObject(p_currentPlayerIndex, weapons, p_weapon);
    if (!foundUnknownWeapon)
    {
        (void)findKnownObject(p_currentPlayerIndex, CluedoObject::Weapon, p_weapon);
    }

    bool foundUnknownRoom = findUnknownObject(p_currentPlayerIndex, rooms, p_room);
    if (!foundUnknownRoom)
    {
        (void)findKnownObject(p_currentPlayerIndex, CluedoObject::Room, p_room);
    }
}

bool GameRunner::findUnknownObject(int p_currentPlayerIndex, std::vector<CluedoObject*>& p_cluedoObjectsToCheck, CluedoObject* p_foundObject)
{
    bool foundObject = false;

    PlayerSet* currentPlayerSet = m_players.at(p_currentPlayerIndex)->getPlayerSet().get();
    std::multimap<int, CluedoObject*>& cluedoObjectsFromOtherPlayers = currentPlayerSet->getCluedoObjectsFromOtherPlayers();

    for (CluedoObject* cluedoObject : p_cluedoObjectsToCheck)
    {
        auto result = std::find_if(
            cluedoObjectsFromOtherPlayers.begin(),
            cluedoObjectsFromOtherPlayers.end(),
            [cluedoObject](const auto& mapObject) {return mapObject.second == cluedoObject; });

        if (cluedoObjectsFromOtherPlayers.end() == result)
        {
            p_foundObject = cluedoObject;
            foundObject = true;
            break;
        }
    }

    return foundObject;
}

bool GameRunner::findKnownObject(int p_currentPlayerIndex, CluedoObject::CluedoObjectType p_objectType, CluedoObject* p_foundObject)
{
    bool foundObject = false;

    PlayerSet* currentPlayerSet = m_players.at(p_currentPlayerIndex)->getPlayerSet().get();
    std::multimap<int, CluedoObject*>& cluedoObjectsFromOtherPlayers = currentPlayerSet->getCluedoObjectsFromOtherPlayers();

    for (std::pair<int, CluedoObject*> knownObject : cluedoObjectsFromOtherPlayers)
    {
        if (p_objectType == knownObject.second->getCluedoObjectType())
        {
            p_foundObject = knownObject.second;
            foundObject = true;
            break;
        }
    }

    return foundObject;
}