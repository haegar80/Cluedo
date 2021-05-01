#include "MessageHandler.h"
#include <sstream>

MessageHandler& MessageHandler::getInstance()
{
    static MessageHandler instance;
    return instance;
}

void MessageHandler::registerMessageHandler(int p_messageId, std::function<void(SOCKET, const std::string&)> p_messageHandlerFunction) {
    m_messageHandlerCallbacks.insert(std::make_pair(p_messageId, p_messageHandlerFunction));
}

bool MessageHandler::handleMessage(SOCKET p_remoteSocket, std::string p_message) {
    printf("Message received: %s\n", p_message.c_str());

    bool handledMessage = false;

    constexpr std::size_t ExpectedDelimiterPos = 3;
    std::size_t delimiterPos = p_message.find(":");
    if (std::string::npos != delimiterPos && ExpectedDelimiterPos == delimiterPos) {
        int commandId;
        std::stringstream ss;
        ss << p_message.substr(0, ExpectedDelimiterPos);
        ss >> commandId;
        std::string payload = p_message.substr(ExpectedDelimiterPos + 1);
        auto itFound = m_messageHandlerCallbacks.find(commandId);
        if (m_messageHandlerCallbacks.end() != itFound) {
            itFound->second(p_remoteSocket, payload);
        }
    }

    return handledMessage;
}

void MessageHandler::convertMessageLengthToCharArray(int p_length, char* p_charArray) {
    constexpr size_t NumberOfLengthChars = 4;

    int divisor = 1000;
    for (int i = 3; i >= 0; i--) {
        int lengthPart = p_length / divisor;
        p_charArray[i] = static_cast<char>(lengthPart) + '0';
        p_length -= lengthPart * divisor;
        divisor /= 10;
    }
}