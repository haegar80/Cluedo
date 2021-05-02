#include "GameRunner.h"
#include "../Model/RemotePlayer.h"
#include <map>
#include <algorithm>
#include <random>

GameRunner::GameRunner(std::vector<Player*>& p_players) : m_players(p_players)
{
}

void GameRunner::startGame() {
    m_currentPlayerIndex = 0;
}

void GameRunner::askPlayer()
{
    CluedoObject* murderToAsk{ nullptr };
    CluedoObject* weaponToAsk{ nullptr };
    CluedoObject* roomToAsk{ nullptr };
    getObjectsToAsk(&murderToAsk, &weaponToAsk, &roomToAsk);

    checkObjectsAtOtherPlayers(murderToAsk, weaponToAsk, roomToAsk);
}

void GameRunner::askPlayer(int p_murderIndex, int p_weaponIndex, int p_roomIndex)
{
    CluedoObjectLoader& cluedoObjectLoader = CluedoObjectLoader::getInstance();
    std::vector<CluedoObject*> murders = cluedoObjectLoader.getMurders();
    CluedoObject* murder = murders.at(p_murderIndex);

    std::vector<CluedoObject*> weapons = cluedoObjectLoader.getWeapons();
    CluedoObject* weapon = weapons.at(p_weaponIndex);

    std::vector<CluedoObject*> rooms = cluedoObjectLoader.getRooms();
    CluedoObject* room = rooms.at(p_roomIndex);

    checkObjectsAtOtherPlayers(murder, weapon, room);
}

void GameRunner::moveToNextPlayer() {
    m_currentPlayerIndex++;
    if (m_players.size() == m_currentPlayerIndex)
    {
        m_currentPlayerIndex = 0;
    }

    Player* currentPlayer = m_players.at(m_currentPlayerIndex);
    
    emit playersListNextPlayer_ready();
    printf("Update players list that next player is ready\n");

    if (Player::PlayerType_SelfServer == currentPlayer->getPlayerType()) {
        emit askPlayer_ready();
    }
}

void GameRunner::checkObjectsAtOtherPlayers(CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room)
{
    int playerIndexToAsk = m_currentPlayerIndex + 1;

    PlayerSet* currentPlayerSet = m_players.at(m_currentPlayerIndex)->getPlayerSet().get();
    currentPlayerSet->setLastAskedMurder(p_murder);
    currentPlayerSet->setLastAskedWeapon(p_weapon);
    currentPlayerSet->setLastAskedRoom(p_room);
    currentPlayerSet->resetPlayerIndicesWithNoShownCluedoObjects();

    CluedoObject* foundObject = nullptr;
    while ((playerIndexToAsk != m_currentPlayerIndex) && (nullptr == foundObject))
    {
        if (m_players.size() == playerIndexToAsk)
        {
            playerIndexToAsk = 0;
            if (playerIndexToAsk == m_currentPlayerIndex)
            {
                break;
            }
        }

        Player* playerToAsk = m_players.at(playerIndexToAsk);
        if (Player::PlayerType_Remote == playerToAsk->getPlayerType()) {
            RemotePlayer* remotePlayer = dynamic_cast<RemotePlayer*>(playerToAsk);
            if (remotePlayer) {
                SOCKET remoteSocket = remotePlayer->getRemoteSocket();
                m_tcpWinSocketServer->sendData(remoteSocket, "Hast du etwas von " + p_murder->getName() + "?");
            }
        }

        foundObject = askObjectsAtOtherPlayer(playerIndexToAsk, p_murder, p_weapon, p_room);

        if (nullptr == foundObject)
        {
            currentPlayerSet->addPlayerIndexWithNoShownCluedoObjects(playerIndexToAsk);
            currentPlayerSet->addMissingCluedoObjectsAtOtherPlayers(playerIndexToAsk, p_murder);
            currentPlayerSet->addMissingCluedoObjectsAtOtherPlayers(playerIndexToAsk, p_weapon);
            currentPlayerSet->addMissingCluedoObjectsAtOtherPlayers(playerIndexToAsk, p_room);
        }

        playerIndexToAsk++;
    }

    if (nullptr != foundObject)
    {
        int playerIndex = --playerIndexToAsk;
        currentPlayerSet->setLastShownCluedoObject(foundObject);
        currentPlayerSet->setLastPlayerIndexWhoShowedCluedoObject(playerIndex);
        currentPlayerSet->addCluedoObjectFromOtherPlayers(playerIndex, foundObject);
    }
    else
    {
        currentPlayerSet->setLastShownCluedoObject(nullptr);
    }
}

