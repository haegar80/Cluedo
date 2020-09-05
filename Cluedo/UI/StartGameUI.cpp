#include "StartGameUI.h"
#include "WaitRemotePlayerUI.h"
#include "../Model/Player.h"
#include "../GameManager/GameController.h"
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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
    this->resize(624, 211);
    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_lineEditPlayerName = new QLineEdit(m_centralwidget);
    m_lineEditPlayerName->setObjectName(QString::fromUtf8("lineEditPlayerName"));
    m_lineEditPlayerName->setGeometry(QRect(130, 40, 131, 20));
    m_labelPlayerName = new QLabel(m_centralwidget);
    m_labelPlayerName->setObjectName(QString::fromUtf8("labelPlayerName"));
    m_labelPlayerName->setGeometry(QRect(50, 40, 81, 16));
    m_labelNumberOfComputerPlayers = new QLabel(m_centralwidget);
    m_labelNumberOfComputerPlayers->setObjectName(QString::fromUtf8("labelNumberOfComputerPlayers"));
    m_labelNumberOfComputerPlayers->setGeometry(QRect(300, 40, 121, 16));
    m_comboBoxNumberOfComputerPlayers = new QComboBox(m_centralwidget);
    m_comboBoxNumberOfComputerPlayers->setObjectName(QString::fromUtf8("comboBoxNumberOfComputerPlayers"));
    m_comboBoxNumberOfComputerPlayers->setGeometry(QRect(470, 40, 69, 22));
    m_labelNumberOfRemotePlayers = new QLabel(m_centralwidget);
    m_labelNumberOfRemotePlayers->setObjectName(QStringLiteral("labelNumberOfRemotePlayers"));
    m_labelNumberOfRemotePlayers->setGeometry(QRect(300, 80, 161, 16));
    m_comboBoxNumberOfRemotePlayers = new QComboBox(m_centralwidget);
    m_comboBoxNumberOfRemotePlayers->setObjectName(QStringLiteral("comboBoxNumberOfRemotePlayers"));
    m_comboBoxNumberOfRemotePlayers->setGeometry(QRect(470, 80, 69, 22));
    m_buttonStartGame = new QPushButton(m_centralwidget);
    m_buttonStartGame->setObjectName(QString::fromUtf8("buttonStartGame"));
    m_buttonStartGame->setGeometry(QRect(50, 120, 75, 23));
    this->setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QString::fromUtf8("menubar"));
    m_menubar->setGeometry(QRect(0, 0, 570, 21));
    this->setMenuBar(m_menubar);
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(m_statusbar);

    retranslateUi();

    QObject::connect(m_buttonStartGame, SIGNAL(pressed()), this, SLOT(buttonStartGame_clicked()));

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
    int numberOfRemotePlayers = m_comboBoxNumberOfRemotePlayers->currentIndex();
    if (numberOfRemotePlayers < 0)
    {
        numberOfRemotePlayers = 0;
    }
    if (numberOfRemotePlayers > 0) {
        m_waitRemotePlayerUI = new WaitRemotePlayerUI(numberOfRemotePlayers);
        m_waitRemotePlayerUI->setWindowModality(Qt::ApplicationModal);
        m_waitRemotePlayerUI->setAttribute(Qt::WA_DeleteOnClose);

        QObject::connect(m_waitRemotePlayerUI, SIGNAL(game_AllRemoteUsersAvailable()), this, SLOT(game_AllRemoteUsersAvailable()));
        QObject::connect(m_waitRemotePlayerUI, SIGNAL(game_remoteUserNotAvailable()), this, SLOT(game_remoteUserNotAvailable()));

        m_waitRemotePlayerUI->show();
    }
    else {
        initializeGame();
    }
}

void StartGameUI::game_allRemoteUsersAvailable() {
    initializeGame();
}

void StartGameUI::game_remoteUserNotAvailable()
{
    // Do nothing yet
}

void StartGameUI::initializeGame() {
    int numberOfComputerPlayers = m_comboBoxNumberOfComputerPlayers->currentIndex();
    if (numberOfComputerPlayers < 0)
    {
        numberOfComputerPlayers = 0;
    }

    GameController& gameController = GameController::getInstance();
    gameController.reset();

    for (int i = 0; i < numberOfComputerPlayers; i++)
    {
        std::stringstream computerName;
        computerName << "Computer " << (i + 1);
        (void)gameController.createNewPlayer(computerName.str().c_str(), Player::PlayerType_Computer);
    }

    Player* player = gameController.createNewPlayer(m_lineEditPlayerName->text().toStdString(), Player::PlayerType_Self);

    GameController::getInstance().startGame();
    gameStarted();

    this->close();
}

void StartGameUI::gameStarted()
{
    emit game_started();
}