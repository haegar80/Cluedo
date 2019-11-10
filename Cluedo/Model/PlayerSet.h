#pragma once

#include <vector>
#include <map>

class CluedoObject;

class PlayerSet
{
public:
    PlayerSet(int p_playerNumber);
    virtual ~PlayerSet() = default;

    void addCluedoObject(CluedoObject* p_cluedoObject);
    void addCluedoObjectFromOtherPlayers(int p_playerIndex, CluedoObject* p_cluedoObject);
    void addMissingCluedoObjectsAtOtherPlayers(int p_playerIndex, CluedoObject* p_cluedoObject);
    void addPlayerIndexWithNoShownCluedoObjects(int p_playerIndex);
    void resetPlayerIndicesWithNoShownCluedoObjects();

    void addUnknownCluedoObjects(CluedoObject* p_cluedoObject);
    void removeUnknownCluedoObjects(CluedoObject* p_cluedoObject);

    int getNumberOfCluedoObjects()
    {
        return static_cast<int>(m_cluedoObjects.size());
    }

    std::vector<CluedoObject*>& getCluedoObjects()
    {
        return m_cluedoObjects;
    }

    std::multimap<int, CluedoObject*>& getCluedoObjectsFromOtherPlayers()
    {
        return m_cluedoObjectsFromOtherPlayers;
    }

    std::multimap<int, CluedoObject*>& getMissingCluedoObjectsAtOtherPlayers()
    {
        return m_missingCluedoObjectsAtOtherPlayers;
    }

    std::vector<int>& getPlayerIndicesWithNoShownCluedoObjects()
    {
        return m_playerIndicesWithNoShownCluedoObjects;
    }

    std::vector<CluedoObject*>& getUnknownCluedoObjects()
    {
        return m_unknownCluedoObjects;
    }

    int getLastPlayerIndexWhoShowedCluedoObject()
    {
        return m_lastPlayerIndexWhoShowedCluedoObject;
    }

    void setLastPlayerIndexWhoShowedCluedoObject(int p_playerIndex)
    {
        m_lastPlayerIndexWhoShowedCluedoObject = p_playerIndex;
    }

    CluedoObject* getLastShownCluedoObject()
    {
        return m_lastShownCluedoObject;
    }

    void setLastShownCluedoObject(CluedoObject* p_lastShownCluedoObject)
    {
        m_lastShownCluedoObject = p_lastShownCluedoObject;
    }

    CluedoObject* getLastAskedMurder()
    {
        return m_lastAskedMurder;
    }

    void setLastAskedMurder(CluedoObject* p_lastAskedMurder)
    {
        m_lastAskedMurder = p_lastAskedMurder;
    }

    CluedoObject* getLastAskedWeapon()
    {
        return m_lastAskedWeapon;
    }

    void setLastAskedWeapon(CluedoObject* p_lastShownCluedoObject)
    {
        m_lastAskedWeapon = p_lastShownCluedoObject;
    }

    CluedoObject* getLastAskedRoom()
    {
        return m_lastAskedRoom;
    }

    void setLastAskedRoom(CluedoObject* p_lastAskedRoom)
    {
        m_lastAskedRoom = p_lastAskedRoom;
    }

    bool getShouldTellSuspicion()
    {
        return m_shouldTellSuspicion;
    }

    PlayerSet(const PlayerSet& copy) = default;
    PlayerSet& operator= (const PlayerSet& copy) = default;
    PlayerSet(PlayerSet&& other) = default;
    PlayerSet& operator= (PlayerSet&& other) = default;

private:
    int m_playerNumber{ 0 };
    std::vector<CluedoObject*> m_cluedoObjects;
    std::multimap<int, CluedoObject*> m_cluedoObjectsFromOtherPlayers;
    std::multimap<int, CluedoObject*> m_missingCluedoObjectsAtOtherPlayers;
    std::vector<int> m_playerIndicesWithNoShownCluedoObjects;
    std::vector<CluedoObject*> m_unknownCluedoObjects;

    int m_lastPlayerIndexWhoShowedCluedoObject{ -1 };
    CluedoObject* m_lastShownCluedoObject{ nullptr };
    CluedoObject* m_lastAskedMurder{ nullptr };
    CluedoObject* m_lastAskedWeapon{ nullptr };
    CluedoObject* m_lastAskedRoom{ nullptr };

    bool m_shouldTellSuspicion{ false };

    void updateSuspicion();
};