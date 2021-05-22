#include "StartGameUI.h"
#include "WaitRemotePlayerUI.h"
#include "../Model/Player.h"
#include "../GameManager/GameController.h"
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <sstream>

StartGameUI::StartGameUI()
{
    setupUi();
}

void StartGameUI::setupUi()
{
    if (this->objectName().isEmpty())
    {
        this->setObjectName(QString::fromUtf8("MainWindow"));
    }

    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    float fW = static_cast<float>(screenGeometry.width()) / static_cast<float>(referenceWidth);
    float fH = static_cast<float>(screenGeometry.height()) / static_cast<float>(referenceHeight);
    this->resize(624 * fW, 211 * fH);

    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_lineEditPlayerName = new QLineEdit(m_centralwidget);
    m_lineEditPlayerName->setObjectName(QString::fromUtf8("lineEditPlayerName"));
    m_lineEditPlayerName->setGeometry(QRect(130 * fW, 40 * fH, 131 * fW, 20 * fH));
    m_labelPlayerName = new QLabel(m_centralwidget);
    m_labelPlayerName->setObjectName(QString::fromUtf8("labelPlayerName"));
    m_labelPlayerName->setGeometry(QRect(50 * fW, 40 * fH, 81 * fW, 16 * fH));
    m_labelNumberOfComputerPlayers = new QLabel(m_centralwidget);
    m_labelNumberOfComputerPlayers->setObjectName(QString::fromUtf8("labelNumberOfComputerPlayers"));
    m_labelNumberOfComputerPlayers->setGeometry(QRect(300 * fW, 40 * fH, 121 * fW, 16 * fH));
    m_comboBoxNumberOfComputerPlayers = new QComboBox(m_centralwidget);
    m_comboBoxNumberOfComputerPlayers->setObjectName(QString::fromUtf8("comboBoxNumberOfComputerPlayers"));
    m_comboBoxNumberOfComputerPlayers->setGeometry(QRect(470 * fW, 40, 69 * fW, 22));
    m_labelNumberOfRemotePlayers = new QLabel(m_centralwidget);
    m_labelNumberOfRemotePlayers->setObjectName(QStringLiteral("labelNumberOfRemotePlayers"));
    m_labelNumberOfRemotePlayers->setGeometry(QRect(300 * fW, 80 * fH, 161 * fW, 16 * fH));
    m_comboBoxNumberOfRemotePlayers = new QComboBox(m_centralwidget);
    m_comboBoxNumberOfRemotePlayers->setObjectName(QStringLiteral("comboBoxNumberOfRemotePlayers"));
    m_comboBoxNumberOfRemotePlayers->setGeometry(QRect(470 * fW, 80 * fH, 69 * fW, 22 * fH));
    m_buttonStartGame = new QPushButton(m_centralwidget);
    m_buttonStartGame->setObjectName(QString::fromUtf8("buttonStartGame"));
    m_buttonStartGame->setGeometry(QRect(50 * fW, 120 * fH, 75 * fW, 23 * fH));
    this->setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QString::fromUtf8("menubar"));
    m_menubar->setGeometry(QRect(0, 0, 570 * fW, 21 * fH));
    this->setMenuBar(m_menubar);
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(m_statusbar);

    retranslateUi();

    QObject::connect(m_buttonStartGame, SIGNAL(pressed()), this, SLOT(buttonStartGame_clicked()));
    QObject::connect(&GameController::getInstance(), SIGNAL(gameController_ready()), this, SLOT(gameController_ready()));

    m_comboBoxNumberOfComputerPlayers->insertItem(0, "Kein");
    m_comboBoxNumberOfComputerPlayers->insertItem(1, "1");
    m_comboBoxNumberOfComputerPlayers->insertItem(2, "2");
    m_comboBoxNumberOfComputerPlayers->insertItem(3, "3");

    m_comboBoxNumberOfRemotePlayers->insertItem(0, "Kein");
    m_comboBoxNumberOfRemotePlayers->insertItem(1, "1");
    m_comboBoxNumberOfRemotePlayers->insertItem(2, "2");
    m_comboBoxNumberOfRemotePlayers->insertItem(3, "3");
}

void StartGameUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("StartGame", "StartGame", 0));
    m_labelPlayerName->setText(QApplication::translate("StartGame", "Benutzername", 0));
    m_labelNumberOfComputerPlayers->setText(QApplication::translate("StartGame", "Anzahl Computergegner"));
    m_labelNumberOfRemotePlayers->setText(QApplication::translate("MainWindow", "Anzahl Gegner \303\274bers Netzwerk", nullptr));
    m_buttonStartGame->setText(QApplication::translate("StartGame", "Starte Spiel", 0));
}

void StartGameUI::buttonStartGame_clicked()
{
    GameController::getInstance().reset();

    int numberOfRemotePlayers = m_comboBoxNumberOfRemotePlayers->currentIndex();
    if (numberOfRemotePlayers < 0)
    {
        numberOfRemotePlayers = 0;
    }
    if (numberOfRemotePlayers > 0) {
        m_waitRemotePlayerUI = new WaitRemotePlayerUI(numberOfRemotePlayers);
        m_waitRemotePlayerUI->setWindowModality(Qt::ApplicationModal);
        m_waitRemotePlayerUI->setAttribute(Qt::WA_DeleteOnClose);

#if WIN32
        m_waitRemotePlayerUI->initTcpWinSocketServer(m_tcpWinSocketServer);
#endif

        QObject::connect(m_waitRemotePlayerUI, SIGNAL(game_allRemoteUsersAvailable()), this, SLOT(game_allRemoteUsersAvailable()));
        QObject::connect(m_waitRemotePlayerUI, SIGNAL(game_notAllRemoteUsersAvailable()), this, SLOT(game_notAllRemoteUsersAvailable()));

        m_waitRemotePlayerUI->show();
    }
    else {
        initializeGame();
    }
}

void StartGameUI::initializeGame() {
    int numberOfComputerPlayers = m_comboBoxNumberOfComputerPlayers->currentIndex();
    if (numberOfComputerPlayers < 0)
    {
        numberOfComputerPlayers = 0;
    }

    GameController& gameController = GameController::getInstance();

    for (int i = 0; i < numberOfComputerPlayers; i++)
    {
        std::stringstream computerName;
        computerName << "Computer " << (i + 1);
        (void)gameController.createNewPlayer(computerName.str().c_str(), Player::PlayerType_Computer);
    }

    (void) gameController.createNewPlayer(m_lineEditPlayerName->text().toStdString(), Player::PlayerType_SelfServer);

    gameController.startGame();

    this->close();
}

void StartGameUI::game_allRemoteUsersAvailable() {
    initializeGame();
}

void StartGameUI::game_notAllRemoteUsersAvailable()
{
    // Do nothing yet
}

void StartGameUI::gameController_ready() {
    emit game_started_server();
}