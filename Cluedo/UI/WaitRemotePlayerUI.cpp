#include "WaitRemotePlayerUI.h"
#include "../GameManager/GameController.h"
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

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

    auto playerUpdateCallback = [this]() { updatedPlayers(); };
    GameController::getInstance().registerPlayerUpdateCallback(playerUpdateCallback);

    startTcpSocketServer();
}

void WaitRemotePlayerUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("MainWindow", "WaitRemotePlayer", nullptr));
    m_labelWaitRemotePlayer->setText(QApplication::translate("MainWindow", "Warte auf Mitspieler...", nullptr));
    m_buttonCancel->setText(QApplication::translate("MainWindow", "Abbrechen", nullptr));
}

void WaitRemotePlayerUI::updatedPlayers() {
    GameController& gameController = GameController::getInstance();
    std::vector<Player*>& availablePlayers = gameController.getPlayers();
    int numberOfRemoteUsers = std::count_if(availablePlayers.begin(), availablePlayers.end(), [](Player* player) {return ((nullptr != player) && (Player::PlayerType_Remote == player->getPlayerType())); });
    if (m_numberOfExpectedRemoteUsers == numberOfRemoteUsers) {
        emit game_allRemoteUsersAvailable();
        this->close();
    }
}

void WaitRemotePlayerUI::buttonCancel_clicked()
{
    emit game_notAllRemoteUsersAvailable();
    this->close();
}

void WaitRemotePlayerUI::startTcpSocketServer() {
#if WIN32
    m_tcpWinSocketServer.init();
    m_tcpWinSocketServer.listenToClients(m_numberOfExpectedRemoteUsers);
#endif
}