#pragma once

#include <QtWidgets/QMainWindow>
#if WIN32
#include "../Network/TcpWinSocketClient.h"
#include "../Network/TcpWinSocketServer.h"
#endif
#include <memory>

class PlayerSet;
class AskPlayerUI;
class ConnectServerUI;
class StartGameUI;
class SelectObjectsUI;
class SelectObjectToShowUI;

class QWidget;
class QPushButton;
class QListWidget;
class QLabel;
class QMenuBar;
class QStatusBar;

/// author: Copyright by Marcel Fuchs
class CluedoUI : public QMainWindow
{
    Q_OBJECT

public:
    CluedoUI();
    virtual ~CluedoUI() = default;

    void setupUi();
    void retranslateUi();

    public slots:
    void buttonSelectObjects_clicked();
    void buttonStartGame_clicked();
    void buttonConnectGame_clicked();
    void buttonQuitGame_clicked();
    void game_started_server();
    void game_started_client();
    void playersList_updated();
    void currentPlayerIndex_updated();
    void allCluedoObjects_distributed();
    void showObject_requested(const QString& p_askedPlayer, int p_murderNumber, int p_weaponNumber, int p_roomNumber);
    void askPlayerFromOtherPlayer_finished(int p_askedMurderNumber, int p_askedWeaponNumber, int p_askedRoomNumber);
    void askPlayerFromOtherPlayerWindow_closed();
    void askPlayer_finished();

private:
    QWidget* m_centralwidget;
    QWidget* m_selectionObjectWidget;
    QLabel* m_labelCluedoObjects;
    QLabel* m_labelCluedoObject1;
    QLabel* m_labelCluedoObject2;
    QLabel* m_labelCluedoObject3;
    QLabel* m_labelCluedoObject4;
    QLabel* m_labelCluedoObject5;
    QLabel* m_labelCluedoObject6;
    QLabel* m_imageCluedoObject1;
    QLabel* m_imageCluedoObject2;
    QLabel* m_imageCluedoObject3;
    QLabel* m_imageCluedoObject4;
    QLabel* m_imageCluedoObject5;
    QLabel* m_imageCluedoObject6;
    QLabel* m_labelCurrentPlayer;
    QListWidget* m_listPlayers;
    QPushButton* m_buttonSelectObjects;
    QPushButton* m_buttonStartGame;
    QPushButton* m_buttonConnectGame;
    QPushButton* m_quitButton;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    std::shared_ptr<PlayerSet> m_myPlayerSet;

    AskPlayerUI* m_askPlayerInfoUI;
    ConnectServerUI* m_connectServerUI;
    StartGameUI* m_startGameUI;
    SelectObjectsUI* m_selectObjectsUI;
    SelectObjectToShowUI* m_selectObjectToShowUI;

#if WIN32
    std::shared_ptr<TcpWinSocketClient> m_tcpWinSocketClient;
    std::shared_ptr<TcpWinSocketServer> m_tcpWinSocketServer;
#endif

    void selectCurrentPlayer();
    void hideNotUsedCluedoObjects();
    void fillCluedoObjects();
};
