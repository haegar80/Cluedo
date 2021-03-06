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

AskPlayerUI::AskPlayerUI(bool p_showShowedObject, const QString& p_askedPlayer, const QString& p_selectedMurderString, const QString& p_selectedWeaponString, const QString& p_selectedRoomString) :
    m_showShowedObject(p_showShowedObject),
    m_askedPlayer(p_askedPlayer),
    m_selectedMurderString(p_selectedMurderString),
    m_selectedWeaponString(p_selectedWeaponString),
    m_selectedRoomString(p_selectedRoomString)
{
    createImages();

    setupUi();
}

AskPlayerUI::AskPlayerUI(bool p_showShowedObject, const QString& p_askedPlayer, int p_selectedMurderNumber, int p_selectedWeaponNumber, int p_selectedRoomNumber) :
    m_showShowedObject(p_showShowedObject),
    m_askedPlayer(p_askedPlayer)
{
    CluedoObject* selectedMurder = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(p_selectedMurderNumber);
    if (selectedMurder) {
        m_selectedMurderString = QString(selectedMurder->getName().c_str());
    }
    CluedoObject* selectedWeapon = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(p_selectedWeaponNumber);
    if (selectedWeapon) {
        m_selectedWeaponString = QString(selectedWeapon->getName().c_str());
    }
    CluedoObject* selectedRoom = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(p_selectedRoomNumber);
    if (selectedRoom) {
        m_selectedRoomString = QString(selectedRoom->getName().c_str());
    }

    createImages();

    setupUi();
}

