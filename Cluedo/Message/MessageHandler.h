#pragma once

#include <functional>
#include <map>
#include <string>

class MessageHandler
{
public:
    static MessageHandler& getInstance();
    virtual ~MessageHandler() = default;
    MessageHandler(const MessageHandler& copy) = default;
    MessageHandler& operator= (const MessageHandler& copy) = default;
    MessageHandler(MessageHandler&& other) = default;
    MessageHandler& operator= (MessageHandler&& other) = default;

    void registerMessageHandler(int p_messageId, std::function<void(const std::string&)> p_messageHandlerFunction);
    bool handleMessage(std::string p_message);
    void convertMessageLengthToCharArray(int p_length, char* p_charArray);

private:
    std::map<int, std::function<void(const std::string&)>> m_messageHandlerCallbacks;

    MessageHandler() = default;
};

