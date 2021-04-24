#pragma once

#include "CluedoObjectLoader.h"
#if WIN32
#include "../Network/TcpWinSocketClient.h"
#include "../Network/TcpWinSocketServer.h"
#endif
#include <memory>
#include <vector>

class Player;
class CluedoObject;

class GameRunner
{
public:
    GameRunner(std::vector<Player*>& p_players);
    virtual ~GameRunner() = default;

    void askPlayer(int p_currentPlayerIndex);
    void askPlayer(int p_currentPlayerIndex, int p_murderIndex, int p_weaponIndex, int p_roomIndex);

    GameRunner(const GameRunner& copy) = default;
    GameRunner& operator= (const GameRunner& copy) = default;
    GameRunner(GameRunner&& other) = default;
    GameRunner& operator= (GameRunner&& other) = default;

#if WIN32
    void setTcpWinSocketServer(std::shared_ptr<TcpWinSocketServer> p_winSocketServer) {
        m_tcpWinSocketServer = p_winSocketServer;
    }
#endif

private:
    std::vector<Player*> m_players;

#if WIN32
    std::shared_ptr<TcpWinSocketServer> m_tcpWinSocketServer;
#endif

    void checkObjectsAtOtherPlayers(int p_currentPlayerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room);
    CluedoObject* askObjectsAtOtherPlayer(int p_otherPlayerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room);

    void getObjectsToAsk(int p_currentPlayerIndex, CluedoObject** p_murder, CluedoObject** p_weapon, CluedoObject** p_room);
    void findUnknownObject(int p_currentPlayerIndex, std::vector<CluedoObject*>& p_cluedoObjectsToCheck, CluedoObject** p_foundObject);
};

