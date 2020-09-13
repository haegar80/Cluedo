#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(const std::string& p_name, std::shared_ptr<PlayerSet> p_playerSet) : Player(p_name, p_playerSet, Player::PlayerType_Remote)
{
}

void RemotePlayer::setClientSocket(SOCKET p_clientSocket) {
    m_clientSocket = p_clientSocket;
}