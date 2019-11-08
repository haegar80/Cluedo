#include "GameRunner.h"
#include "CluedoObjectLoader.h"
#include "../Model/Player.h"

GameRunner::GameRunner(std::vector<Player*>& p_players) : m_players(p_players)
{
}

void GameRunner::askPlayer(int p_murderIndex, int p_weaponIndex, int p_roomIndex)
{
    std::vector<CluedoObject*> murders = CluedoObjectLoader::getInstance().getMurders();
    CluedoObject* murder = murders.at(p_murderIndex);

    std::vector<CluedoObject*> weapons = CluedoObjectLoader::getInstance().getWeapons();
    CluedoObject* weapon = weapons.at(p_weaponIndex);

    std::vector<CluedoObject*> rooms = CluedoObjectLoader::getInstance().getRooms();
    CluedoObject* room = rooms.at(p_roomIndex);
}

void GameRunner::setCurrentPlayer(int p_currentPlayerIndex)
{
    m_currentPlayerIndex = p_currentPlayerIndex;
}

void GameRunner::checkObjectAtOtherPlayer(CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room)
{
    for (int i = 0; i < m_players.size(); i++)
    {
        if (i == m_currentPlayerIndex)
        {
            continue;
        }

    }
}