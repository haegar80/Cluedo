#pragma once

#include <winsock2.h>
#include <atomic>
#include <string>

class TcpWinSocketClient
{
public:
    TcpWinSocketClient() = default;
    virtual ~TcpWinSocketClient() = default;
    TcpWinSocketClient(const TcpWinSocketClient& copy) = delete;
    TcpWinSocketClient& operator= (const TcpWinSocketClient& copy) = delete;

    bool init(std::string p_serverAddress);
    bool connectToServer();
    void shutdownSocket();

private:
    static constexpr int BufferLength = 512;
    static const std::string m_port;
    SOCKET m_clientSocket;
    struct addrinfo* m_addressInfo{ nullptr };
    std::atomic<bool> m_readingActive{ false };

    void readDataThread();
};

