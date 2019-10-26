#pragma once

#include "../Model/CluedoObject.h"
#include <vector>
#include <memory>

class CluedoObjectLoader
{
public:
    CluedoObjectLoader();
    virtual ~CluedoObjectLoader();

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
    std::vector<CluedoObject*> m_murders;
    std::vector<CluedoObject*> m_weapons;
    std::vector<CluedoObject*> m_rooms;

    void createMurders();
    void createWeapons();
    void createRooms();

    CluedoObjectLoader(const CluedoObjectLoader& copy) = default;
    CluedoObjectLoader& operator= (const CluedoObjectLoader& copy) = default;
    CluedoObjectLoader(CluedoObjectLoader&& other) = default;
    CluedoObjectLoader& operator= (CluedoObjectLoader&& other) = default;
};