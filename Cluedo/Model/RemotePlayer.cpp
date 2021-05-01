#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(SOCKET p_clientSocket, std::shared_ptr<PlayerSet> p_playerSet) : Player("Remote player", p_playerSet, Player::PlayerType_Remote), m_clientSocket(p_clientSocket)
{
}

RemotePlayer::RemotePlayer(std::shared_ptr<PlayerSet> p_playerSet) : Player("Remote player", p_playerSet, Player::PlayerType_Remote)
{
}