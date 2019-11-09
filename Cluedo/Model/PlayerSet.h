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

    std::vector<CluedoObject*>& getUnknownCluedoObjects()
    {
        return m_unknownCluedoObjects;
    }


    CluedoObject* getLastShownCluedoObject()
    {
        return m_lastShownCluedoObject;
    }

    void setLastShownCluedoObject(CluedoObject* p_lastShownCluedoObject)
    {
        m_lastShownCluedoObject = p_lastShownCluedoObject;
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
    std::vector<CluedoObject*> m_unknownCluedoObjects;

    CluedoObject* m_lastShownCluedoObject{ nullptr };
    bool m_shouldTellSuspicion{ false };

    void updateSuspicion();
};