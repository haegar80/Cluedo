#pragma once

#include <vector>

class CluedoObject;

class PlayerSet
{
public:
    PlayerSet(int p_playerNumber);
    virtual ~PlayerSet() = default;

    void addCluedoObject(CluedoObject* p_cluedoObject);

    int getNumberOfCluedoObjects()
    {
        return static_cast<int>(m_cluedoObjects.size());
    }

    std::vector<CluedoObject*>& getCluedoObjects()
    {
        return m_cluedoObjects;
    }

private:
    int m_playerNumber{ 0 };
    std::vector<CluedoObject*> m_cluedoObjects;

    PlayerSet(const PlayerSet& copy) = default;
    PlayerSet& operator= (const PlayerSet& copy) = default;
    PlayerSet(PlayerSet&& other) = default;
    PlayerSet& operator= (PlayerSet&& other) = default;
};