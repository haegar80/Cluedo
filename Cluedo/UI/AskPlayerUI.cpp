#include "AskPlayerUI.h"
#include "../GameManager/GameController.h"
#include "../Model/Player.h"
#include "../Model/CluedoObject.h"
#include "../Utils/Utils.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QCloseEvent>

AskPlayerUI::AskPlayerUI(const QPixmap* p_selectedMurder, const QPixmap* p_selectedWeapon, const QPixmap* p_selectedRoom) :
    m_selectedMurder(p_selectedMurder),
    m_selectedWeapon(p_selectedWeapon),
    m_selectedRoom(p_selectedRoom)
{
    setupUi();
}

void AskPlayerUI::setupUi()
{
    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("mainWindowAskPlayer"));
    }

    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    this->resize(1101, 739);

    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_labelSelectedMurder = new QLabel(m_centralwidget);
    m_labelSelectedMurder->setObjectName(QStringLiteral("labelSelectedMurder"));
    m_labelSelectedMurder->setGeometry(QRect(10, 30, 111, 16));
    m_labelSelectedWeapon = new QLabel(m_centralwidget);
    m_labelSelectedWeapon->setObjectName(QStringLiteral("labelSelectedWeapon"));
    m_labelSelectedWeapon->setGeometry(QRect(260, 30, 111, 16));
    m_labelSelectedRoom = new QLabel(m_centralwidget);
    m_labelSelectedRoom->setObjectName(QStringLiteral("labelSelectedRoom"));
    m_labelSelectedRoom->setGeometry(QRect(510, 30, 111, 16));
    m_imageSelectedMurder = new QLabel(m_centralwidget);
    m_imageSelectedMurder->setObjectName(QStringLiteral("imageSelectedMurder"));
    m_imageSelectedMurder->setGeometry(QRect(10, 60, 211, 281));
    m_imageSelectedMurder->setFrameShape(QFrame::Box);
    m_imageSelectedMurder->setScaledContents(true);
    m_imageSelectedMurder->setPixmap(*m_selectedMurder);
    m_imageSelectedWeapon = new QLabel(m_centralwidget);
    m_imageSelectedWeapon->setObjectName(QStringLiteral("imageSelectedWeapon"));
    m_imageSelectedWeapon->setGeometry(QRect(260, 60, 211, 281));
    m_imageSelectedWeapon->setFrameShape(QFrame::Box);
    m_imageSelectedWeapon->setScaledContents(true);
    m_imageSelectedWeapon->setPixmap(*m_selectedWeapon);
    m_imageSelectedRoom = new QLabel(m_centralwidget);
    m_imageSelectedRoom->setObjectName(QStringLiteral("imageSelectedRoom"));
    m_imageSelectedRoom->setGeometry(QRect(510, 60, 281, 281));
    m_imageSelectedRoom->setFrameShape(QFrame::Box);
    m_imageSelectedRoom->setScaledContents(true);
    m_imageSelectedRoom->setPixmap(*m_selectedRoom);
   
    m_labelPlayer = new QLabel(m_centralwidget);
    m_labelPlayer->setObjectName(QStringLiteral("labelPlayer"));
    m_labelPlayer->setGeometry(QRect(20, 360, 161, 16));
    m_labelPlayerName = new QLabel(m_centralwidget);
    m_labelPlayerName->setObjectName(QStringLiteral("labelPlayerName"));
    m_labelPlayerName->setGeometry(QRect(20, 390, 201, 16));
    m_labelPlayerName->setAutoFillBackground(false);
    m_labelPlayerName->setFrameShape(QFrame::Box);
    m_labelPlayerName->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNoObjects = new QLabel(m_centralwidget);
    m_labelPlayerNoObjects->setObjectName(QStringLiteral("labelPlayerNoObjects"));
    m_labelPlayerNoObjects->setGeometry(QRect(20, 450, 201, 16));
    m_labelPlayerNameNoObjects1 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects1->setObjectName(QStringLiteral("labelPlayerNameNoObjects1"));
    m_labelPlayerNameNoObjects1->setGeometry(QRect(20, 480, 201, 16));
    m_labelPlayerNameNoObjects1->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects1->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects1->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNameNoObjects2 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects2->setObjectName(QStringLiteral("labelPlayerNameNoObjects2"));
    m_labelPlayerNameNoObjects2->setGeometry(QRect(20, 500, 201, 16));
    m_labelPlayerNameNoObjects2->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects2->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects2->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNameNoObjects3 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects3->setObjectName(QStringLiteral("labelPlayerNameNoObjects3"));
    m_labelPlayerNameNoObjects3->setGeometry(QRect(20, 520, 201, 16));
    m_labelPlayerNameNoObjects3->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects3->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects3->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNameNoObjects4 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects4->setObjectName(QStringLiteral("labelPlayerNameNoObjects4"));
    m_labelPlayerNameNoObjects4->setGeometry(QRect(20, 540, 201, 16));
    m_labelPlayerNameNoObjects4->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects4->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects4->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNameNoObjects5 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects5->setObjectName(QStringLiteral("labelPlayerNameNoObjects5"));
    m_labelPlayerNameNoObjects5->setGeometry(QRect(20, 560, 201, 16));
    m_labelPlayerNameNoObjects5->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects5->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects5->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNameNoObjects6 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects6->setObjectName(QStringLiteral("labelPlayerNameNoObjects6"));
    m_labelPlayerNameNoObjects6->setGeometry(QRect(20, 580, 201, 16));
    m_labelPlayerNameNoObjects6->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects6->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects6->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelShowedObject = new QLabel(m_centralwidget);
    m_labelShowedObject->setObjectName(QStringLiteral("labelShowedObject"));
    m_labelShowedObject->setGeometry(QRect(260, 360, 171, 16));
    m_imageShowedObject = new QLabel(m_centralwidget);
    m_imageShowedObject->setObjectName(QStringLiteral("imageShowedObject"));
    m_imageShowedObject->setGeometry(QRect(260, 390, 211, 281));
    m_imageShowedObject->setFrameShape(QFrame::Box);
    m_imageShowedObject->setScaledContents(true);
    m_buttonOk = new QPushButton(m_centralwidget);
    m_buttonOk->setObjectName(QStringLiteral("buttonOk"));
    m_buttonOk->setGeometry(QRect(20, 650, 75, 23));
    m_buttonOk->setEnabled(false);
    this->setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QStringLiteral("menubar"));
    m_menubar->setGeometry(QRect(0, 0, 1101, 21));
    this->setMenuBar(m_menubar);
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QStringLiteral("statusbar"));
    this->setStatusBar(m_statusbar);

    retranslateUi();

    QObject::connect(m_buttonOk, SIGNAL(pressed()), this, SLOT(close()));

    hideLabels();
}

void AskPlayerUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("mainWindowAskPlayer", "Ask Player", nullptr));
    m_labelSelectedMurder->setText(QApplication::translate("mainWindowAskPlayer", "Ausgew\303\244hlter Murder", nullptr));
    m_labelSelectedWeapon->setText(QApplication::translate("mainWindowAskPlayer", "Ausgew\303\244hlte Waffe", nullptr));
    m_labelSelectedRoom->setText(QApplication::translate("mainWindowAskPlayer", "Ausgew\303\244hlter Raum", nullptr));
    m_imageSelectedMurder->setText(QString());
    m_imageSelectedWeapon->setText(QString());
    m_imageSelectedRoom->setText(QString());
    m_labelPlayer->setText(QApplication::translate("mainWindowAskPlayer", "Spieler/In der/die etwas besitzt", nullptr));
    m_labelPlayerName->setText(QString());
    m_labelPlayerNoObjects->setText(QApplication::translate("mainWindowAskPlayer", "<html><head/><body><p>Spieler/In der/die nichts zeigen konnte</p></body></html>", nullptr));
    m_labelPlayerNameNoObjects1->setText(QString());
    m_labelPlayerNameNoObjects2->setText(QString());
    m_labelPlayerNameNoObjects3->setText(QString());
    m_labelPlayerNameNoObjects4->setText(QString());
    m_labelPlayerNameNoObjects5->setText(QString());
    m_labelPlayerNameNoObjects6->setText(QString());
    m_labelShowedObject->setText(QApplication::translate("mainWindowAskPlayer", "Gezeigter Murder/Waffe/Raum", nullptr));
    m_imageShowedObject->setText(QString());
    m_buttonOk->setText(QApplication::translate("mainWindowAskPlayer", "Ok", nullptr));
}

void AskPlayerUI::updateShownCluedoObject()
{
    Player* currentPlayer = GameController::getInstance().getCurrentPlayer();
    std::shared_ptr<PlayerSet> playerSet;
    if (nullptr != currentPlayer)
    {
        playerSet = currentPlayer->getPlayerSet();
    }

    if (playerSet)
    {
        CluedoObject* cluedoObject = playerSet->getLastShownCluedoObject();
        if (nullptr != cluedoObject)
        {
            checkAndupdateImageWithShownObject(currentPlayer, cluedoObject);
            updatePlayerLabelWithShownObject(playerSet.get(), cluedoObject);
            updatePlayerNoObjectLabels(playerSet.get());
        }
        else
        {
            m_labelPlayerName->setText(QString("Niemand anderes besitzt etwas davon!"));
            m_labelShowedObject->hide();
            m_imageShowedObject->hide();
        }
    }

    m_buttonOk->setEnabled(true);
}

