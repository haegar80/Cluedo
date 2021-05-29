#pragma once

#if WIN32
#include "../Network/TcpWinSocketClient.h"
#endif
#include <QtWidgets/QMainWindow>
#include <memory>

class QLineEdit;
class QLabel;
class QMenuBar;
class QPushButton;
class QStatusBar;
class QWidget;

/// author: Copyright by Marcel Fuchs
class ConnectServerUI : public QMainWindow
{
    Q_OBJECT

public:
    ConnectServerUI();
    virtual ~ConnectServerUI() = default;

    void setupUi();
    void retranslateUi();
#if WIN32
    void setTcpWinSocketClient(std::shared_ptr<TcpWinSocketClient> p_winSocketClient) {
        m_tcpWinSocketClient = p_winSocketClient;
    }
#endif

    signals:
    void game_started_client();

    public slots:
    void buttonOk_clicked();
    void buttonCancel_clicked();

private:
    static constexpr int referenceWidth = 1920;
    static constexpr int referenceHeight = 1040;

#if WIN32
    std::shared_ptr<TcpWinSocketClient> m_tcpWinSocketClient;
#endif

    QWidget* m_centralwidget;
    QLabel* m_labelPlayerName;
    QLineEdit* m_lineEditPlayerName;
    QLabel* m_labelIPAddressServer;
    QLineEdit* m_lineEditIPAddressServer;
    QPushButton* m_buttonOk;
    QPushButton* m_buttonCancel;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    void connectToServer();
};
