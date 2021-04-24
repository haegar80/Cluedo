#pragma once

#include "../Model/Player.h"
#include <winsock2.h>

class RemotePlayer : public Player
{
public:
    RemotePlayer(std::shared_ptr<PlayerSet> p_playerSet);
    virtual ~RemotePlayer() = default;
    RemotePlayer(const RemotePlayer& copy) = default;
    RemotePlayer& operator= (const RemotePlayer& copy) = default;
    RemotePlayer(RemotePlayer&& other) = default;
    RemotePlayer& operator= (RemotePlayer&& other) = default;

    void setClientSocket(SOCKET p_clientSocket) {
        m_clientSocket = p_clientSocket;
    }
     

private:
    SOCKET m_clientSocket;
};