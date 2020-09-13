#pragma once

#if WIN32
#include "../Network/TcpWinSocketClient.h"
#endif

#include <QtWidgets/QMainWindow>

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

    public slots:
    void buttonOk_clicked();
    void buttonCancel_clicked();

private:
#if WIN32
    TcpWinSocketClient m_tcpWinSocketClient;
#endif

    QWidget* m_centralwidget;
    QLabel* m_labelIPAddressServer;
    QLineEdit* m_lineEditIPAddressServer;
    QPushButton* m_buttonOk;
    QPushButton* m_buttonCancel;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    void connectToServer();
};
