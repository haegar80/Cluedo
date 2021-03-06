#include "CluedoUI.h"
#include "AskPlayerUI.h"
#include "ConnectServerUI.h"
#include "StartGameUI.h"
#include "SelectObjectsUI.h"
#include "SelectObjectToShowUI.h"
#include "../Model/Player.h"
#include "../GameManager/GameController.h"
#include "../Utils/Utils.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QMessageBox>
#include <sstream>

CluedoUI::CluedoUI()
{
    setupUi();
}

void CluedoUI::setupUi()
{
    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("windowCluedo"));
    }

    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    this->resize(screenGeometry.width(), screenGeometry.height());
    this->setMinimumSize(QSize(1000, 1000));
    float fW = static_cast<float>(screenGeometry.width()) / static_cast<float>(referenceWidth);
    float fH = static_cast<float>(screenGeometry.height()) / static_cast<float>(referenceHeight);

    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_selectionObjectWidget = new QWidget(m_centralwidget);
    m_selectionObjectWidget->setObjectName(QString::fromUtf8("selectionObjectWidget"));
    m_selectionObjectWidget->setGeometry(QRect(20 * fW, 40 * fH, 1041 * fW, 681 * fH));
    m_labelCluedoObjects = new QLabel(m_selectionObjectWidget);
    m_labelCluedoObjects->setObjectName(QStringLiteral("labelCluedoObjects"));
    m_labelCluedoObjects->setGeometry(QRect(20 * fW, 30 * fH, 201 * fW, 16 * fH));
    m_labelCluedoObject1 = new QLabel(m_selectionObjectWidget);
    m_labelCluedoObject1->setObjectName(QStringLiteral("labelCluedoObject1"));
    m_labelCluedoObject1->setGeometry(QRect(20 * fW, 60 * fH, 151 * fW, 16 * fH));
    m_labelCluedoObject2 = new QLabel(m_selectionObjectWidget);
    m_labelCluedoObject2->setObjectName(QStringLiteral("labelCluedoObject2"));
    m_labelCluedoObject2->setGeometry(QRect(190 * fW, 60 * fH, 151 * fW, 16 * fH));
    m_labelCluedoObject3 = new QLabel(m_selectionObjectWidget);
    m_labelCluedoObject3->setObjectName(QStringLiteral("labelCluedoObject3"));
    m_labelCluedoObject3->setGeometry(QRect(360 * fW, 60 * fH, 151 * fW, 16 * fH));
    m_labelCluedoObject4 = new QLabel(m_selectionObjectWidget);
    m_labelCluedoObject4->setObjectName(QStringLiteral("labelCluedoObject4"));
    m_labelCluedoObject4->setGeometry(QRect(530 * fW, 60 * fH, 151 * fW, 16 * fH));
    m_labelCluedoObject5 = new QLabel(m_selectionObjectWidget);
    m_labelCluedoObject5->setObjectName(QStringLiteral("labelCluedoObject5"));
    m_labelCluedoObject5->setGeometry(QRect(700 * fW, 60 * fH, 151 * fW, 16 * fH));
    m_labelCluedoObject6 = new QLabel(m_selectionObjectWidget);
    m_labelCluedoObject6->setObjectName(QStringLiteral("labelCluedoObject6"));
    m_labelCluedoObject6->setGeometry(QRect(870 * fW, 60 * fH, 151 * fW, 16 * fH));
    m_imageCluedoObject1 = new QLabel(m_selectionObjectWidget);
    m_imageCluedoObject1->setObjectName(QStringLiteral("imageCluedoObject1"));
    m_imageCluedoObject1->setGeometry(QRect(20 * fW, 90 * fH, 150 * fW, 200 * fH));
    m_imageCluedoObject1->setFrameShape(QFrame::Box);
    m_imageCluedoObject1->setScaledContents(true);
    m_imageCluedoObject2 = new QLabel(m_selectionObjectWidget);
    m_imageCluedoObject2->setObjectName(QStringLiteral("imageCluedoObject2"));
    m_imageCluedoObject2->setGeometry(QRect(190 * fW, 90 * fH, 150 * fW, 200 * fH));
    m_imageCluedoObject2->setFrameShape(QFrame::Box);
    m_imageCluedoObject2->setScaledContents(true);
    m_imageCluedoObject3 = new QLabel(m_selectionObjectWidget);
    m_imageCluedoObject3->setObjectName(QStringLiteral("imageCluedoObject3"));
    m_imageCluedoObject3->setGeometry(QRect(360 * fW, 90 * fH, 150 * fW, 200 * fH));
    m_imageCluedoObject3->setFrameShape(QFrame::Box);
    m_imageCluedoObject3->setScaledContents(true);
    m_imageCluedoObject4 = new QLabel(m_selectionObjectWidget);
    m_imageCluedoObject4->setObjectName(QStringLiteral("imageCluedoObject4"));
    m_imageCluedoObject4->setGeometry(QRect(530 * fW, 90 * fH, 150 * fW, 200 * fH));
    m_imageCluedoObject4->setFrameShape(QFrame::Box);
    m_imageCluedoObject4->setScaledContents(true);
    m_imageCluedoObject5 = new QLabel(m_selectionObjectWidget);
    m_imageCluedoObject5->setObjectName(QStringLiteral("imageCluedoObject5"));
    m_imageCluedoObject5->setGeometry(QRect(700 * fW, 90 * fH, 150 * fW, 200 * fH));
    m_imageCluedoObject5->setFrameShape(QFrame::Box);
    m_imageCluedoObject5->setScaledContents(true);
    m_imageCluedoObject6 = new QLabel(m_selectionObjectWidget);
    m_imageCluedoObject6->setObjectName(QStringLiteral("imageCluedoObject6"));
    m_imageCluedoObject6->setGeometry(QRect(870 * fW, 90 * fH, 150 * fW, 200 * fH));
    m_imageCluedoObject6->setFrameShape(QFrame::Box);
    m_imageCluedoObject6->setScaledContents(true);
    m_labelCurrentPlayer = new QLabel(m_centralwidget);
    m_labelCurrentPlayer->setObjectName(QString::fromUtf8("labelCurrentPlayer"));
    m_labelCurrentPlayer->setGeometry(QRect(1090 * fW, 80 * fH, 111 * fW, 16 * fH));
    m_listPlayers = new QListWidget(m_centralwidget);
    m_listPlayers->setObjectName(QString::fromUtf8("listPlayers"));
    m_listPlayers->setEnabled(false);
    m_listPlayers->setGeometry(QRect(1090 * fW, 110 * fH, 256 * fW, 131 * fH));
    m_buttonSelectObjects = new QPushButton(m_centralwidget);
    m_buttonSelectObjects->setObjectName(QStringLiteral("buttonSelectObjects"));
    m_buttonSelectObjects->setEnabled(false);
    m_buttonSelectObjects->setGeometry(QRect(1090 * fW, 260 * fH, 261 * fW, 41 * fH));
    m_buttonStartGame = new QPushButton(m_centralwidget);
    m_buttonStartGame->setObjectName(QString::fromUtf8("buttonStartGame"));
    m_buttonStartGame->setGeometry(QRect(60 * fW, screenGeometry.height() - 73 * fH, 161 * fW, 23 * fH));
    m_buttonConnectGame = new QPushButton(m_centralwidget);
    m_buttonConnectGame->setObjectName(QStringLiteral("buttonConnectGame"));
    m_buttonConnectGame->setGeometry(QRect(270 * fW, screenGeometry.height() - 73 * fH, 251 * fW, 23 * fH));
    m_quitButton = new QPushButton(m_centralwidget);
    m_quitButton->setObjectName(QString::fromUtf8("quitButton"));
    m_quitButton->setGeometry(QRect(1180 * fW, screenGeometry.height() - 73 * fH, 75 * fW, 23 * fH));
    this->setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QString::fromUtf8("menubar"));
    m_menubar->setGeometry(QRect(0, 0, 800 * fW, 21 * fH));
    this->setMenuBar(m_menubar);
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(m_statusbar);

    retranslateUi();

    QObject::connect(m_buttonSelectObjects, SIGNAL(pressed()), this, SLOT(buttonSelectObjects_clicked()));
    QObject::connect(m_buttonStartGame, SIGNAL(pressed()), this, SLOT(buttonStartGame_clicked()));
    QObject::connect(m_buttonConnectGame, SIGNAL(pressed()), this, SLOT(buttonConnectGame_clicked()));
    QObject::connect(m_quitButton, SIGNAL(pressed()), this, SLOT(buttonQuitGame_clicked()));
    QObject::connect(&GameController::getInstance(), SIGNAL(playersList_updated()), this, SLOT(playersList_updated()));
    QObject::connect(&GameController::getInstance(), SIGNAL(currentPlayerIndex_updated()), this, SLOT(currentPlayerIndex_updated()));
    QObject::connect(&GameController::getInstance(), SIGNAL(allCluedoObjects_distributed()), this, SLOT(allCluedoObjects_distributed()));
    QObject::connect(&GameController::getInstance(), &GameController::showObject_requested, this, &CluedoUI::showObject_requested);
    QObject::connect(&GameController::getInstance(), &GameController::askPlayerFromOtherPlayer_finished, this, &CluedoUI::askPlayerFromOtherPlayer_finished);
    QObject::connect(&GameController::getInstance(), &GameController::otherPlayerToldSuspicion, this, &CluedoUI::otherPlayerToldSuspicion);

    m_selectionObjectWidget->hide();
}

void CluedoUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("windowCluedo", "Cluedo", nullptr));
    m_labelCluedoObjects->setText(QApplication::translate("windowCluedo", "Deine T\303\244ter/Waffen/R\303\244ume", nullptr));
    m_labelCluedoObject1->setText(QString());
    m_labelCluedoObject2->setText(QString());
    m_labelCluedoObject3->setText(QString());
    m_labelCluedoObject4->setText(QString());
    m_labelCluedoObject5->setText(QString());
    m_labelCluedoObject6->setText(QString());
    m_imageCluedoObject1->setText(QString());
    m_imageCluedoObject2->setText(QString());
    m_imageCluedoObject3->setText(QString());
    m_imageCluedoObject4->setText(QString());
    m_imageCluedoObject5->setText(QString());
    m_imageCluedoObject6->setText(QString());
    m_labelCurrentPlayer->setText(QApplication::translate("windowCluedo", "Spieler", nullptr));
    m_buttonSelectObjects->setText(QApplication::translate("windowCluedo", "Frage Mitspieler / \n"
        "Verdacht aussprechen", nullptr));
    m_buttonStartGame->setText(QApplication::translate("windowCluedo", "Starte Spiel", nullptr));
    m_buttonConnectGame->setText(QApplication::translate("windowCluedo", "Verbinde zu bestehendem Spiel", nullptr));
    m_quitButton->setText(QApplication::translate("windowCluedo", "Quit", nullptr));
}

