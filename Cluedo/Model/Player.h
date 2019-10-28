#pragma once

#include <string>

class Player
{
public:
    Player(std::string p_name);
    virtual ~Player() = default;

    const std::string& getName()
    {
        return m_name;
    }

private:
    std::string m_name{ "" };

    Player(const Player& copy) = default;
    Player& operator= (const Player& copy) = default;
    Player(Player&& other) = default;
    Player& operator= (Player&& other) = default;
};