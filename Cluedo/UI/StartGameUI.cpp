#include "StartGameUI.h"
#include "PlayerSetUI.h"
#include "../Model/PlayerSet.h"
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
    this->resize(570, 211);
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
    m_comboBoxNumberOfComputerPlayers->setGeometry(QRect(440, 40, 69, 22));
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
    m_comboBoxNumberOfComputerPlayers->insertItem(4, "4");
    m_comboBoxNumberOfComputerPlayers->insertItem(5, "5");
}

void StartGameUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("StartGame", "StartGame", 0));
    m_labelPlayerName->setText(QApplication::translate("StartGame", "Benutzername", 0));
    m_labelNumberOfComputerPlayers->setText(QApplication::translate("StartGame", "Anzahl Computergegner"));
    m_buttonStartGame->setText(QApplication::translate("StartGame", "Starte Spiel", 0));
}

void StartGameUI::buttonStartGame_clicked()
{
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
        (void) gameController.createNewPlayer(computerName.str().c_str());
        (void) gameController.createNewPlayerSet();
    }
    
    (void) gameController.createNewPlayer(m_lineEditPlayerName->text().toStdString());
    PlayerSet* playerSet = gameController.createNewPlayerSet();

    m_playerSetUI = new PlayerSetUI(playerSet);
    m_playerSetUI->setAttribute(Qt::WA_DeleteOnClose);
    m_playerSetUI->show();
    this->close();
}