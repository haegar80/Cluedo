#pragma once

#include "GameRunner.h"
#include "../Model/CluedoObject.h"
#include <vector>
#include <functional>
#include <memory>

class Player;
class PlayerSet;

class GameController
{
public:
    static GameController& getInstance();
    virtual ~GameController();

    void reset();
    void startGame();
    void askPlayer(int p_murderIndex, int p_weaponIndex, int p_roomIndex);

    void selectAndDistributeCluedoObjects();

    Player* createNewPlayer(std::string p_name, bool p_self);
    std::shared_ptr<PlayerSet> getPlayerSetOfCurrentPlayer();
    void setCurrentPlayer(int p_currentPlayerIndex);

    void registerPlayerUpdateCallback(std::function<void(void)> p_callback);

    std::vector<Player*>& getPlayers()
    {
        return m_players;
    }

    int getNumberOfPlayers()
    {
        return static_cast<int>(m_players.size());
    }

private:
    std::shared_ptr<GameRunner> m_gameRunner;
    std::vector<Player*> m_players;

    std::vector<CluedoObject*> m_murdersToDistribute;
    std::vector<CluedoObject*> m_weaponsToDistribute;
    std::vector<CluedoObject*> m_roomsToDistribute;

    CluedoObject* m_effectiveMurder{ nullptr };
    CluedoObject* m_effectiveWeapon{ nullptr };
    CluedoObject* m_effectiveRoom{ nullptr };

    int m_lastDistributedPlayerSetIndex{ 0 };

    std::vector<std::function<void(void)>> m_playerUpdateCallbacks;

    GameController() = default;
    GameController(const GameController& copy) = delete;
    GameController& operator= (const GameController& copy) = delete;

    std::shared_ptr<PlayerSet> createNewPlayerSet();

    void selectEffectiveMurderWeaponRoom();
    void addCluedoObjectsToDistribute(std::vector<CluedoObject*>& p_cluedoObjects, CluedoObject::CluedoObjectType p_type);

    void distributeCluedoObjects();
    void distributeCluedoObjects(std::vector<CluedoObject*>& p_cluedoObjects);
    void distributeMurders();
    void distributeWeapons();
    void distributeRooms();
};