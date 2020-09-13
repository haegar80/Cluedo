#pragma once

#include <QObject>
#include <winsock2.h>
#include <string>
#include <vector>

class TcpWinSocketServer : public QObject
{
    Q_OBJECT
public:
    TcpWinSocketServer() = default;
    virtual ~TcpWinSocketServer() = default;
    TcpWinSocketServer(const TcpWinSocketServer& copy) = delete;
    TcpWinSocketServer& operator= (const TcpWinSocketServer& copy) = delete;

    bool init();
    bool listenToClients();
    void shutdownSockets();
    void disableWaitingForClients();

signals:
    void remotePlayer_added();

private:
    static constexpr int MaxConnectionQueue = 5;
    static constexpr int BufferLength = 512;
    static const std::string m_port;
    SOCKET m_serverSocket;
    bool m_disableWaiting{ false };
    std::vector<SOCKET> m_clientSockets;
};

