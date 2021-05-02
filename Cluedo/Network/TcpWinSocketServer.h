#pragma once

#include <winsock2.h>
#include <atomic>
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
    bool listenToClients();
    void shutdownSockets();
    void shutdownSocket(SOCKET p_clientSocket);
    void disableWaitingForClients();
    void sendData(SOCKET p_socket, const std::string& p_data);

    std::vector<SOCKET>& getClientSockets()
    {
        return m_clientSockets;
    }

private:
    static constexpr int MaxConnectionQueue = 5;
    static constexpr int BufferLength = 512;
    static const std::string m_port;
    SOCKET m_serverSocket;
    std::atomic<bool> m_disableWaiting{ false };
    std::atomic<bool> m_readingActive{ false };
    std::vector<SOCKET> m_clientSockets;

    void readDataThread(SOCKET p_clientSocket);
    bool readDataLength(SOCKET p_clientSocket, int& length);
};

