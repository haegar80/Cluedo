#include "GameRunner.h"
#include "../Message/MessageIds.h"
#include "../Model/RemotePlayer.h"
#include <map>
#include <algorithm>
#include <random>
#include <sstream>

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

    return askPlayer(murderToAsk, weaponToAsk, roomToAsk);
}

void GameRunner::askPlayer(CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room)
{
    PlayerSet* currentPlayerSet = m_players.at(m_currentPlayerIndex)->getPlayerSet().get();
    currentPlayerSet->setLastAskedMurder(p_murder);
    currentPlayerSet->setLastAskedWeapon(p_weapon);
    currentPlayerSet->setLastAskedRoom(p_room);

    if (m_lastAskedPlayerIndex < 0) {
        currentPlayerSet->resetPlayerIndicesWithNoShownCluedoObjects();
    }

    int playerIndexToAsk = m_currentPlayerIndex + 1;
    if (m_lastAskedPlayerIndex >= 0) {
        playerIndexToAsk = m_lastAskedPlayerIndex + 1;
    }

    CluedoObject* foundObject = nullptr;
    if (m_players.size() == playerIndexToAsk)
    {
        playerIndexToAsk = 0;
        if (playerIndexToAsk == m_currentPlayerIndex)
        {
            handleNoObjectCanBeShown();
        }
    }

    m_lastAskedPlayerIndex = playerIndexToAsk;

    Player* playerToAsk = m_players.at(playerIndexToAsk);
    if (Player::PlayerType_SelfServer == playerToAsk->getPlayerType()) {
        m_showObjectCallback(playerToAsk->getName(), p_murder->getNumber(), p_weapon->getNumber(), p_room->getNumber());
    }
    else if (Player::PlayerType_Remote == playerToAsk->getPlayerType()) {
        RemotePlayer* remotePlayer = dynamic_cast<RemotePlayer*>(playerToAsk);
        if (remotePlayer) {
            SOCKET remoteSocket = remotePlayer->getRemoteSocket();
            std::stringstream ss;
            ss << MessageIds::AskOtherPlayer << ":";
            ss << m_currentPlayerIndex;
            ss << ";";
            ss << p_murder->getNumber();
            ss << ";";
            ss << p_weapon->getNumber();
            ss << ";";
            ss << p_room->getNumber();
            ss << ";";
#if WIN32
            m_tcpWinSocketServer->sendData(remoteSocket, ss.str());
#endif
        }
    }
    else if (Player::PlayerType_Computer == playerToAsk->getPlayerType()) {
        foundObject = askObjectsAtComputer(p_murder, p_weapon, p_room);
        askPlayerResponse((nullptr != foundObject), foundObject);
    }
}

void GameRunner::askPlayerResponse(bool p_objectCouldBeShown, CluedoObject* p_cluedoObject) {
    if (p_objectCouldBeShown) {
        askPlayerResponseWithShownObject(p_cluedoObject);
    }
    else {
        askPlayerResponseWithoutShownObject();
    }
}

void GameRunner::moveToNextPlayer() {
    m_currentPlayerIndex++;
    if (m_players.size() == m_currentPlayerIndex)
    {
        m_currentPlayerIndex = 0;
    }
}

void GameRunner::askPlayerResponseWithShownObject(CluedoObject* p_cluedoObject) {
    Player* currentPlayer = m_players.at(m_currentPlayerIndex);
    PlayerSet* currentPlayerSet = currentPlayer->getPlayerSet().get();
    currentPlayerSet->setLastShownCluedoObject(p_cluedoObject);
    currentPlayerSet->setLastPlayerIndexWhoShowedCluedoObject(m_lastAskedPlayerIndex);

    // This is only needed when current player is a computer
    currentPlayerSet->addCluedoObjectFromOtherPlayers(m_lastAskedPlayerIndex, p_cluedoObject);

    if (Player::PlayerType_SelfServer == currentPlayer->getPlayerType()) {
        m_objectShownCallback();
    }
    else if (Player::PlayerType_Remote == currentPlayer->getPlayerType()) {
        RemotePlayer* remotePlayer = dynamic_cast<RemotePlayer*>(currentPlayer);
        if (remotePlayer) {
            SOCKET remoteSocket = remotePlayer->getRemoteSocket();
            std::stringstream ss;
            ss << MessageIds::AskOtherPlayerResponse << ":";
            ss << m_lastAskedPlayerIndex;
            ss << ";";
            ss << p_cluedoObject->getNumber();
            ss << ";";
#if WIN32
            m_tcpWinSocketServer->sendData(remoteSocket, ss.str());
#endif
        }
    }

    askPlayerResponseInformNotInvolvedPlayer();
    m_lastAskedPlayerIndex = -1;
}