CluedoObject* GameRunner::askObjectsAtOtherPlayer(int p_otherPlayerIndex, CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room)
{
    CluedoObject* foundObject = nullptr;

    PlayerSet* playerSet = m_players.at(p_otherPlayerIndex)->getPlayerSet().get();
    std::vector<CluedoObject*>& cluedoObjects = playerSet->getCluedoObjects();

    for (CluedoObject* cluedoObject : cluedoObjects)
    {
        if (cluedoObject == p_murder)
        {
            foundObject = p_murder;
            break;
        }
        else if (cluedoObject == p_weapon)
        {
            foundObject = p_weapon;
            break;
        }
        else if (cluedoObject == p_room)
        {
            foundObject = p_room;
            break;
        }
    }

    return foundObject;
}

void GameRunner::getObjectsToAsk(CluedoObject** p_murder, CluedoObject** p_weapon, CluedoObject** p_room)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    CluedoObjectLoader& cluedoObjectLoader = CluedoObjectLoader::getInstance();
    std::vector<CluedoObject*>murders = cluedoObjectLoader.getMurders();
    auto randomEngineMurders = std::default_random_engine(seed);
    std::shuffle(std::begin(murders), std::end(murders), randomEngineMurders);

    std::vector<CluedoObject*>weapons = cluedoObjectLoader.getWeapons();
    auto randomEngineWeapons = std::default_random_engine(seed);
    std::shuffle(std::begin(weapons), std::end(weapons), randomEngineWeapons);

    std::vector<CluedoObject*>rooms = cluedoObjectLoader.getRooms();
    auto randomEngineRooms = std::default_random_engine(seed);
    std::shuffle(std::begin(rooms), std::end(rooms), randomEngineRooms);

    findUnknownObject(murders, p_murder);
    findUnknownObject(weapons, p_weapon);
    findUnknownObject(rooms, p_room);
}

void GameRunner::findUnknownObject(std::vector<CluedoObject*>& p_cluedoObjectsToCheck, CluedoObject** p_foundObject)
{
    bool foundUnknownObject = false;

    PlayerSet* currentPlayerSet = m_players.at(m_currentPlayerIndex)->getPlayerSet().get();
    std::vector<CluedoObject*>& cluedoObjects = currentPlayerSet->getCluedoObjects();
    std::multimap<int, CluedoObject*>& cluedoObjectsFromOtherPlayers = currentPlayerSet->getCluedoObjectsFromOtherPlayers();

    for (CluedoObject* cluedoObject : p_cluedoObjectsToCheck)
    {
        auto resultObjectsFromCurrentPlayer = std::find_if(
            cluedoObjects.begin(),
            cluedoObjects.end(),
            [cluedoObject](const CluedoObject* vectorObject) {return vectorObject == cluedoObject; });

        if (cluedoObjects.end() == resultObjectsFromCurrentPlayer)
        {
            *p_foundObject = cluedoObject;
            foundUnknownObject = true;
        }

        if(foundUnknownObject)
        {
            foundUnknownObject = false;

            auto resultObjectsFromOtherPlayers = std::find_if(
                cluedoObjectsFromOtherPlayers.begin(),
                cluedoObjectsFromOtherPlayers.end(),
                [cluedoObject](const auto& mapObject) {return mapObject.second == cluedoObject; });

            if (cluedoObjectsFromOtherPlayers.end() == resultObjectsFromOtherPlayers)
            {
                *p_foundObject = cluedoObject;
                foundUnknownObject = true;
                break;
            }
        }
    }
}