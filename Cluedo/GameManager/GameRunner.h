#pragma once

#include "CluedoObjectLoader.h"
#if WIN32
#include "../Network/TcpWinSocketClient.h"
#include "../Network/TcpWinSocketServer.h"
#endif
#include <memory>
#include <functional>
#include <vector>

class Player;
class CluedoObject;

class GameRunner
{
public:
    GameRunner(std::vector<Player*>& p_players);
    virtual ~GameRunner() = default;

    GameRunner(const GameRunner& copy) = default;
    GameRunner& operator= (const GameRunner& copy) = default;
    GameRunner(GameRunner&& other) = default;
    GameRunner& operator= (GameRunner&& other) = default;

    void startGame();

    void askPlayer();
    void askPlayer(CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room);
    void askPlayerResponse(bool p_objectCouldBeShown, CluedoObject* p_cluedoObject);
    void moveToNextPlayer();

    void registerShowObjectCallback(std::function<void(int, int, int)> p_callback) {
        m_showObjectCallback = p_callback;
    }

    void registerObjectShownCallback(std::function<void()> p_callback) {
        m_objectShownCallback = p_callback;
    }

    void registerNoObjectCanBeShownCallback(std::function<void()> p_callback) {
        m_noObjectCanBeShownCallback = p_callback;
    }

    void registerAskPlayerResponseInformNotInvolvedServerCallback(std::function<void()> p_callback) {
        m_askPlayerResponseInformNotInvolvedServerCallback = p_callback;
    }

    int getCurrentPlayerIndex() {
        return m_currentPlayerIndex;
    }

#if WIN32
    void setTcpWinSocketServer(std::shared_ptr<TcpWinSocketServer> p_winSocketServer) {
        m_tcpWinSocketServer = p_winSocketServer;
    }
#endif

private:
    int m_currentPlayerIndex{ -1 };
    int m_lastAskedPlayerIndex{ -1 };
    std::vector<Player*> m_players;

    std::function<void(int, int, int)> m_showObjectCallback;
    std::function<void()> m_objectShownCallback;
    std::function<void()> m_noObjectCanBeShownCallback;
    std::function<void()> m_askPlayerResponseInformNotInvolvedServerCallback;

#if WIN32
    std::shared_ptr<TcpWinSocketServer> m_tcpWinSocketServer;
#endif

    void askPlayerResponseWithShownObject(CluedoObject* p_cluedoObject);
    void askPlayerResponseWithoutShownObject();
    void handleNoObjectCanBeShown();
    void askPlayerResponseInformNotInvolvedPlayer();

    CluedoObject* askObjectsAtComputer(CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room);

    void getObjectsToAsk(CluedoObject** p_murder, CluedoObject** p_weapon, CluedoObject** p_room);
    void findUnknownObject(std::vector<CluedoObject*>& p_cluedoObjectsToCheck, CluedoObject** p_foundObject);
};

