#pragma once

#include <QtWidgets/QMainWindow>
#include <memory>

#if WIN32
class TcpWinSocketServer;
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
#if WIN32
    void initTcpWinSocketServer(std::shared_ptr<TcpWinSocketServer> p_winSocketServer);
#endif

    signals:
    void game_allRemoteUsersAvailable();
    void game_notAllRemoteUsersAvailable();

    public slots:
    void remotePlayer_added();
    void buttonCancel_clicked();

private:
#if WIN32
    std::shared_ptr<TcpWinSocketServer> m_tcpWinSocketServer;
#endif

    int m_numberOfExpectedRemoteUsers{ 0 };
    int m_addedRemoteUsers{ 0 };

    QWidget* m_centralwidget;
    QLabel* m_labelWaitRemotePlayer;
    QPushButton* m_buttonCancel;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    void startTcpSocketServer();
};
