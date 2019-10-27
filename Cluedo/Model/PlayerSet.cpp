#include "PlayerSet.h"
#include "CluedoObject.h"

PlayerSet::PlayerSet(int p_playerNumber) : m_playerNumber(p_playerNumber)
{
}

void PlayerSet::addCluedoObject(CluedoObject* p_cluedoObject)
{
    m_cluedoObjects.push_back(p_cluedoObject);
}