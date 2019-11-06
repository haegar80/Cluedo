#pragma once

#include "../Model/CluedoObject.h"
#include <vector>
#include <functional>

class Player;
class PlayerSet;

class GameController
{
public:
    static GameController& getInstance();
    virtual ~GameController();

    void reset();
    void startGameRounds();

    void selectAndDistributeCluedoObjects();

    Player* createNewPlayer(std::string p_name);
    PlayerSet* createNewPlayerSet();

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
    std::vector<Player*> m_players;
    std::vector<PlayerSet*> m_playerSets;

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
    GameController(GameController&& other) = delete;
    GameController& operator= (GameController&& other) = delete;

    void selectEffectiveMurderWeaponRoom();
    void addCluedoObjectsToDistribute(std::vector<CluedoObject*>& p_cluedoObjects, CluedoObject::CluedoObjectType p_type);

    void distributeCluedoObjects();
    void distributeCluedoObjects(std::vector<CluedoObject*>& p_cluedoObjects);
    void distributeMurders();
    void distributeWeapons();
    void distributeRooms();

    int generateRandomNumber(int p_minNumber, int p_maxNumber);
};