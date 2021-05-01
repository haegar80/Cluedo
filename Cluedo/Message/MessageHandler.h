#pragma once

#include <functional>
#include <map>
#include <string>
#if WIN32
#include <winsock2.h>
#endif

class MessageHandler
{
public:
    static MessageHandler& getInstance();
    virtual ~MessageHandler() = default;
    MessageHandler(const MessageHandler& copy) = default;
    MessageHandler& operator= (const MessageHandler& copy) = default;
    MessageHandler(MessageHandler&& other) = default;
    MessageHandler& operator= (MessageHandler&& other) = default;

    void registerMessageHandler(int p_messageId, std::function<void(SOCKET, const std::string&)> p_messageHandlerFunction);
    bool handleMessage(SOCKET p_remoteSocket, std::string p_message);
    void convertMessageLengthToCharArray(int p_length, char* p_charArray);

private:
    std::map<int, std::function<void(SOCKET, const std::string&)>> m_messageHandlerCallbacks;

    MessageHandler() = default;
};

