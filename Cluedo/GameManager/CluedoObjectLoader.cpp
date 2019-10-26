#include "CluedoObjectLoader.h"
#include  "../Model/Murder.h"
#include  "../Model/Weapon.h"
#include  "../Model/Room.h"

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

void CluedoObjectLoader::createMurders()
{
    CluedoObject* azurro = new Murder("Capitano Azurro");
    m_murders.push_back(azurro);
    CluedoObject* dunkel = new Murder("Doktor Dunkel");
    m_murders.push_back(dunkel);
    CluedoObject* rose = new Murder("Evelyne Rose");
    m_murders.push_back(rose);
    CluedoObject* weiss = new Murder("Fraeulein Weiss");
    m_murders.push_back(weiss);
    CluedoObject* curry = new Murder("Madame Curry");
    m_murders.push_back(curry);
    CluedoObject* verde = new Murder("Professor Verde");
    m_murders.push_back(verde);
}

void CluedoObjectLoader::createWeapons()
{
    CluedoObject* dolch = new Weapon("Dolch");
    m_weapons.push_back(dolch);
    CluedoObject* kerzenstaender = new Weapon("Kerzenstaender");
    m_weapons.push_back(kerzenstaender);
    CluedoObject* strick = new Weapon("Strick");
    m_weapons.push_back(strick);
    CluedoObject* bleirohr = new Weapon("Bleirohr");
    m_weapons.push_back(bleirohr);
    CluedoObject* revolver = new Weapon("Revolver");
    m_weapons.push_back(revolver);
    CluedoObject* schraubenschluessel = new Weapon("Schraubenschluessel");
    m_weapons.push_back(schraubenschluessel);
}

void CluedoObjectLoader::createRooms()
{
    CluedoObject* schlafzimmer = new Room("Schlafzimmer");
    m_rooms.push_back(schlafzimmer);
    CluedoObject* salon = new Room("Salon");
    m_rooms.push_back(salon);
    CluedoObject* billardzimmer = new Room("Billardzimmer");
    m_rooms.push_back(billardzimmer);
    CluedoObject* esszimmer = new Room("Esszimmer");
    m_rooms.push_back(esszimmer);
    CluedoObject* badezimmer = new Room("Badezimmer");
    m_rooms.push_back(badezimmer);
    CluedoObject* kueche = new Room("Kueche");
    m_rooms.push_back(kueche);
    CluedoObject* studio = new Room("Studio");
    m_rooms.push_back(studio);
    CluedoObject* musikzimmer = new Room("Musikzimmer");
    m_rooms.push_back(musikzimmer);
    CluedoObject* bibliothek = new Room("Bibliothek");
    m_rooms.push_back(bibliothek);
}