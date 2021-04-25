#include "TcpWinSocketClient.h"
#include "../Message/MessageHandler.h"
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <thread>

const std::string TcpWinSocketClient::m_port = "27015";

bool TcpWinSocketClient::init(std::string p_serverAddress) {
    m_clientSocket = INVALID_SOCKET;

    struct addrinfo hints;

    // Initialize Winsock
    WSADATA wsaData;
    int socketResult = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (0 != socketResult) {
        printf("WSAStartup failed with error: %d\n", socketResult);
        return false;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    socketResult = ::getaddrinfo(p_serverAddress.c_str(), m_port.c_str(), &hints, &m_addressInfo);
    if (0 != socketResult) {
        printf("getaddrinfo failed with error: %d\n", socketResult);
        ::WSACleanup();
        return false;
    }

    // Create a SOCKET for connecting to server
    m_clientSocket = ::socket(m_addressInfo->ai_family, m_addressInfo->ai_socktype, m_addressInfo->ai_protocol);
    if (INVALID_SOCKET == m_clientSocket) {
        printf("Socket failed with error: %ld\n", WSAGetLastError());
        ::freeaddrinfo(m_addressInfo);
        ::WSACleanup();
        return false;
    }

    return true;
}

bool TcpWinSocketClient::connectToServer() {
    for (struct addrinfo* ptr = m_addressInfo; ptr != NULL; ptr = ptr->ai_next) {
        int socketResult = ::connect(m_clientSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (SOCKET_ERROR == socketResult) {
            ::closesocket(m_clientSocket);
            m_clientSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    ::freeaddrinfo(m_addressInfo);

    if (INVALID_SOCKET == m_clientSocket) {
        printf("Unable to connect to server!\n");
        ::WSACleanup();
        return false;
    }

    m_readingActive = true;
    std::thread t(&TcpWinSocketClient::readDataThread, this);
    t.detach();

    return true;
}

void TcpWinSocketClient::shutdownSocket() {
    m_readingActive = false;
    if (m_clientSocket) {
        ::closesocket(m_clientSocket);
    }
    ::WSACleanup();
}

void TcpWinSocketClient::readDataThread() {
    while (m_readingActive)
    {
        int dataLength;
        bool dataLengthSuccessful = readDataLength(dataLength);
        if (dataLengthSuccessful) {
            char recvbuf[BufferLength];
            int readResult = ::recv(m_clientSocket, recvbuf, dataLength, 0);
            if (readResult > 0) {
                std::string message(recvbuf, readResult);
                MessageHandler::getInstance().handleMessage(message);
            }
            else if (0 == readResult) {
                printf("Connection closed\n");
            }
            else {
                printf("recv failed with error: %d\n", WSAGetLastError());
                shutdownSocket();
            }
        }
    }
}

bool TcpWinSocketClient::readDataLength(int& length) {
    bool readSuccessful = false;

    constexpr size_t NumberOfLengthChars = 4;
    char recvbufLength[NumberOfLengthChars];
    int readResultLength = ::recv(m_clientSocket, recvbufLength, NumberOfLengthChars, 0);

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
        shutdownSocket();
    }

    return readSuccessful;
}