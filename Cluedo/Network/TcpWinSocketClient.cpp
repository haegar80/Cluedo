#include "TcpWinSocketClient.h"
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>

const std::string TcpWinSocketClient::m_port = "27015";

bool TcpWinSocketClient::init(std::string p_serverAddress) {
    m_clientSocket = INVALID_SOCKET;

    struct addrinfo hints;

    // Initialize Winsock
    WSADATA wsaData;
    int socketResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (0 != socketResult) {
        printf("WSAStartup failed with error: %d\n", socketResult);
        return false;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    socketResult = getaddrinfo(p_serverAddress.c_str(), m_port.c_str(), &hints, &m_addressInfo);
    if (0 != socketResult) {
        printf("getaddrinfo failed with error: %d\n", socketResult);
        WSACleanup();
        return false;
    }

    // Create a SOCKET for connecting to server
    m_clientSocket = socket(m_addressInfo->ai_family, m_addressInfo->ai_socktype, m_addressInfo->ai_protocol);
    if (INVALID_SOCKET == m_clientSocket) {
        printf("Socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(m_addressInfo);
        WSACleanup();
        return false;
    }

    return true;
}

bool TcpWinSocketClient::connectToServer() {
    for (struct addrinfo* ptr = m_addressInfo; ptr != NULL; ptr = ptr->ai_next) {
        int socketResult = connect(m_clientSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (SOCKET_ERROR == socketResult) {
            closesocket(m_clientSocket);
            m_clientSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(m_addressInfo);

    if (INVALID_SOCKET == m_clientSocket) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return false;
    }

    return true;
}