void CluedoUI::buttonSelectObjects_clicked()
{
    GameController& gameController = GameController::getInstance();
    std::vector<Player*>& players = gameController.getPlayers();
    Player* currentPlayer = gameController.getCurrentPlayer();

    m_selectObjectsUI = new SelectObjectsUI();
    m_selectObjectsUI->setWindowModality(Qt::ApplicationModal);
    m_selectObjectsUI->setAttribute(Qt::WA_DeleteOnClose);

    QObject::connect(m_selectObjectsUI, SIGNAL(askPlayer_finished()), this, SLOT(askPlayer_finished()));

    m_selectObjectsUI->show();
}

void CluedoUI::buttonStartGame_clicked()
{
    m_buttonConnectGame->setDisabled(true);

    m_startGameUI = new StartGameUI();
    m_startGameUI->setWindowModality(Qt::ApplicationModal);
    m_startGameUI->setAttribute(Qt::WA_DeleteOnClose);

#if WIN32
    m_tcpWinSocketServer = std::make_shared<TcpWinSocketServer>();
    m_startGameUI->setTcpWinSocketServer(m_tcpWinSocketServer);
#endif

    QObject::connect(m_startGameUI, SIGNAL(game_started_server()), this, SLOT(game_started_server()));

#if WIN32
    GameController::getInstance().setTcpWinSocketServer(m_tcpWinSocketServer);
#endif

    GameController::getInstance().registerRemoteServerMessages(false);

    m_startGameUI->show();

    m_buttonStartGame->setDisabled(true);
}

void CluedoUI::buttonConnectGame_clicked()
{
    m_connectServerUI = new ConnectServerUI();
    m_connectServerUI->setWindowModality(Qt::ApplicationModal);
    m_connectServerUI->setAttribute(Qt::WA_DeleteOnClose);

#if WIN32
    m_tcpWinSocketClient = std::make_shared<TcpWinSocketClient>();
    m_connectServerUI->setTcpWinSocketClient(m_tcpWinSocketClient);
#endif

    QObject::connect(m_connectServerUI, SIGNAL(game_started_client()), this, SLOT(game_started_client()));

    m_connectServerUI->show();
}

