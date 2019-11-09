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

    void askPlayer(int p_currentPlayerIndex, int p_murderIndex, int p_weaponIndex, int p_roomIndex);

    GameRunner(const GameRunner& copy) = default;
    GameRunner& operator= (const GameRunner& copy) = default;
    GameRunner(GameRunner&& other) = default;
    GameRunner& operator= (GameRunner&& other) = default;

private:
    std::vector<Player*> m_players;

    void checkObjectsAtOtherPlayers(int p_currentPlayerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room);
    CluedoObject* askObjectsAtOtherPlayer(int p_otherPlayerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room);
    void getObjectsToAsk(int p_currentPlayerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room);
    bool findUnknownObject(int p_currentPlayerIndex, std::vector<CluedoObject*>& p_cluedoObjectsToCheck, CluedoObject* p_foundObject);
    bool findKnownObject(int p_currentPlayerIndex, CluedoObject::CluedoObjectType p_objectType, CluedoObject* p_foundObject);
};