void GameRunner::askPlayerResponseWithoutShownObject() {
    Player* currentPlayer = m_players.at(m_currentPlayerIndex);
    PlayerSet* currentPlayerSet = currentPlayer->getPlayerSet().get();
    currentPlayerSet->setLastShownCluedoObject(nullptr);
    currentPlayerSet->addPlayerIndexWithNoShownCluedoObjects(m_lastAskedPlayerIndex);

    // This is only needed when current player is a computer
    currentPlayerSet->addMissingCluedoObjectsAtOtherPlayers(m_lastAskedPlayerIndex, currentPlayerSet->getLastAskedMurder());
    currentPlayerSet->addMissingCluedoObjectsAtOtherPlayers(m_lastAskedPlayerIndex, currentPlayerSet->getLastAskedWeapon());
    currentPlayerSet->addMissingCluedoObjectsAtOtherPlayers(m_lastAskedPlayerIndex, currentPlayerSet->getLastAskedRoom());

    constexpr int CluedoObjectNumberInitValue = 0;
    if (Player::PlayerType_Remote == currentPlayer->getPlayerType()) {
        RemotePlayer* remotePlayer = dynamic_cast<RemotePlayer*>(currentPlayer);
        if (remotePlayer) {
            SOCKET remoteSocket = remotePlayer->getRemoteSocket();
            std::stringstream ss;
            ss << MessageIds::AskOtherPlayerResponse << ":";
            ss << m_lastAskedPlayerIndex;
            ss << ";";
            ss << CluedoObjectNumberInitValue;
            ss << ";";
#if WIN32
            m_tcpWinSocketServer->sendData(remoteSocket, ss.str());
#endif
        }
    }

    askPlayer(currentPlayerSet->getLastAskedMurder(), currentPlayerSet->getLastAskedWeapon(), currentPlayerSet->getLastAskedRoom());
}

void GameRunner::handleNoObjectCanBeShown() {
    Player* currentPlayer = m_players.at(m_currentPlayerIndex);
    if (Player::PlayerType_SelfServer == currentPlayer->getPlayerType()) {
        m_noObjectCanBeShownCallback();
    }
    else if (Player::PlayerType_Remote == currentPlayer->getPlayerType()) {
        RemotePlayer* remotePlayer = dynamic_cast<RemotePlayer*>(currentPlayer);
        if (remotePlayer) {
            SOCKET remoteSocket = remotePlayer->getRemoteSocket();
            std::stringstream ss;
            ss << MessageIds::NoCluedoObjectCanBeShown << ":";
#if WIN32
            m_tcpWinSocketServer->sendData(remoteSocket, ss.str());
#endif
        }
    }

    askPlayerResponseInformNotInvolvedPlayer();
    m_lastAskedPlayerIndex = -1;
}

void GameRunner::askPlayerResponseInformNotInvolvedPlayer() {
    Player* currentPlayer = m_players.at(m_currentPlayerIndex);
    PlayerSet* currentPlayerSet = currentPlayer->getPlayerSet().get();

    for (int i = 0; i < m_players.size(); i++) {
        if ((i != m_currentPlayerIndex) && (i != m_lastAskedPlayerIndex)) {
            if (Player::PlayerType_SelfServer == m_players.at(i)->getPlayerType()) {
                PlayerSet* serverPlayerSet = m_players.at(i)->getPlayerSet().get();
                for (int playerIndexWithNoShownCluedoObject : currentPlayerSet->getPlayerIndicesWithNoShownCluedoObjects()) {
                    serverPlayerSet->addPlayerIndexWithNoShownCluedoObjects(playerIndexWithNoShownCluedoObject);
                }
                serverPlayerSet->setLastPlayerIndexWhoShowedCluedoObject(currentPlayerSet->getLastPlayerIndexWhoShowedCluedoObject());
                m_askPlayerResponseInformNotInvolvedServerCallback();
            }
            else if (Player::PlayerType_Remote == m_players.at(i)->getPlayerType()) {
                RemotePlayer* remotePlayer = dynamic_cast<RemotePlayer*>(m_players.at(i));
                if (remotePlayer) {
                    SOCKET remoteSocket = remotePlayer->getRemoteSocket();
                    std::stringstream ss;
                    ss << MessageIds::InformNotInvolvedPlayer << ":";
                    ss << currentPlayerSet->getLastAskedMurder()->getNumber();
                    ss << ";";
                    ss << currentPlayerSet->getLastAskedWeapon()->getNumber();
                    ss << ";";
                    ss << currentPlayerSet->getLastAskedRoom()->getNumber();
                    ss << ";";

                    for (int playerIndexWithNoShownCluedoObject : currentPlayerSet->getPlayerIndicesWithNoShownCluedoObjects()) {
                        ss << playerIndexWithNoShownCluedoObject;
                        ss << ";";
                    }
                    ss << currentPlayerSet->getLastPlayerIndexWhoShowedCluedoObject();
                    ss << ";";
#if WIN32
                    m_tcpWinSocketServer->sendData(remoteSocket, ss.str());
#endif
                }
            }
        }
    }
}

CluedoObject* GameRunner::askObjectsAtComputer(CluedoObject* p_murder, CluedoObject* p_weapon, CluedoObject* p_room)
{
    CluedoObject* foundObject = nullptr;

    PlayerSet* playerSet = m_players.at(m_lastAskedPlayerIndex)->getPlayerSet().get();
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