void AskPlayerUI::setupUi()
{
    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("mainWindowAskPlayer"));
    }

    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    float fW = static_cast<float>(screenGeometry.width()) / static_cast<float>(referenceWidth);
    float fH = static_cast<float>(screenGeometry.height()) / static_cast<float>(referenceHeight);
    this->resize(1101 * fW, 839 * fH);

    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_labelAsk = new QLabel(m_centralwidget);
    m_labelAsk->setObjectName(QStringLiteral("labelAsk"));
    m_labelAsk->setGeometry(QRect(10 * fW, 20 * fH, 71 * fW, 16 * fH));
    m_labelAskedPerson = new QLabel(m_centralwidget);
    m_labelAskedPerson->setObjectName(QStringLiteral("labelAskedPerson"));
    m_labelAskedPerson->setGeometry(QRect(90 * fW, 20 * fH, 371 * fW, 16 * fH));
    m_labelSelectedMurder = new QLabel(m_centralwidget);
    m_labelSelectedMurder->setObjectName(QStringLiteral("labelSelectedMurder"));
    m_labelSelectedMurder->setGeometry(QRect(10 * fW, 50 * fH, 161 * fW, 16 * fH));
    m_labelSelectedWeapon = new QLabel(m_centralwidget);
    m_labelSelectedWeapon->setObjectName(QStringLiteral("labelSelectedWeapon"));
    m_labelSelectedWeapon->setGeometry(QRect(260 * fW, 50 * fH, 161 * fW, 16 * fH));
    m_labelSelectedRoom = new QLabel(m_centralwidget);
    m_labelSelectedRoom->setObjectName(QStringLiteral("labelSelectedRoom"));
    m_labelSelectedRoom->setGeometry(QRect(510 * fW, 50 * fH, 151 * fW, 16 * fH));
    m_imageSelectedMurder = new QLabel(m_centralwidget);
    m_imageSelectedMurder->setObjectName(QStringLiteral("imageSelectedMurder"));
    m_imageSelectedMurder->setGeometry(QRect(10 * fW, 80 * fH, 211 * fW, 281 * fH));
    m_imageSelectedMurder->setFrameShape(QFrame::Box);
    m_imageSelectedMurder->setScaledContents(true);
    m_imageSelectedMurder->setPixmap(m_selectedMurder);
    m_imageSelectedWeapon = new QLabel(m_centralwidget);
    m_imageSelectedWeapon->setObjectName(QStringLiteral("imageSelectedWeapon"));
    m_imageSelectedWeapon->setGeometry(QRect(260 * fW, 80 * fH, 211 * fW, 281 * fH));
    m_imageSelectedWeapon->setFrameShape(QFrame::Box);
    m_imageSelectedWeapon->setScaledContents(true);
    m_imageSelectedWeapon->setPixmap(m_selectedWeapon);
    m_imageSelectedRoom = new QLabel(m_centralwidget);
    m_imageSelectedRoom->setObjectName(QStringLiteral("imageSelectedRoom"));
    m_imageSelectedRoom->setGeometry(QRect(510 * fW, 80 * fH, 281 * fW, 281 * fH));
    m_imageSelectedRoom->setFrameShape(QFrame::Box);
    m_imageSelectedRoom->setScaledContents(true);
    m_imageSelectedRoom->setPixmap(m_selectedRoom);
    m_labelSelectedMurderName = new QLabel(m_centralwidget);
    m_labelSelectedMurderName->setObjectName(QStringLiteral("labelSelectedMurderName"));
    m_labelSelectedMurderName->setGeometry(QRect(10 * fW, 370 * fH, 211 * fW, 16 * fH));
    m_labelSelectedWeaponName = new QLabel(m_centralwidget);
    m_labelSelectedWeaponName->setObjectName(QStringLiteral("labelSelectedWeaponName"));
    m_labelSelectedWeaponName->setGeometry(QRect(260 * fW, 370 * fH, 211 * fW, 16 * fH));
    m_labelSelectedRoomName = new QLabel(m_centralwidget);
    m_labelSelectedRoomName->setObjectName(QStringLiteral("labelSelectedRoomName"));
    m_labelSelectedRoomName->setGeometry(QRect(510 * fW, 370 * fH, 211 * fW, 16 * fH));
   
    m_labelPlayer = new QLabel(m_centralwidget);
    m_labelPlayer->setObjectName(QStringLiteral("labelPlayer"));
    m_labelPlayer->setGeometry(QRect(10 * fW, 410 * fH, 221 * fW, 16 * fH));
    m_labelPlayerName = new QLabel(m_centralwidget);
    m_labelPlayerName->setObjectName(QStringLiteral("labelPlayerName"));
    m_labelPlayerName->setGeometry(QRect(10 * fW, 440 * fH, 201 * fW, 16 * fH));
    m_labelPlayerName->setAutoFillBackground(false);
    m_labelPlayerName->setFrameShape(QFrame::Box);
    m_labelPlayerName->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNoObjects = new QLabel(m_centralwidget);
    m_labelPlayerNoObjects->setObjectName(QStringLiteral("labelPlayerNoObjects"));
    m_labelPlayerNoObjects->setGeometry(QRect(10 * fW, 520 * fH, 231 * fW, 16 * fH));
    m_labelPlayerNameNoObjects1 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects1->setObjectName(QStringLiteral("labelPlayerNameNoObjects1"));
    m_labelPlayerNameNoObjects1->setGeometry(QRect(10 * fW, 550 * fH, 201 * fW, 21 * fH));
    m_labelPlayerNameNoObjects1->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects1->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects1->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNameNoObjects2 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects2->setObjectName(QStringLiteral("labelPlayerNameNoObjects2"));
    m_labelPlayerNameNoObjects2->setGeometry(QRect(10 * fW, 580 * fH, 201 * fW, 21 * fH));
    m_labelPlayerNameNoObjects2->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects2->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects2->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNameNoObjects3 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects3->setObjectName(QStringLiteral("labelPlayerNameNoObjects3"));
    m_labelPlayerNameNoObjects3->setGeometry(QRect(10 * fW, 610 * fH, 201 * fW, 21 * fH));
    m_labelPlayerNameNoObjects3->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects3->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects3->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNameNoObjects4 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects4->setObjectName(QStringLiteral("labelPlayerNameNoObjects4"));
    m_labelPlayerNameNoObjects4->setGeometry(QRect(10 * fW, 640 * fH, 201 * fW, 21 * fH));
    m_labelPlayerNameNoObjects4->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects4->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects4->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNameNoObjects5 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects5->setObjectName(QStringLiteral("labelPlayerNameNoObjects5"));
    m_labelPlayerNameNoObjects5->setGeometry(QRect(10 * fW, 670 * fH, 201 * fW, 21 * fH));
    m_labelPlayerNameNoObjects5->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects5->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects5->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayerNameNoObjects6 = new QLabel(m_centralwidget);
    m_labelPlayerNameNoObjects6->setObjectName(QStringLiteral("labelPlayerNameNoObjects6"));
    m_labelPlayerNameNoObjects6->setGeometry(QRect(10 * fW, 700 * fH, 201 * fW, 21 * fH));
    m_labelPlayerNameNoObjects6->setAutoFillBackground(false);
    m_labelPlayerNameNoObjects6->setFrameShape(QFrame::Box);
    m_labelPlayerNameNoObjects6->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelShowedObject = new QLabel(m_centralwidget);
    m_labelShowedObject->setObjectName(QStringLiteral("labelShowedObject"));
    m_labelShowedObject->setGeometry(QRect(260 * fW, 410 * fH, 251 * fW, 16 * fH));
    if (!m_showShowedObject) {
        m_labelShowedObject->hide();
    }
    m_imageShowedObject = new QLabel(m_centralwidget);
    m_imageShowedObject->setObjectName(QStringLiteral("imageShowedObject"));
    m_imageShowedObject->setGeometry(QRect(260 * fW, 440 * fH, 211 * fW, 281 * fH));
    m_imageShowedObject->setFrameShape(QFrame::Box);
    m_imageShowedObject->setScaledContents(true);
    if (!m_showShowedObject) {
        m_imageShowedObject->hide();
    }
    m_buttonOk = new QPushButton(m_centralwidget);
    m_buttonOk->setObjectName(QStringLiteral("buttonOk"));
    m_buttonOk->setGeometry(QRect(10 * fW, 760 * fH, 75 * fW, 23 * fH));
    m_buttonOk->setEnabled(false);
    this->setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QStringLiteral("menubar"));
    m_menubar->setGeometry(QRect(0, 0, 1101 * fW, 21 * fH));
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
    m_labelAsk->setText(QApplication::translate("mainWindowAskPlayer", "Es fragt:", nullptr));
    m_labelAskedPerson->setText(m_askedPlayer);
    m_labelSelectedMurder->setText(QApplication::translate("mainWindowAskPlayer", "Ausgew\303\244hlter T\303\244ter", nullptr));
    m_labelSelectedWeapon->setText(QApplication::translate("mainWindowAskPlayer", "Ausgew\303\244hlte Waffe", nullptr));
    m_labelSelectedRoom->setText(QApplication::translate("mainWindowAskPlayer", "Ausgew\303\244hlter Raum", nullptr));
    m_imageSelectedMurder->setText(QString());
    m_imageSelectedWeapon->setText(QString());
    m_imageSelectedRoom->setText(QString());
    m_labelSelectedMurderName->setText(m_selectedMurderString);
    m_labelSelectedWeaponName->setText(m_selectedWeaponString);
    m_labelSelectedRoomName->setText(m_selectedRoomString);

    m_labelPlayer->setText(QApplication::translate("mainWindowAskPlayer", "Spieler/In der/die etwas besitzt", nullptr));
    m_labelPlayerName->setText(QString());
    m_labelPlayerNoObjects->setText(QApplication::translate("mainWindowAskPlayer", "Spieler/In der/die nichts besitzt", nullptr));
    m_labelPlayerNameNoObjects1->setText(QString());
    m_labelPlayerNameNoObjects2->setText(QString());
    m_labelPlayerNameNoObjects3->setText(QString());
    m_labelPlayerNameNoObjects4->setText(QString());
    m_labelPlayerNameNoObjects5->setText(QString());
    m_labelPlayerNameNoObjects6->setText(QString());
    m_labelShowedObject->setText(QApplication::translate("mainWindowAskPlayer", "Gezeigter T\303\244ter/Waffe/Raum", nullptr));
    m_imageShowedObject->setText(QString());
    m_buttonOk->setText(QApplication::translate("mainWindowAskPlayer", "Ok", nullptr));
}

