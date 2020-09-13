#pragma once

#include <QtWidgets/QMainWindow>

#if WIN32
#include "../Network/TcpWinSocketServer.h"
#endif

class QWidget;
class QPushButton;
class QLabel;
class QString;
class QStatusBar;
class QMenuBar;

/// author: Copyright by Marcel Fuchs
class WaitRemotePlayerUI : public QMainWindow
{
    Q_OBJECT

public:
    WaitRemotePlayerUI(int p_numberOfExpectedRemoteUsers);
    virtual ~WaitRemotePlayerUI() = default;

    void setupUi();
    void retranslateUi();
    void updatedPlayers();

    signals:
    void game_allRemoteUsersAvailable();
    void game_notAllRemoteUsersAvailable();

    public slots:
    void buttonCancel_clicked();

private:
#if WIN32
    TcpWinSocketServer m_tcpWinSocketServer;
#endif

    int m_numberOfExpectedRemoteUsers{ 0 };

    QWidget* m_centralwidget;
    QLabel* m_labelWaitRemotePlayer;
    QPushButton* m_buttonCancel;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    void startTcpSocketServer();
};
