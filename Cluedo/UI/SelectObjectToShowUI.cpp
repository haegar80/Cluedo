#include "SelectObjectToShowUI.h"
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
#include <QMessageBox>
#include <sstream>

SelectObjectToShowUI::SelectObjectToShowUI(const QString& p_askedPlayer, const QString& p_selectedMurder, const QString& p_selectedWeapon, const QString& p_selectedRoom) :
    m_askedPlayer(p_askedPlayer),
    m_selectedMurder(p_selectedMurder),
    m_selectedWeapon(p_selectedWeapon),
    m_selectedRoom(p_selectedRoom)
{
    setupUi();
}

void SelectObjectToShowUI::setupUi()
{
    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("mainWindowSelectObjectToShow"));
    }

    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    this->resize(1101, 879);

    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_labelAsk = new QLabel(m_centralwidget);
    m_labelAsk->setObjectName(QStringLiteral("labelAsk"));
    m_labelAsk->setGeometry(QRect(10, 20, 71, 16));
    m_labelAskedPerson = new QLabel(m_centralwidget);
    m_labelAskedPerson->setObjectName(QStringLiteral("labelAskedPerson"));
    m_labelAskedPerson->setGeometry(QRect(90, 20, 401, 16));
    m_labelSelectedMurder = new QLabel(m_centralwidget);
    m_labelSelectedMurder->setObjectName(QStringLiteral("labelSelectedMurder"));
    m_labelSelectedMurder->setGeometry(QRect(10, 50, 111, 16));
    m_labelSelectedWeapon = new QLabel(m_centralwidget);
    m_labelSelectedWeapon->setObjectName(QStringLiteral("labelSelectedWeapon"));
    m_labelSelectedWeapon->setGeometry(QRect(260, 50, 111, 16));
    m_labelSelectedRoom = new QLabel(m_centralwidget);
    m_labelSelectedRoom->setObjectName(QStringLiteral("labelSelectedRoom"));
    m_labelSelectedRoom->setGeometry(QRect(510, 50, 111, 16));
    m_imageSelectedMurder = new QLabel(m_centralwidget);
    m_imageSelectedMurder->setObjectName(QStringLiteral("imageSelectedMurder"));
    m_imageSelectedMurder->setGeometry(QRect(10, 80, 211, 281));
    m_imageSelectedMurder->setFrameShape(QFrame::Box);
    m_imageSelectedMurder->setScaledContents(true);
    QImage image = Utils::getImage(m_selectedMurder);
    if (!image.isNull())
    {
        m_imageSelectedMurder->setPixmap(QPixmap::fromImage(image));
    }
    m_imageSelectedWeapon = new QLabel(m_centralwidget);
    m_imageSelectedWeapon->setObjectName(QStringLiteral("imageSelectedWeapon"));
    m_imageSelectedWeapon->setGeometry(QRect(260, 80, 211, 281));
    m_imageSelectedWeapon->setFrameShape(QFrame::Box);
    m_imageSelectedWeapon->setScaledContents(true);
    image = Utils::getImage(m_selectedWeapon);
    if (!image.isNull())
    {
        m_imageSelectedWeapon->setPixmap(QPixmap::fromImage(image));
    }
    m_imageSelectedRoom = new QLabel(m_centralwidget);
    m_imageSelectedRoom->setObjectName(QStringLiteral("imageSelectedRoom"));
    m_imageSelectedRoom->setGeometry(QRect(510, 80, 281, 281));
    m_imageSelectedRoom->setFrameShape(QFrame::Box);
    m_imageSelectedRoom->setScaledContents(true);
    image = Utils::getImage(m_selectedRoom);
    if (!image.isNull())
    {
        m_imageSelectedRoom->setPixmap(QPixmap::fromImage(image));
    }

    m_labelAvailableObjects = new QLabel(m_centralwidget);
    m_labelAvailableObjects->setObjectName(QStringLiteral("labelAvailableObjects"));
    m_labelAvailableObjects->setGeometry(QRect(270, 400, 251, 16));
    m_labelAvailableMurder = new QLabel(m_centralwidget);
    m_labelAvailableMurder->setObjectName(QStringLiteral("labelAvailableMurder"));
    m_labelAvailableMurder->setGeometry(QRect(10, 430, 51, 16));
    m_labelAvailableWeapon = new QLabel(m_centralwidget);
    m_labelAvailableWeapon->setObjectName(QStringLiteral("labelAvailableWeapon"));
    m_labelAvailableWeapon->setGeometry(QRect(270, 430, 51, 16));
    m_labelAvailableRoom = new QLabel(m_centralwidget);
    m_labelAvailableRoom->setObjectName(QStringLiteral("labelAvailableRoom"));
    m_labelAvailableRoom->setGeometry(QRect(520, 430, 111, 16));
    m_imageAvailableMurder = new QLabel(m_centralwidget);
    m_imageAvailableMurder->setObjectName(QStringLiteral("imageAvailableMurder"));
    m_imageAvailableMurder->setGeometry(QRect(10, 460, 211, 281));
    m_imageAvailableMurder->setFrameShape(QFrame::Box);
    m_imageAvailableMurder->setScaledContents(true);
    m_imageAvailableWeapon = new QLabel(m_centralwidget);
    m_imageAvailableWeapon->setObjectName(QStringLiteral("imageAvailableWeapon"));
    m_imageAvailableWeapon->setGeometry(QRect(260, 460, 211, 281));
    m_imageAvailableWeapon->setFrameShape(QFrame::Box);
    m_imageAvailableWeapon->setScaledContents(true);
    m_imageAvailableRoom = new QLabel(m_centralwidget);
    m_imageAvailableRoom->setObjectName(QStringLiteral("imageAvailableRoom"));
    m_imageAvailableRoom->setGeometry(QRect(510, 460, 281, 281));
    m_imageAvailableRoom->setFrameShape(QFrame::Box);
    m_imageAvailableRoom->setScaledContents(true);
    m_buttonShowMurder = new QPushButton(m_centralwidget);
    m_buttonShowMurder->setObjectName(QStringLiteral("buttonShowMurder"));
    m_buttonShowMurder->setGeometry(QRect(60, 750, 111, 23));
    m_buttonShowMurder->setEnabled(false);
    m_buttonShowWeapon = new QPushButton(m_centralwidget);
    m_buttonShowWeapon->setObjectName(QStringLiteral("buttonShowWeapon"));
    m_buttonShowWeapon->setGeometry(QRect(310, 750, 111, 23));
    m_buttonShowWeapon->setEnabled(false);
    m_buttonShowRoom = new QPushButton(m_centralwidget);
    m_buttonShowRoom->setObjectName(QStringLiteral("buttonShowRoom"));
    m_buttonShowRoom->setGeometry(QRect(590, 750, 111, 23));
    m_buttonShowRoom->setEnabled(false);

    m_buttonOk = new QPushButton(m_centralwidget);
    m_buttonOk->setObjectName(QStringLiteral("buttonOk"));
    m_buttonOk->setGeometry(QRect(10, 810, 75, 23));
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

    QObject::connect(m_buttonShowMurder, SIGNAL(pressed()), this, SLOT(buttonShowMurder_clicked()));
    QObject::connect(m_buttonShowWeapon, SIGNAL(pressed()), this, SLOT(buttonShowWeapon_clicked()));
    QObject::connect(m_buttonShowRoom, SIGNAL(pressed()), this, SLOT(buttonShowRoom_clicked()));
    QObject::connect(m_buttonOk, SIGNAL(pressed()), this, SLOT(buttonOk_clicked()));

    initObjectsToShow();
}

void SelectObjectToShowUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("mainWindowSelectObjectToShow", "Show Object", nullptr));
    m_labelAsk->setText(QApplication::translate("mainWindowSelectObjectToShow", "Es fragt dich:", nullptr));
    m_labelAskedPerson->setText(m_askedPlayer);
    m_labelSelectedMurder->setText(QApplication::translate("mainWindowSelectObjectToShow", "Ausgew\303\244hlter Murder", nullptr));
    m_labelSelectedWeapon->setText(QApplication::translate("mainWindowSelectObjectToShow", "Ausgew\303\244hlte Waffe", nullptr));
    m_labelSelectedRoom->setText(QApplication::translate("mainWindowSelectObjectToShow", "Ausgew\303\244hlter Raum", nullptr));
    m_imageSelectedMurder->setText(QString());
    m_imageSelectedWeapon->setText(QString());
    m_imageSelectedRoom->setText(QString());
    m_labelAvailableObjects->setText(QApplication::translate("mainWindowSelectObjectToShow", "Karten von obiger Anfrage, die du selber besitzt:", nullptr));
    m_labelAvailableMurder->setText(QApplication::translate("mainWindowSelectObjectToShow", "Murder", nullptr));
    m_labelAvailableWeapon->setText(QApplication::translate("mainWindowSelectObjectToShow", "Waffe", nullptr));
    m_labelAvailableRoom->setText(QApplication::translate("mainWindowSelectObjectToShow", "Raum", nullptr));
    m_imageAvailableMurder->setText(QString());
    m_imageAvailableWeapon->setText(QString());
    m_imageAvailableRoom->setText(QString());
    m_buttonShowMurder->setText(QApplication::translate("mainWindowSelectObjectToShow", "Will ich zeigen", nullptr));
    m_buttonShowWeapon->setText(QApplication::translate("mainWindowSelectObjectToShow", "Will ich zeigen", nullptr));
    m_buttonShowRoom->setText(QApplication::translate("mainWindowSelectObjectToShow", "Will ich zeigen", nullptr));
    m_buttonOk->setText(QApplication::translate("mainWindowAskPlayer", "Ok", nullptr));
}