void AskPlayerUI::updateShownCluedoObject(Player* p_player)
{
    std::shared_ptr<PlayerSet> playerSet;
    if (nullptr != p_player)
    {
        playerSet = p_player->getPlayerSet();
    }

    if (playerSet)
    {
        CluedoObject* cluedoObject = playerSet->getLastShownCluedoObject();
        if (m_showShowedObject && (nullptr != cluedoObject))
        {
            if (m_showShowedObject) {
                checkAndupdateImageWithShownObject(p_player, cluedoObject);
            }
            updatePlayerLabelWithShownObject(playerSet.get(), cluedoObject);
            updatePlayerNoObjectLabels(playerSet.get());
        }
        else if (!m_showShowedObject) {
            updatePlayerLabelWithShownObject(playerSet.get(), cluedoObject);
            updatePlayerNoObjectLabels(playerSet.get());
        }
        else
        {
            m_labelPlayerName->setText(QString("Niemand!"));
            m_labelShowedObject->hide();
            m_imageShowedObject->hide();
        }
    }

    m_buttonOk->setEnabled(true);
}

void AskPlayerUI::closeEvent(QCloseEvent* event)
{
    emit askPlayerWindow_closed();
    emit askPlayerFromOtherPlayerWindow_closed();
}

void AskPlayerUI::createImages() {
    QImage image = Utils::getImage(m_selectedMurderString);
    if (!image.isNull())
    {
        m_selectedMurder = QPixmap::fromImage(image);
    }

    image = Utils::getImage(m_selectedWeaponString);
    if (!image.isNull())
    {
        m_selectedWeapon = QPixmap::fromImage(image);
    }

    image = Utils::getImage(m_selectedRoomString);
    if (!image.isNull())
    {
        m_selectedRoom = QPixmap::fromImage(image);
    }
}

void AskPlayerUI::checkAndupdateImageWithShownObject(Player* p_player, CluedoObject* p_shownCluedoObject)
{
    if ((Player::PlayerType_SelfServer == p_player->getPlayerType()) || (Player::PlayerType_SelfClient == p_player->getPlayerType()))
    {
        updateImageWithShownObject(p_shownCluedoObject);
    }
    else
    {
        std::vector<Player*>& allPlayers = GameController::getInstance().getPlayers();
        PlayerSet* playerSet = p_player->getPlayerSet().get();
        Player* playerWithOwningObject = allPlayers.at(playerSet->getLastPlayerIndexWhoShowedCluedoObject());
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
    if (p_playerSet->getLastPlayerIndexWhoShowedCluedoObject() >= 0) {
        Player* playerWithOwningObject = allPlayers.at(p_playerSet->getLastPlayerIndexWhoShowedCluedoObject());
        m_labelPlayerName->setText(QString(playerWithOwningObject->getName().c_str()));
    }
    else {
        m_labelPlayerName->setText(QString("Niemand besitzt etwas!"));
    }
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