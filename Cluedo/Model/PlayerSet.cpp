#include "PlayerSet.h"
#include "CluedoObject.h"

PlayerSet::PlayerSet(int p_playerNumber) : m_playerNumber(p_playerNumber)
{
}

std::vector<CluedoObject*> PlayerSet::getMurders() {
    std::vector<CluedoObject*> murders;

    for (CluedoObject* cluedoObject : m_cluedoObjects) {
        if (CluedoObject::Murder == cluedoObject->getCluedoObjectType()) {
            murders.push_back(cluedoObject);
        }
    }

    return murders;
}

std::vector<CluedoObject*> PlayerSet::getWeapons() {
    std::vector<CluedoObject*> weapons;

    for (CluedoObject* cluedoObject : m_cluedoObjects) {
        if (CluedoObject::Weapon == cluedoObject->getCluedoObjectType()) {
            weapons.push_back(cluedoObject);
        }
    }

    return weapons;
}

std::vector<CluedoObject*> PlayerSet::getRooms() {
    std::vector<CluedoObject*> rooms;

    for (CluedoObject* cluedoObject : m_cluedoObjects) {
        if (CluedoObject::Room == cluedoObject->getCluedoObjectType()) {
            rooms.push_back(cluedoObject);
        }
    }

    return rooms;
}

void PlayerSet::addCluedoObject(CluedoObject* p_cluedoObject)
{
    m_cluedoObjects.push_back(p_cluedoObject);
    removeUnknownCluedoObjects(p_cluedoObject);
}

void PlayerSet::addCluedoObjectFromOtherPlayers(int p_playerIndex, CluedoObject* p_cluedoObject)
{
    m_cluedoObjectsFromOtherPlayers.insert(std::make_pair(p_playerIndex, p_cluedoObject));
    removeUnknownCluedoObjects(p_cluedoObject);
}

void PlayerSet::addMissingCluedoObjectsAtOtherPlayers(int p_playerIndex, CluedoObject* p_cluedoObject)
{
    m_missingCluedoObjectsAtOtherPlayers.insert(std::make_pair(p_playerIndex, p_cluedoObject));
}

void PlayerSet::addPlayerIndexWithNoShownCluedoObjects(int p_playerIndex)
{
    m_playerIndicesWithNoShownCluedoObjects.push_back(p_playerIndex);
}

void PlayerSet::resetPlayerIndicesWithNoShownCluedoObjects()
{
    m_playerIndicesWithNoShownCluedoObjects.clear();
}

void PlayerSet::addUnknownCluedoObjects(CluedoObject* p_cluedoObject)
{
    m_unknownCluedoObjects.push_back(p_cluedoObject);
}

void PlayerSet::removeUnknownCluedoObjects(CluedoObject* p_cluedoObject)
{
    auto it = std::find(m_unknownCluedoObjects.begin(), m_unknownCluedoObjects.end(), p_cluedoObject);
    if (m_unknownCluedoObjects.end() != it)
    {
        m_unknownCluedoObjects.erase(it);
    }
    updateSuspicion();
}

void PlayerSet::updateSuspicion()
{
    constexpr int MinimumUnknownObjects = 1;

    int numberOfUnknownMurders = std::count_if(
        m_unknownCluedoObjects.begin(),
        m_unknownCluedoObjects.end(),
        [](CluedoObject* vectorObject) {return CluedoObject::Murder == vectorObject->getCluedoObjectType(); });

    int numberOfUnknownWeapons = std::count_if(
        m_unknownCluedoObjects.begin(),
        m_unknownCluedoObjects.end(),
        [](CluedoObject* vectorObject) {return CluedoObject::Weapon == vectorObject->getCluedoObjectType(); });

    int numberOfUnknownRooms = std::count_if(
        m_unknownCluedoObjects.begin(),
        m_unknownCluedoObjects.end(),
        [](CluedoObject* vectorObject) {return CluedoObject::Room == vectorObject->getCluedoObjectType(); });

    if ((MinimumUnknownObjects == numberOfUnknownMurders) && (MinimumUnknownObjects == numberOfUnknownWeapons) && (MinimumUnknownObjects == numberOfUnknownRooms))
    {
        for (CluedoObject* unknownCluedoObject : m_unknownCluedoObjects) {
            if (CluedoObject::Murder == unknownCluedoObject->getCluedoObjectType()) {
                m_suspectedMurder = unknownCluedoObject;
            }
            else if (CluedoObject::Weapon == unknownCluedoObject->getCluedoObjectType()) {
                m_suspectedMurder = unknownCluedoObject;
            }
            else if (CluedoObject::Room == unknownCluedoObject->getCluedoObjectType()) {
                m_suspectedMurder = unknownCluedoObject;
            }
        }

        m_shouldTellSuspicion = true;
    }
}