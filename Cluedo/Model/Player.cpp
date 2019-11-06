#include "Player.h"

Player::Player(const std::string& p_name, std::shared_ptr<PlayerSet> p_playerSet) : m_name(p_name), m_playerSet(p_playerSet)
{
}