void CluedoUI::buttonQuitGame_clicked() {
#if WIN32
    if (m_tcpWinSocketClient) {
        m_tcpWinSocketClient->shutdownSocket();
    }
    if (m_tcpWinSocketServer) {
        m_tcpWinSocketServer->shutdownSockets();
    }
#endif
    close();
}

void CluedoUI::game_started_server()
{
    GameController::getInstance().sendPlayersListToClients();
    GameController::getInstance().selectAndDistributeCluedoObjects();
    GameController::getInstance().sendCurrentPlayerIndexToClients();
    selectCurrentPlayer();

    if (Player::PlayerType_Computer == GameController::getInstance().getCurrentPlayer()->getPlayerType()) {
        GameController::getInstance().askPlayer();
    }
}

void CluedoUI::game_started_client() {
    m_buttonStartGame->setDisabled(true);
    m_buttonConnectGame->setDisabled(true);

#if WIN32
    GameController::getInstance().setTcpWinSocketClient(m_tcpWinSocketClient);
#endif
    GameController::getInstance().registerRemoteServerMessages(true);
}

void CluedoUI::playersList_updated()
{
    m_listPlayers->clear();

    std::vector<Player*>& players = GameController::getInstance().getPlayers();

    for (Player* player : players)
    {
        m_listPlayers->addItem(QString::fromStdString(player->getName()));

        if ((Player::PlayerType_SelfServer == player->getPlayerType()) || (Player::PlayerType_SelfClient == player->getPlayerType()))
        {
            m_myPlayerSet = player->getPlayerSet();
        }
    }

    selectCurrentPlayer();
}

void CluedoUI::currentPlayerIndex_updated()
{
    selectCurrentPlayer();

    Player* currentPlayer = GameController::getInstance().getCurrentPlayer();
    if (currentPlayer && (Player::PlayerType_SelfServer == currentPlayer->getPlayerType()) || (Player::PlayerType_SelfClient == currentPlayer->getPlayerType())) {
        m_buttonSelectObjects->setEnabled(true);
    }
    else {
        m_buttonSelectObjects->setEnabled(false);
    }
}

void CluedoUI::allCluedoObjects_distributed()
{
    hideNotUsedCluedoObjects();
    fillCluedoObjects();
    m_selectionObjectWidget->show();
}

void CluedoUI::showObject_requested(int p_murderNumber, int p_weaponNumber, int p_roomNumber)
{
    Player* currentPlayer = GameController::getInstance().getCurrentPlayer();
    QString currentPlayerName = QString(currentPlayer->getName().c_str());
    m_selectObjectToShowUI = new SelectObjectToShowUI(currentPlayerName, p_murderNumber, p_weaponNumber, p_roomNumber);
    m_selectObjectToShowUI->setWindowModality(Qt::ApplicationModal);
    m_selectObjectToShowUI->setAttribute(Qt::WA_DeleteOnClose);

    QObject::connect(m_selectObjectToShowUI, &SelectObjectToShowUI::selectObjectToShowWindow_closed, this, &CluedoUI::selectObjectToShowWindow_closed);

    m_selectObjectToShowUI->show();
}

void CluedoUI::selectObjectToShowWindow_closed(bool p_objectCouldBeShown) {
    if (p_objectCouldBeShown) {
        GameController::getInstance().moveToNextPlayer();
    }
    else {
        Player* currentPlayer = GameController::getInstance().getCurrentPlayer();
        Player* selfPlayer = GameController::getInstance().getSelfPlayer();
        std::vector<Player*>& players = GameController::getInstance().getPlayers();
        for (int i = 0; i < players.size(); ++i) {
            if (players.at(i) == selfPlayer) {
                int nextIndex = i + 1;
                if (players.size() == nextIndex) {
                    nextIndex = 0;
                }
                if (players.at(nextIndex) == currentPlayer) {
                    GameController::getInstance().moveToNextPlayer();
                    break;
                }
            }
        }
    }
}

void CluedoUI::askPlayerFromOtherPlayer_finished(int p_askedMurderNumber, int p_askedWeaponNumber, int p_askedRoomNumber)
{
    Player* currentPlayer = GameController::getInstance().getCurrentPlayer();
    QString currentPlayerName = QString(currentPlayer->getName().c_str());
    m_askPlayerInfoUI = new AskPlayerUI(false, currentPlayerName, p_askedMurderNumber, p_askedWeaponNumber, p_askedRoomNumber);
    m_askPlayerInfoUI->setWindowModality(Qt::ApplicationModal);
    m_askPlayerInfoUI->setAttribute(Qt::WA_DeleteOnClose);

    Player* selfPlayer = GameController::getInstance().getSelfPlayer();
    m_askPlayerInfoUI->updateShownCluedoObject(selfPlayer);

    QObject::connect(m_askPlayerInfoUI, SIGNAL(askPlayerFromOtherPlayerWindow_closed()), this, SLOT(askPlayerFromOtherPlayerWindow_closed()));

    m_askPlayerInfoUI->show();
}

