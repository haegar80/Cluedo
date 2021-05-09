#pragma once

#include "GameRunner.h"
#include "../Model/CluedoObject.h"
#include "../Model/RemotePlayer.h"
#if WIN32
#include "../Network/TcpWinSocketClient.h"
#include "../Network/TcpWinSocketServer.h"
#endif
#include <vector>
#include <memory>

class PlayerSet;

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController& getInstance();
    virtual ~GameController();
    GameController(GameController const&) = delete;
    GameController& operator=(GameController const&) = delete;

    void reset();
    void startGame();
    void askPlayer();
    void askPlayer(int p_murderIndex, int p_weaponIndex, int p_roomIndex);
    bool tellSuspicion(int p_murderIndex, int p_weaponIndex, int p_roomIndex);
    bool shouldTellSuspicion();

    // Server functions
    void selectAndDistributeCluedoObjects();
    void sendPlayersListToClients();
    void sendCurrentPlayerIndexToClients();
#if WIN32
    void setTcpWinSocketServer(std::shared_ptr<TcpWinSocketServer> p_winSocketServer) {
        m_tcpWinSocketServer = p_winSocketServer;
        if (m_gameRunner) {
            m_gameRunner->setTcpWinSocketServer(p_winSocketServer);
        }
    }
#endif

    // Client functions
    void registerRemoteServerMessages(bool p_client);
#if WIN32
    void setTcpWinSocketClient(std::shared_ptr<TcpWinSocketClient> p_winSocketClient) {
        m_tcpWinSocketClient = p_winSocketClient;
    }
#endif

    Player* createNewPlayer(std::string p_name, Player::EPlayerType p_playerType);
    int getCurrentPlayerIndex();
    Player* getCurrentPlayer();
    void moveToNextPlayer();

    std::shared_ptr<GameRunner> getGameRunner() {
        return m_gameRunner;
    }

    std::vector<Player*>& getPlayers()
    {
        return m_players;
    }

    int getNumberOfPlayers()
    {
        return static_cast<int>(m_players.size());
    }

    signals:
    void gameController_ready();
    void remotePlayer_added();
    void playersList_updated();
    void currentPlayerIndex_updated();
    void allCluedoObjects_distributed();
    void showObject_requested(const QString& p_askedPlayer, const QString& p_murderString, const QString& p_weaponString, const QString& p_roomString);
    void askPlayerResponse_ready();

private:
    std::shared_ptr<GameRunner> m_gameRunner;
    std::vector<Player*> m_players;

    std::vector<CluedoObject*> m_murdersToDistribute;
    std::vector<CluedoObject*> m_weaponsToDistribute;
    std::vector<CluedoObject*> m_roomsToDistribute;

    CluedoObject* m_effectiveMurder{ nullptr };
    CluedoObject* m_effectiveWeapon{ nullptr };
    CluedoObject* m_effectiveRoom{ nullptr };

    bool m_gameEnd{ false };
    int m_lastDistributedPlayerSetIndex{ 0 };
    int m_currentPlayerIndexFromServer{ -1 };

#if WIN32
    std::shared_ptr<TcpWinSocketClient> m_tcpWinSocketClient;
    std::shared_ptr<TcpWinSocketServer> m_tcpWinSocketServer;
#endif

    GameController();

    std::shared_ptr<PlayerSet> createNewPlayerSet();
    void initPlayerSet(std::shared_ptr<PlayerSet> playerSet);

    Player* getSelfPlayer();
    int getSelfPlayerIndex();
    std::vector<RemotePlayer*> getRemotePlayers();
    RemotePlayer* createNewRemotePlayer(int p_indexNumber, std::string p_name, SOCKET p_remoteSocket);

    void selectEffectiveMurderWeaponRoom();
    void addCluedoObjectsToDistribute(std::vector<CluedoObject*>& p_cluedoObjects, CluedoObject::CluedoObjectType p_type);

    void distributeCluedoObjects();
    void distributeCluedoObjects(std::vector<CluedoObject*>& p_cluedoObjects);
    void distributeMurders();
    void distributeWeapons();
    void distributeRooms();
    void showObjectCallback(const std::string& p_askedPlayer, const std::string& p_murderString, const std::string& p_weaponString, const std::string& p_roomString);

    void receiveRemoteCluedoObject(const std::string& message);
    void receiveRemoteAllCluedoObjectsDistributed();
    void receiveRemotePlayersList(SOCKET p_sourceSocket, const std::string& message);
    void receiveRemoteCurrentPlayerIndex(const std::string& message);
    void receiveRemoteAskOtherPlayer(const std::string& message);
};