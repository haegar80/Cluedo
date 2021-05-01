#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(SOCKET p_clientSocket, std::shared_ptr<PlayerSet> p_playerSet) : Player("Remote player", p_playerSet, Player::PlayerType_Remote), m_clientSocket(p_clientSocket)
{
}

RemotePlayer::RemotePlayer(const std::string& p_name, std::shared_ptr<PlayerSet> p_playerSet) : Player(p_name, p_playerSet, Player::PlayerType_Remote)
{
}