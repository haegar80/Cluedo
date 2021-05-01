#include "TcpWinSocketServer.h"
#include "../GameManager/GameController.h"
#include "../Message/MessageHandler.h"
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <thread>

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

    printf("Listen to clients ready");

    while (!m_disableWaiting)
    {
        SOCKET clientSocket = ::accept(m_serverSocket, NULL, NULL);
        if (INVALID_SOCKET != clientSocket) {
            printf("Client connected!");
            m_clientSockets.push_back(clientSocket);

            m_readingActive = true;
            std::thread t(&TcpWinSocketServer::readDataThread, this, clientSocket);
            t.detach();

            emit remotePlayer_added();
        }
    }
    printf("Finished listening to clients!");

    return true;
}

void TcpWinSocketServer::shutdownSockets() {
    m_readingActive = false;

    ::closesocket(m_serverSocket);

    for (SOCKET clientSocket : m_clientSockets) {
        int socketResult = ::shutdown(clientSocket, SD_SEND);
        ::closesocket(clientSocket);
    }
    ::WSACleanup();
}

void TcpWinSocketServer::shutdownSocket(SOCKET p_clientSocket) {
    int socketResult = ::shutdown(p_clientSocket, SD_SEND);
    ::closesocket(p_clientSocket);
}

void TcpWinSocketServer::disableWaitingForClients() {
    m_disableWaiting = true;
}

void TcpWinSocketServer::sendData(SOCKET p_socket, const std::string& p_data) {
    constexpr size_t NumberOfLengthChars = 4;
    char bytes[NumberOfLengthChars];

    MessageHandler::getInstance().convertMessageLengthToCharArray(static_cast<int>(p_data.length()), bytes);
    std::stringstream dataWithLength;
    dataWithLength << bytes[3] << bytes[2] << bytes[1] << bytes[0] << p_data;
    int sendResult = ::send(p_socket, dataWithLength.str().c_str(), static_cast<int>(dataWithLength.str().length()), 0);
    if (SOCKET_ERROR == sendResult) {
        printf("send failed with error: %d\n", WSAGetLastError());
        ::closesocket(p_socket);
        ::WSACleanup();
    }
}

void TcpWinSocketServer::readDataThread(SOCKET p_clientSocket) {
    while (m_readingActive)
    {
        int dataLength;
        bool dataLengthSuccessful = readDataLength(p_clientSocket, dataLength);
        if (dataLengthSuccessful) {
            char recvbuf[BufferLength];
            int readResult = ::recv(p_clientSocket, recvbuf, dataLength, 0);
            if (readResult > 0) {
                std::string message(recvbuf, readResult);
                MessageHandler::getInstance().handleMessage(p_clientSocket, message);
            }
            else if (0 == readResult) {
                printf("Connection closed\n");
                break;
            }
            else {
                printf("recv failed with error: %d\n", WSAGetLastError());
                shutdownSocket(p_clientSocket);
                break;
            }
        }
        else {
            break;
        }
    }
}

bool TcpWinSocketServer::readDataLength(SOCKET p_clientSocket, int& length) {
    bool readSuccessful = false;

    constexpr size_t NumberOfLengthChars = 4;
    char recvbufLength[NumberOfLengthChars];
    int readResultLength = ::recv(p_clientSocket, recvbufLength, NumberOfLengthChars, 0);

    if (readResultLength > 0) {
        std::string stringLength(recvbufLength, readResultLength);
        std::stringstream ssLength;
        ssLength << stringLength;
        ssLength >> length;
        readSuccessful = true;
    }
    else if (0 == readResultLength) {
        printf("Connection closed\n");
    }
    else {
        printf("recv failed with error: %d\n", WSAGetLastError());
        shutdownSocket(p_clientSocket);
    }

    return readSuccessful;
}