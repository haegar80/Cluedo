#pragma once

#include "PlayerSet.h"
#include <string>
#include <memory>

class Player
{
public:
    enum EPlayerType {
        PlayerType_Undefined = 0,
        PlayerType_SelfServer = 1,
        PlayerType_SelfClient = 2,
        PlayerType_Remote = 3,
        PlayerType_Computer = 4
    };

    Player(const std::string& p_name, std::shared_ptr<PlayerSet> p_playerSet, EPlayerType p_playerType);
    Player(const Player& copy) = default;
    Player& operator= (const Player& copy) = default;
    Player(Player&& other) = default;
    Player& operator= (Player&& other) = default;

    virtual ~Player() = default;

    const std::string& getName()
    {
        return m_name;
    }

    std::shared_ptr<PlayerSet> getPlayerSet()
    {
        return m_playerSet;
    }

    EPlayerType getPlayerType()
    {
        return m_playerType;
    }

    void setName(const std::string& p_name) {
        m_name = p_name;
    }

protected:
    std::string m_name{ "" };

private:
    std::shared_ptr<PlayerSet> m_playerSet;
    
    EPlayerType m_playerType{ PlayerType_Undefined };
};