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
            QString itemText(cluedoObject->getName().c_str());
            QImage image = Utils::getImage(itemText);
            if (!image.isNull())
            {
                m_imageShowedObject->setPixmap(QPixmap::fromImage(image));
            }

            std::multimap<int, CluedoObject*>& cluedoObjectsFromOtherPlayers = playerSet->getCluedoObjectsFromOtherPlayers();
            for (std::pair<int, CluedoObject*> cluedoObjectFromOtherPlayer : cluedoObjectsFromOtherPlayers)
            {
                if (cluedoObject == cluedoObjectFromOtherPlayer.second)
                {
                    std::vector<Player*>& allPlayers = GameController::getInstance().getPlayers();
                    Player* playerWithOwningObject = allPlayers.at(cluedoObjectFromOtherPlayer.first);
                    m_labelPlayerName->setText(QString(playerWithOwningObject->getName().c_str()));
                    break;
                }
            }
        }
        else
        {
            m_labelPlayerName->setText(QString("Niemand anderes besitzt etwas davon!"));
        }
    }
}

void AskPlayerUI::closeEvent(QCloseEvent* event)
{
    emit askPlayerWindow_closed();
}