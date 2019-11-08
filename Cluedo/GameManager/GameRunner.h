#pragma once

#include "CluedoObjectLoader.h"
#include <vector>

class Player;
class CluedoObject;

class GameRunner
{
public:
    GameRunner(std::vector<Player*>& p_players);
    virtual ~GameRunner() = default;

    void askPlayer(int p_murderIndex, int p_weaponIndex, int p_roomIndex);
    int getCurrentPlayerIndex()
    {
        return m_currentPlayerIndex;
    }

    void setCurrentPlayerIndex(int p_currentPlayerIndex)
    {
        m_currentPlayerIndex = p_currentPlayerIndex;
    }

    GameRunner(const GameRunner& copy) = default;
    GameRunner& operator= (const GameRunner& copy) = default;
    GameRunner(GameRunner&& other) = default;
    GameRunner& operator= (GameRunner&& other) = default;

private:
    std::vector<Player*> m_players;
    int m_currentPlayerIndex{ -1 };

    void checkObjectsAtOtherPlayers(CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room);
    CluedoObject* askObjectsAtOtherPlayer(int p_playerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room);
    void getObjectsToAsk(int p_playerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room);
    bool findUnknownObject(int p_playerIndex, std::vector<CluedoObject*>& p_cluedoObjectsToCheck, CluedoObject* p_foundObject);
    bool findKnownObject(int p_playerIndex, CluedoObject::CluedoObjectType p_objectType, CluedoObject* p_foundObject);
};

