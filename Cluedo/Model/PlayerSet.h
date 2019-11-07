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
    void addCluedoObjectFromOtherPlayer(const std::string& p_playerName, CluedoObject* p_cluedoObject);

    int getNumberOfCluedoObjects()
    {
        return static_cast<int>(m_cluedoObjects.size());
    }

    std::vector<CluedoObject*>& getCluedoObjects()
    {
        return m_cluedoObjects;
    }

    PlayerSet(const PlayerSet& copy) = default;
    PlayerSet& operator= (const PlayerSet& copy) = default;
    PlayerSet(PlayerSet&& other) = default;
    PlayerSet& operator= (PlayerSet&& other) = default;

private:
    int m_playerNumber{ 0 };
    std::vector<CluedoObject*> m_cluedoObjects;
    std::map<const std::string, CluedoObject*> m_cluedoObjectsFromOtherPlayers;
};