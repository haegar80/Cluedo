#include "GameRunner.h"
#include "../Model/Player.h"
#include <map>

GameRunner::GameRunner(std::vector<Player*>& p_players) : m_players(p_players)
{
}

void GameRunner::askPlayer(int p_murderIndex, int p_weaponIndex, int p_roomIndex)
{
    CluedoObjectLoader& cluedoObjectLoader = CluedoObjectLoader::getInstance();
    std::vector<CluedoObject*> murders = cluedoObjectLoader.getMurders();
    CluedoObject* murder = murders.at(p_murderIndex);

    std::vector<CluedoObject*> weapons = cluedoObjectLoader.getWeapons();
    CluedoObject* weapon = weapons.at(p_weaponIndex);

    std::vector<CluedoObject*> rooms = cluedoObjectLoader.getRooms();
    CluedoObject* room = rooms.at(p_roomIndex);

    checkObjectsAtOtherPlayers(murder, weapon, room);
}

void GameRunner::checkObjectsAtOtherPlayers(CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room)
{
    int playerIndexToAsk = m_currentPlayerIndex + 1;

    CluedoObject* foundObject = nullptr;
    while ((playerIndexToAsk != m_currentPlayerIndex) && (nullptr == foundObject))
    {
        if (m_players.size() == playerIndexToAsk)
        {
            playerIndexToAsk = 0;
        }
        foundObject = askObjectsAtOtherPlayer(playerIndexToAsk, p_murder, p_weapon, p_room);

        playerIndexToAsk++;
    }

    if (nullptr != foundObject)
    {
        PlayerSet* currentPlayerSet = m_players.at(m_currentPlayerIndex)->getPlayerSet().get();
        currentPlayerSet->setLastShownCluedoObject(foundObject);
        currentPlayerSet->addCluedoObjectFromOtherPlayers(--playerIndexToAsk, foundObject);
    }
}

CluedoObject* GameRunner::askObjectsAtOtherPlayer(int p_playerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room)
{
    CluedoObject* foundObject = nullptr;

    PlayerSet* currentPlayerSet = m_players.at(m_currentPlayerIndex)->getPlayerSet().get();
    std::vector<CluedoObject*>& cluedoObjects = currentPlayerSet->getCluedoObjects();

    bool murderIsAtOtherPlayer = false;
    bool weaponIsAtOtherPlayer = false;
    bool roomIsAtOtherPlayer = false;

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

void GameRunner::getObjectsToAsk(int p_playerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room)
{
    CluedoObjectLoader& cluedoObjectLoader = CluedoObjectLoader::getInstance();
    std::vector<CluedoObject*>& murders = cluedoObjectLoader.getMurders();
    std::vector<CluedoObject*>& weapons = cluedoObjectLoader.getWeapons();
    std::vector<CluedoObject*>& rooms = cluedoObjectLoader.getRooms();

    bool foundUnknownMurder = findUnknownObject(p_playerIndex, murders, p_murder);
    if (!foundUnknownMurder)
    {
        (void) findKnownObject(p_playerIndex, CluedoObject::Murder, p_murder);
    }

    bool foundUnknownWeapon = findUnknownObject(p_playerIndex, weapons, p_weapon);
    if (!foundUnknownWeapon)
    {
        (void)findKnownObject(p_playerIndex, CluedoObject::Weapon, p_weapon);
    }

    bool foundUnknownRoom = findUnknownObject(p_playerIndex, rooms, p_room);
    if (!foundUnknownRoom)
    {
        (void)findKnownObject(p_playerIndex, CluedoObject::Room, p_room);
    }
}

bool GameRunner::findUnknownObject(int p_playerIndex, std::vector<CluedoObject*>& p_cluedoObjectsToCheck, CluedoObject* p_foundObject)
{
    bool foundObject = false;

    PlayerSet* currentPlayerSet = m_players.at(m_currentPlayerIndex)->getPlayerSet().get();
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

bool GameRunner::findKnownObject(int p_playerIndex, CluedoObject::CluedoObjectType p_objectType, CluedoObject* p_foundObject)
{
    bool foundObject = false;

    PlayerSet* currentPlayerSet = m_players.at(m_currentPlayerIndex)->getPlayerSet().get();
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