#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(std::shared_ptr<PlayerSet> p_playerSet) : Player("Remote player", p_playerSet, Player::PlayerType_Remote)
{
}