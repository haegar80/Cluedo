#pragma once

#include <vector>

class Player;
class CluedoObject;

class GameRunner
{
public:
    GameRunner(std::vector<Player*>& p_players);
    virtual ~GameRunner() = default;

    void askPlayer(int p_murderIndex, int p_weaponIndex, int p_roomIndex);
    void setCurrentPlayer(int p_currentPlayerIndex);

    GameRunner(const GameRunner& copy) = default;
    GameRunner& operator= (const GameRunner& copy) = default;
    GameRunner(GameRunner&& other) = default;
    GameRunner& operator= (GameRunner&& other) = default;

private:
    std::vector<Player*> m_players;
    int m_currentPlayerIndex{ -1 };

    void checkObjectAtOtherPlayer(CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room);
};

