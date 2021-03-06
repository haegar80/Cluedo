#pragma once

#include <QtWidgets/QMainWindow>
#if WIN32
#include "../Network/TcpWinSocketServer.h"
#endif
#include <memory>

class WaitRemotePlayerUI;
class PlayerSetUI;
class QWidget;
class QPushButton;
class QLineEdit;
class QLabel;
class QString;
class QStatusBar;
class QComboBox;
class QMenuBar;

/// author: Copyright by Marcel Fuchs
class StartGameUI : public QMainWindow
{
    Q_OBJECT

public:
    StartGameUI();
    virtual ~StartGameUI() = default;

    void setupUi();
    void retranslateUi();
#if WIN32
    void setTcpWinSocketServer(std::shared_ptr<TcpWinSocketServer> p_winSocketServer) {
        m_tcpWinSocketServer = p_winSocketServer;
    }
#endif

    signals:
    void game_started_server();

    public slots:
    void buttonStartGame_clicked();
    void game_allRemoteUsersAvailable();
    void game_notAllRemoteUsersAvailable();
    void gameController_ready();

private:
    static constexpr int referenceWidth = 1920;
    static constexpr int referenceHeight = 1040;

#if WIN32
    std::shared_ptr<TcpWinSocketServer> m_tcpWinSocketServer;
#endif

    WaitRemotePlayerUI* m_waitRemotePlayerUI;
    PlayerSetUI* m_playerSetUI;

    QWidget* m_centralwidget;
    QLineEdit* m_lineEditPlayerName;
    QLabel* m_labelPlayerName;
    QLabel* m_labelNumberOfComputerPlayers;
    QComboBox* m_comboBoxNumberOfComputerPlayers;
    QLabel* m_labelNumberOfRemotePlayers;
    QComboBox* m_comboBoxNumberOfRemotePlayers;
    QPushButton* m_buttonStartGame;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    void initializeGame();
};
