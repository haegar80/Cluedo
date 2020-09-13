#pragma once

#include "GameRunner.h"
#include "../Model/CluedoObject.h"
#include "../Model/RemotePlayer.h"
#include <vector>
#include <functional>
#include <memory>

class PlayerSet;

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController& getInstance();
    virtual ~GameController();

    void reset();
    void startGame();
    void askPlayer();
    void askPlayer(int p_murderIndex, int p_weaponIndex, int p_roomIndex);
    bool tellSuspicion(int p_murderIndex, int p_weaponIndex, int p_roomIndex);
    bool shouldTellSuspicion();

    void selectAndDistributeCluedoObjects();

    RemotePlayer* createNewRemotePlayer(std::string p_name);
    Player* createNewPlayer(std::string p_name, Player::EPlayerType p_playerType);
    Player* getCurrentPlayer();

    void setCurrentPlayerIndex(int p_currentPlayerIndex)
    {
        m_currentPlayerIndex = p_currentPlayerIndex;
    }

    void registerPlayerUpdateCallback(std::function<void(void)> p_callback);

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
    int m_currentPlayerIndex{ -1 };
    int m_lastDistributedPlayerSetIndex{ 0 };

    std::vector<std::function<void(void)>> m_playerUpdateCallbacks;

    GameController();
    GameController(const GameController& copy) = delete;
    GameController& operator= (const GameController& copy) = delete;

    std::shared_ptr<PlayerSet> createNewPlayerSet();
    void initPlayerSet(std::shared_ptr<PlayerSet> playerSet);

    void selectEffectiveMurderWeaponRoom();
    void addCluedoObjectsToDistribute(std::vector<CluedoObject*>& p_cluedoObjects, CluedoObject::CluedoObjectType p_type);

    void distributeCluedoObjects();
    void distributeCluedoObjects(std::vector<CluedoObject*>& p_cluedoObjects);
    void distributeMurders();
    void distributeWeapons();
    void distributeRooms();
};