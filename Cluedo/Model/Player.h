#pragma once

#include "PlayerSet.h"
#include <string>
#include <memory>

class Player
{
public:
    Player(const std::string& p_name, std::shared_ptr<PlayerSet> p_playerSet, bool p_self);
    virtual ~Player() = default;

    const std::string& getName()
    {
        return m_name;
    }

    std::shared_ptr<PlayerSet> getPlayerSet()
    {
        return m_playerSet;
    }

    bool getSelf()
    {
        return m_self;
    }

private:
    std::string m_name{ "" };
    std::shared_ptr<PlayerSet> m_playerSet;
    bool m_self{ false };

    Player(const Player& copy) = default;
    Player& operator= (const Player& copy) = default;
    Player(Player&& other) = default;
    Player& operator= (Player&& other) = default;
};