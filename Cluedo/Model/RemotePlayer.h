#pragma once

#include "../Model/Player.h"
#if WIN32
#include <winsock2.h>
#endif

class RemotePlayer : public Player
{
public:
    RemotePlayer(const std::string& p_name, std::shared_ptr<PlayerSet> p_playerSet, SOCKET p_remoteSocket);
    RemotePlayer(const std::string& p_name, std::shared_ptr<PlayerSet> p_playerSet);
    virtual ~RemotePlayer() = default;
    RemotePlayer(const RemotePlayer& copy) = default;
    RemotePlayer& operator= (const RemotePlayer& copy) = default;
    RemotePlayer(RemotePlayer&& other) = default;
    RemotePlayer& operator= (RemotePlayer&& other) = default;

    SOCKET getRemoteSocket() {
        return m_remoteSocket;
    }

private:
    SOCKET m_remoteSocket;
};