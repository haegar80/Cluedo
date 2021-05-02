#include "WaitRemotePlayerUI.h"
#include "../GameManager/GameController.h"
#if WIN32
#include "../Network/TcpWinSocketServer.h"
#endif
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <future>
#include <thread>

WaitRemotePlayerUI::WaitRemotePlayerUI(int p_numberOfExpectedRemoteUsers) : m_numberOfExpectedRemoteUsers(p_numberOfExpectedRemoteUsers)
{
    setupUi();
}

void WaitRemotePlayerUI::setupUi()
{
    if (this->objectName().isEmpty())
    {
        this->setObjectName(QString::fromUtf8("MainWindow"));
    }
    this->resize(318, 137);
    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QStringLiteral("centralwidget"));
    m_labelWaitRemotePlayer = new QLabel(m_centralwidget);
    m_labelWaitRemotePlayer->setObjectName(QStringLiteral("labelWaitRemotePlayer"));
    m_labelWaitRemotePlayer->setGeometry(QRect(30, 20, 121, 16));
    m_buttonCancel = new QPushButton(m_centralwidget);
    m_buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
    m_buttonCancel->setGeometry(QRect(30, 60, 81, 21));
    this->setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QStringLiteral("menubar"));
    m_menubar->setGeometry(QRect(0, 0, 318, 21));
    this->setMenuBar(m_menubar);
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QStringLiteral("statusbar"));
    this->setStatusBar(m_statusbar);

    retranslateUi();

    QObject::connect(m_buttonCancel, SIGNAL(pressed()), this, SLOT(buttonCancel_clicked()));
    QObject::connect(&GameController::getInstance(), SIGNAL(remotePlayer_added()), this, SLOT(remotePlayer_added()));
}

void WaitRemotePlayerUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("MainWindow", "WaitRemotePlayer", nullptr));
    m_labelWaitRemotePlayer->setText(QApplication::translate("MainWindow", "Warte auf Mitspieler...", nullptr));
    m_buttonCancel->setText(QApplication::translate("MainWindow", "Abbrechen", nullptr));
}

#if WIN32
void WaitRemotePlayerUI::initTcpWinSocketServer(std::shared_ptr<TcpWinSocketServer> p_winSocketServer) {
    m_tcpWinSocketServer = p_winSocketServer;
    startTcpSocketServer();
}
#endif

void WaitRemotePlayerUI::remotePlayer_added() {
    m_addedRemoteUsers++;

    if (m_numberOfExpectedRemoteUsers == m_addedRemoteUsers) {
#if WIN32
        if (m_tcpWinSocketServer) {
            m_tcpWinSocketServer->disableWaitingForClients();
        }
#endif
        emit game_allRemoteUsersAvailable();
        this->close();
    }
}

void WaitRemotePlayerUI::buttonCancel_clicked()
{
#if WIN32
    if (m_tcpWinSocketServer) {
        m_tcpWinSocketServer->disableWaitingForClients();
    }
#endif

    emit game_notAllRemoteUsersAvailable();
    this->close();
}

void WaitRemotePlayerUI::startTcpSocketServer() {
#if WIN32
    if (m_tcpWinSocketServer) {
        bool initSuccessful = m_tcpWinSocketServer->init();

        if (initSuccessful) {
            std::thread t(&TcpWinSocketServer::listenToClients, m_tcpWinSocketServer);
            t.detach();
        }
    }
#endif
}