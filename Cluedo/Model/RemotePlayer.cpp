#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(const std::string& p_name, std::shared_ptr<PlayerSet> p_playerSet, SOCKET p_remoteSocket) : Player(p_name, p_playerSet, Player::PlayerType_Remote), m_remoteSocket(p_remoteSocket)
{
}

RemotePlayer::RemotePlayer(const std::string& p_name, std::shared_ptr<PlayerSet> p_playerSet) : Player(p_name, p_playerSet, Player::PlayerType_Remote)
{
}