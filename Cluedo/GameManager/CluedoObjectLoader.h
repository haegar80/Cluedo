#pragma once

#include "../Model/CluedoObject.h"
#include <vector>

class CluedoObjectLoader
{
public:
    static CluedoObjectLoader& getInstance();
    virtual ~CluedoObjectLoader();

    CluedoObject* findCluedoObjectByNumber(int p_number);

    std::vector<CluedoObject*>& getMurders()
    {
        return m_murders;
    }

    std::vector<CluedoObject*>& getWeapons()
    {
        return m_weapons;
    }

    std::vector<CluedoObject*>& getRooms()
    {
        return m_rooms;
    }

private:
    CluedoObjectLoader();

    std::vector<CluedoObject*> m_murders;
    std::vector<CluedoObject*> m_weapons;
    std::vector<CluedoObject*> m_rooms;

    void createMurders();
    void createWeapons();
    void createRooms();

    CluedoObjectLoader(const CluedoObjectLoader& copy) = delete;
    CluedoObjectLoader& operator= (const CluedoObjectLoader& copy) = delete;
    CluedoObjectLoader(CluedoObjectLoader&& other) = delete;
    CluedoObjectLoader& operator= (CluedoObjectLoader&& other) = delete;
};