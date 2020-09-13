#pragma once

#include <winsock2.h>
#include <string>
#include <vector>

class TcpWinSocketServer
{
public:
    TcpWinSocketServer() = default;
    virtual ~TcpWinSocketServer() = default;
    TcpWinSocketServer(const TcpWinSocketServer& copy) = delete;
    TcpWinSocketServer& operator= (const TcpWinSocketServer& copy) = delete;

    bool init();
    bool listenToClients(int p_numberOfExpectedClients);
    void shutdownSockets();
    void disableWaitingForClients();

private:
    static constexpr int BufferLength = 512;
    static const std::string m_port;
    SOCKET m_serverSocket;
    bool m_disableWaiting{ false };
    std::vector<SOCKET> m_clientSockets;
};

