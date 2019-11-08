#pragma once

#include <vector>

class Player;

class GameRunner
{
public:
    GameRunner(std::vector<Player*>& p_players);
    virtual ~GameRunner() = default;

    void askPlayer(int p_murderIndex, int p_weaponIndex, int p_roomIndex);

    void setCurrentPlayer(Player* p_currentPlayer)
    {
        m_currentPlayer = p_currentPlayer;
    }

    GameRunner(const GameRunner& copy) = default;
    GameRunner& operator= (const GameRunner& copy) = default;
    GameRunner(GameRunner&& other) = default;
    GameRunner& operator= (GameRunner&& other) = default;

private:
    std::vector<Player*> m_players;
    Player* m_currentPlayer{ nullptr };
};

