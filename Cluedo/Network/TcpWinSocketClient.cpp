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
    m_serverSocket = INVALID_SOCKET;

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
    m_serverSocket = ::socket(m_addressInfo->ai_family, m_addressInfo->ai_socktype, m_addressInfo->ai_protocol);
    if (INVALID_SOCKET == m_serverSocket) {
        printf("Socket failed with error: %ld\n", WSAGetLastError());
        ::freeaddrinfo(m_addressInfo);
        ::WSACleanup();
        return false;
    }

    return true;
}

bool TcpWinSocketClient::connectToServer() {
    for (struct addrinfo* ptr = m_addressInfo; ptr != NULL; ptr = ptr->ai_next) {
        int socketResult = ::connect(m_serverSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (SOCKET_ERROR == socketResult) {
            ::closesocket(m_serverSocket);
            m_serverSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    ::freeaddrinfo(m_addressInfo);

    if (INVALID_SOCKET == m_serverSocket) {
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
    if (m_serverSocket) {
        ::closesocket(m_serverSocket);
    }
    ::WSACleanup();
}

void TcpWinSocketClient::sendData(const std::string& p_data) {
    constexpr size_t NumberOfLengthChars = 4;
    char bytes[NumberOfLengthChars];

    MessageHandler::getInstance().convertMessageLengthToCharArray(static_cast<int>(p_data.length()), bytes);
    std::stringstream dataWithLength;
    dataWithLength << bytes[3] << bytes[2] << bytes[1] << bytes[0] << p_data;
    int sendResult = ::send(m_serverSocket, dataWithLength.str().c_str(), static_cast<int>(dataWithLength.str().length()), 0);
    if (SOCKET_ERROR == sendResult) {
        printf("send failed with error: %d\n", WSAGetLastError());
        ::closesocket(m_serverSocket);
        ::WSACleanup();
    }
}

void TcpWinSocketClient::readDataThread() {
    while (m_readingActive)
    {
        int dataLength;
        bool dataLengthSuccessful = readDataLength(dataLength);
        if (dataLengthSuccessful) {
            char recvbuf[BufferLength];
            int readResult = ::recv(m_serverSocket, recvbuf, dataLength, 0);
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
        else {
            break;
        }
    }
}

bool TcpWinSocketClient::readDataLength(int& length) {
    bool readSuccessful = false;

    constexpr size_t NumberOfLengthChars = 4;
    char recvbufLength[NumberOfLengthChars];
    int readResultLength = ::recv(m_serverSocket, recvbufLength, NumberOfLengthChars, 0);

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