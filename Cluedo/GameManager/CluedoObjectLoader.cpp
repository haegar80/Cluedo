#include "CluedoObjectLoader.h"
#include  "../Model/Murder.h"
#include  "../Model/Weapon.h"
#include  "../Model/Room.h"

CluedoObjectLoader& CluedoObjectLoader::getInstance()
{
    static CluedoObjectLoader instance;
    return instance;
}

CluedoObjectLoader::CluedoObjectLoader()
{
    createMurders();
    createWeapons();
    createRooms();
}

CluedoObjectLoader::~CluedoObjectLoader()
{
    for (CluedoObject* murder : m_murders)
    {
        delete murder;
    }
    for (CluedoObject* weapon : m_weapons)
    {
        delete weapon;
    }
    for (CluedoObject* room : m_rooms)
    {
        delete room;
    }
}

CluedoObject* CluedoObjectLoader::findCluedoObjectByNumber(int p_number) {
    CluedoObject* cluedoObject = nullptr;

    auto itFoundMurders = std::find_if(m_murders.begin(), m_murders.end(), [&](CluedoObject* cluedoObject) { return (cluedoObject->getNumber() == p_number); });
    if (m_murders.end() == itFoundMurders) {
        auto itFoundWeapons = std::find_if(m_weapons.begin(), m_weapons.end(), [&](CluedoObject* cluedoObject) { return (cluedoObject->getNumber() == p_number); });
        if (m_weapons.end() == itFoundWeapons) {
            auto itFoundRooms = std::find_if(m_rooms.begin(), m_rooms.end(), [&](CluedoObject* cluedoObject) { return (cluedoObject->getNumber() == p_number); });
            if (m_rooms.end() != itFoundRooms) {
                cluedoObject = *itFoundRooms;
            }
        }
        else {
            cluedoObject = *itFoundWeapons;
        }
    }
    else {
        cluedoObject = *itFoundMurders;
    }
    
    return cluedoObject;
}

void CluedoObjectLoader::createMurders()
{
    CluedoObject* azurro = new Murder("Capitano Azurro");
    azurro->setNumber(++CluedoObject::maxNumber);
    m_murders.push_back(azurro);
    CluedoObject* dunkel = new Murder("Doktor Dunkel");
    dunkel->setNumber(++CluedoObject::maxNumber);
    m_murders.push_back(dunkel);
    CluedoObject* rose = new Murder("Evelyne Rose");
    rose->setNumber(++CluedoObject::maxNumber);
    m_murders.push_back(rose);
    CluedoObject* weiss = new Murder("Fraeulein Weiss");
    weiss->setNumber(++CluedoObject::maxNumber);
    m_murders.push_back(weiss);
    CluedoObject* curry = new Murder("Madame Curry");
    curry->setNumber(++CluedoObject::maxNumber);
    m_murders.push_back(curry);
    CluedoObject* verde = new Murder("Professor Verde");
    verde->setNumber(++CluedoObject::maxNumber);
    m_murders.push_back(verde);
}

void CluedoObjectLoader::createWeapons()
{
    CluedoObject* dolch = new Weapon("Dolch");
    dolch->setNumber(++CluedoObject::maxNumber);
    m_weapons.push_back(dolch);
    CluedoObject* kerzenstaender = new Weapon("Kerzenstaender");
    kerzenstaender->setNumber(++CluedoObject::maxNumber);
    m_weapons.push_back(kerzenstaender);
    CluedoObject* strick = new Weapon("Strick");
    strick->setNumber(++CluedoObject::maxNumber);
    m_weapons.push_back(strick);
    CluedoObject* bleirohr = new Weapon("Bleirohr");
    bleirohr->setNumber(++CluedoObject::maxNumber);
    m_weapons.push_back(bleirohr);
    CluedoObject* revolver = new Weapon("Revolver");
    revolver->setNumber(++CluedoObject::maxNumber);
    m_weapons.push_back(revolver);
    CluedoObject* schraubenschluessel = new Weapon("Schraubenschluessel");
    schraubenschluessel->setNumber(++CluedoObject::maxNumber);
    m_weapons.push_back(schraubenschluessel);
}

void CluedoObjectLoader::createRooms()
{
    CluedoObject* schlafzimmer = new Room("Schlafzimmer");
    schlafzimmer->setNumber(++CluedoObject::maxNumber);
    m_rooms.push_back(schlafzimmer);
    CluedoObject* salon = new Room("Salon");
    salon->setNumber(++CluedoObject::maxNumber);
    m_rooms.push_back(salon);
    CluedoObject* billardzimmer = new Room("Billardzimmer");
    billardzimmer->setNumber(++CluedoObject::maxNumber);
    m_rooms.push_back(billardzimmer);
    CluedoObject* esszimmer = new Room("Esszimmer");
    esszimmer->setNumber(++CluedoObject::maxNumber);
    m_rooms.push_back(esszimmer);
    CluedoObject* badezimmer = new Room("Badezimmer");
    badezimmer->setNumber(++CluedoObject::maxNumber);
    m_rooms.push_back(badezimmer);
    CluedoObject* kueche = new Room("Kueche");
    kueche->setNumber(++CluedoObject::maxNumber);
    m_rooms.push_back(kueche);
    CluedoObject* studio = new Room("Studio");
    studio->setNumber(++CluedoObject::maxNumber);
    m_rooms.push_back(studio);
    CluedoObject* musikzimmer = new Room("Musikzimmer");
    musikzimmer->setNumber(++CluedoObject::maxNumber);
    m_rooms.push_back(musikzimmer);
    CluedoObject* bibliothek = new Room("Bibliothek");
    bibliothek->setNumber(++CluedoObject::maxNumber);
    m_rooms.push_back(bibliothek);
}