void AskPlayerUI::closeEvent(QCloseEvent* event)
{
    emit askPlayerWindow_closed();
}

void AskPlayerUI::checkAndupdateImageWithShownObject(Player* p_currentPlayer, CluedoObject* p_shownCluedoObject)
{
    if ((Player::PlayerType_SelfServer == p_currentPlayer->getPlayerType()) || (Player::PlayerType_SelfClient == p_currentPlayer->getPlayerType()))
    {
        updateImageWithShownObject(p_shownCluedoObject);
    }
    else
    {
        std::vector<Player*>& allPlayers = GameController::getInstance().getPlayers();
        PlayerSet* currentPlayerSet = p_currentPlayer->getPlayerSet().get();
        Player* playerWithOwningObject = allPlayers.at(currentPlayerSet->getLastPlayerIndexWhoShowedCluedoObject());
        if ((Player::PlayerType_SelfServer == playerWithOwningObject->getPlayerType()) || (Player::PlayerType_SelfClient == playerWithOwningObject->getPlayerType()))
        {
            updateImageWithShownObject(p_shownCluedoObject);
        }
        else
        {
            m_labelShowedObject->hide();
            m_imageShowedObject->hide();
        }
    }
}

void AskPlayerUI::updateImageWithShownObject(CluedoObject* p_shownCluedoObject)
{
    QString itemText(p_shownCluedoObject->getName().c_str());
    QImage image = Utils::getImage(itemText);
    if (!image.isNull())
    {
        m_imageShowedObject->setPixmap(QPixmap::fromImage(image));
    }
}

void AskPlayerUI::hideLabels()
{
    m_labelPlayerNoObjects->hide();
    m_labelPlayerNameNoObjects1->hide();
    m_labelPlayerNameNoObjects2->hide();
    m_labelPlayerNameNoObjects3->hide();
    m_labelPlayerNameNoObjects4->hide();
    m_labelPlayerNameNoObjects5->hide();
    m_labelPlayerNameNoObjects6->hide();
}

void AskPlayerUI::updatePlayerLabelWithShownObject(PlayerSet* p_playerSet, CluedoObject* p_shownCluedoObject)
{
    std::vector<Player*>& allPlayers = GameController::getInstance().getPlayers();
    Player* playerWithOwningObject = allPlayers.at(p_playerSet->getLastPlayerIndexWhoShowedCluedoObject());
    m_labelPlayerName->setText(QString(playerWithOwningObject->getName().c_str()));
}

void AskPlayerUI::updatePlayerNoObjectLabels(PlayerSet* p_playerSet)
{
    std::vector<int>& playerIndicesWithNoShownObjects = p_playerSet->getPlayerIndicesWithNoShownCluedoObjects();
    std::vector<Player*>& allPlayers = GameController::getInstance().getPlayers();

    Player* player{ nullptr };

    if (playerIndicesWithNoShownObjects.size() > 0)
    {
        m_labelPlayerNoObjects->show();
    }

    switch (playerIndicesWithNoShownObjects.size())
    {
        case 6:
            player = allPlayers.at(playerIndicesWithNoShownObjects.at(5));
            m_labelPlayerNameNoObjects6->setText(QString(player->getName().c_str()));
            m_labelPlayerNameNoObjects6->show();
        case 5:
            player = allPlayers.at(playerIndicesWithNoShownObjects.at(4));
            m_labelPlayerNameNoObjects5->setText(QString(player->getName().c_str()));
            m_labelPlayerNameNoObjects5->show();
        case 4:
            player = allPlayers.at(playerIndicesWithNoShownObjects.at(3));
            m_labelPlayerNameNoObjects4->setText(QString(player->getName().c_str()));
            m_labelPlayerNameNoObjects4->show();
        case 3:
            player = allPlayers.at(playerIndicesWithNoShownObjects.at(2));
            m_labelPlayerNameNoObjects3->setText(QString(player->getName().c_str()));
            m_labelPlayerNameNoObjects3->show();
        case 2:
            player = allPlayers.at(playerIndicesWithNoShownObjects.at(1));
            m_labelPlayerNameNoObjects2->setText(QString(player->getName().c_str()));
            m_labelPlayerNameNoObjects2->show();
        case 1:
            player = allPlayers.at(playerIndicesWithNoShownObjects.at(0));
            m_labelPlayerNameNoObjects1->setText(QString(player->getName().c_str()));
            m_labelPlayerNameNoObjects1->show();
        default:
            break;
    }
}