void SelectObjectToShowUI::buttonShowMurder_clicked()
{
    m_buttonOk->setEnabled(true);

    m_showMurder = true;
    m_imageAvailableWeapon->hide();
    m_imageAvailableRoom->hide();
}

void SelectObjectToShowUI::buttonShowWeapon_clicked()
{
    m_buttonOk->setEnabled(true);

    m_showWeapon = true;
    m_imageAvailableMurder->hide();
    m_imageAvailableRoom->hide();
}

void SelectObjectToShowUI::buttonShowRoom_clicked()
{
    m_buttonOk->setEnabled(true);

    m_showRoom = true;
    m_imageAvailableMurder->hide();
    m_imageAvailableWeapon->hide();
}

void SelectObjectToShowUI::buttonOk_clicked()
{
    this->close();
}

void SelectObjectToShowUI::initObjectsToShow() {
    Player* currentPlayer = GameController::getInstance().getCurrentPlayer();
    if (currentPlayer) {
        std::shared_ptr<PlayerSet> playerSet = currentPlayer->getPlayerSet();
        std::vector<CluedoObject*>& cluedoObjects = playerSet->getCluedoObjects();
        bool hasObject = false;
        for (CluedoObject* cluedoObject : cluedoObjects) {
            if (cluedoObject->getName() == m_selectedMurder.toStdString()) {
                hasObject = true;
                m_buttonShowMurder->setEnabled(true);
                QImage image = Utils::getImage(m_selectedMurder);
                if (!image.isNull())
                {
                    m_imageAvailableMurder->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (cluedoObject->getName() == m_selectedWeapon.toStdString()) {
                hasObject = true;
                m_buttonShowWeapon->setEnabled(true);
                QImage image = Utils::getImage(m_selectedWeapon);
                if (!image.isNull())
                {
                    m_imageAvailableWeapon->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (cluedoObject->getName() == m_selectedRoom.toStdString()) {
                hasObject = true;
                m_buttonShowRoom->setEnabled(true);
                QImage image = Utils::getImage(m_selectedRoom);
                if (!image.isNull())
                {
                    m_imageAvailableRoom->setPixmap(QPixmap::fromImage(image));
                }
            }
        }

        if (!hasObject) {
            m_buttonOk->setEnabled(true);

            QMessageBox msgBox;
            std::stringstream ss;
            ss << "Du kannst nichts zeigen, du hast keine von den gew\303\274nschten Karten!";
            msgBox.setText(ss.str().c_str());
            msgBox.exec();
        }
    }
}