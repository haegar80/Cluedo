#include "TcpWinSocketServer.h"
#include "../GameManager/GameController.h"
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>

const std::string TcpWinSocketServer::m_port = "27015";

bool TcpWinSocketServer::init() { 
    m_serverSocket = INVALID_SOCKET;

    struct addrinfo* addressResult = nullptr;
    struct addrinfo hints;

    // Initialize Winsock
    WSADATA wsaData;
    int socketResult = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (0 != socketResult) {
        printf("WSAStartup failed with error: %d\n", socketResult);
        return false;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    socketResult = ::getaddrinfo(NULL, m_port.c_str(), &hints, &addressResult);
    if (0 != socketResult) {
        printf("getaddrinfo failed with error: %d\n", socketResult);
        ::WSACleanup();
        return false;
    }

    // Create a SOCKET for connecting to server
    m_serverSocket = ::socket(addressResult->ai_family, addressResult->ai_socktype, addressResult->ai_protocol);
    if (INVALID_SOCKET == m_serverSocket) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        ::freeaddrinfo(addressResult);
        ::WSACleanup();
        return false;
    }

    // Setup the TCP listening socket
    socketResult = ::bind(m_serverSocket, addressResult->ai_addr, (int)addressResult->ai_addrlen);
    if (SOCKET_ERROR == socketResult) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        ::freeaddrinfo(addressResult);
        ::closesocket(m_serverSocket);
        ::WSACleanup();
        return false;
    }

    ::freeaddrinfo(addressResult);

    return true;
}

bool TcpWinSocketServer::listenToClients() {
    int socketResult = ::listen(m_serverSocket, MaxConnectionQueue);
    if (SOCKET_ERROR == socketResult) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        ::closesocket(m_serverSocket);
        ::WSACleanup();
        return false;
    }

    // Enable non-blocking mode
    DWORD NonBlocking = 1;
    ::ioctlsocket(m_serverSocket, FIONBIO, &NonBlocking);

    printf("Listen to clients ready");

    while (!m_disableWaiting)
    {
        SOCKET clientSocket = ::accept(m_serverSocket, NULL, NULL);
        if (INVALID_SOCKET != clientSocket) {
            printf("Client connected!");
            m_clientSockets.push_back(clientSocket);

            emit remotePlayer_added();
        }
    }
    printf("Finished listening to clients!");

    return true;
}

void TcpWinSocketServer::shutdownSockets() {
    ::closesocket(m_serverSocket);

    for (SOCKET clientSocket : m_clientSockets) {
        int socketResult = ::shutdown(clientSocket, SD_SEND);
        ::closesocket(clientSocket);
    }
    ::WSACleanup();
}

void TcpWinSocketServer::disableWaitingForClients() {
    m_disableWaiting = true;
}

void TcpWinSocketServer::sendData(SOCKET p_socket, const std::string& p_data) {
    int remainingLength = static_cast<int>(p_data.length());
    constexpr size_t NumberOfLengthChars = 4;
    char bytes[NumberOfLengthChars];

    int divisor = 1000;
    for (int i = 3; i >= 0; i--) {
        int lengthPart = remainingLength / divisor;
        bytes[i] = static_cast<char>(lengthPart) + '0';
        remainingLength -= lengthPart * divisor;
        divisor /= 10;
    }

    std::stringstream dataWithLength;
    dataWithLength << bytes[3] << bytes[2] << bytes[1] << bytes[0] << p_data;
    int sendResult = ::send(p_socket, dataWithLength.str().c_str(), static_cast<int>(dataWithLength.str().length()), 0);
    if (SOCKET_ERROR == sendResult) {
        printf("send failed with error: %d\n", WSAGetLastError());
        ::closesocket(p_socket);
        ::WSACleanup();
    }
}