void CluedoUI::askPlayerFromOtherPlayerWindow_closed()
{
    GameController::getInstance().moveToNextPlayer();
}

void CluedoUI::askPlayer_finished() 
{
    m_buttonSelectObjects->setEnabled(false);
    GameController::getInstance().moveToNextPlayer();
}

void CluedoUI::otherPlayerToldSuspicion(bool p_isSuspicionCorrect, int p_suspectedMurderNumber, int p_suspectedWeaponNumber, int p_suspectedRoomNumber) {
    Player* currentPlayer = GameController::getInstance().getCurrentPlayer();
    CluedoObjectLoader& cluedoObjectLoader = CluedoObjectLoader::getInstance();

    QMessageBox msgBox;
    std::stringstream resultText;
    resultText << "Spieler " << currentPlayer->getName() << " spricht folgende Verd\303\244chtigung aus:\n";
    resultText << "T\303\244ter: " << cluedoObjectLoader.findCluedoObjectByNumber(p_suspectedMurderNumber)->getName() << "\n";
    resultText << "Waffe: " << cluedoObjectLoader.findCluedoObjectByNumber(p_suspectedWeaponNumber)->getName() << "\n";
    resultText << "Raum: " << cluedoObjectLoader.findCluedoObjectByNumber(p_suspectedRoomNumber)->getName() << "\n";
    resultText << "Die Verd\303\244chtigung ist: " << (p_isSuspicionCorrect ? "RICHTIG!" : "FALSCH!");
    msgBox.setText(resultText.str().c_str());
    msgBox.exec();
}

void CluedoUI::selectCurrentPlayer() {
    if (m_listPlayers->count() > 0)
    {
        int currentPlayerIndex = GameController::getInstance().getCurrentPlayerIndex();
        if (currentPlayerIndex >= 0) {
            m_listPlayers->item(currentPlayerIndex)->setSelected(true);
        }
    }
}

void CluedoUI::hideNotUsedCluedoObjects()
{
    int numberOfCluedoObjects = m_myPlayerSet->getNumberOfCluedoObjects();

    switch (numberOfCluedoObjects)
    {
    case 0:
        m_labelCluedoObject1->hide();
        m_imageCluedoObject1->hide();
    case 1:
        m_labelCluedoObject2->hide();
        m_imageCluedoObject2->hide();
    case 2:
        m_labelCluedoObject3->hide();
        m_imageCluedoObject3->hide();
    case 3:
        m_labelCluedoObject4->hide();
        m_imageCluedoObject4->hide();
    case 4:
        m_labelCluedoObject5->hide();
        m_imageCluedoObject5->hide();
    case 5:
        m_labelCluedoObject6->hide();
        m_imageCluedoObject6->hide();
        break;
    default:
        break;
    }
}

void CluedoUI::fillCluedoObjects()
{
    if (m_myPlayerSet)
    {
        std::vector<CluedoObject*>& cluedoObjects = m_myPlayerSet->getCluedoObjects();
        int index = 1;
        for (CluedoObject* cluedoObject : cluedoObjects)
        {
            QString name = QString::fromStdString(cluedoObject->getName());
            if (1 == index)
            {
                m_labelCluedoObject1->setText(name);
                QImage image = Utils::getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject1->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (2 == index)
            {
                m_labelCluedoObject2->setText(name);
                QImage image = Utils::getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject2->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (3 == index)
            {
                m_labelCluedoObject3->setText(name);
                QImage image = Utils::getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject3->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (4 == index)
            {
                m_labelCluedoObject4->setText(name);
                QImage image = Utils::getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject4->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (5 == index)
            {
                m_labelCluedoObject5->setText(name);
                QImage image = Utils::getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject5->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (6 == index)
            {
                m_labelCluedoObject6->setText(name);
                QImage image = Utils::getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject6->setPixmap(QPixmap::fromImage(image));
                }
            }
            index++;
        }
    }
}