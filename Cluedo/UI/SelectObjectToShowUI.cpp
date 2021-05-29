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

SelectObjectToShowUI::SelectObjectToShowUI(const QString& p_askedPlayer, int p_murderNumber, int p_weaponNumber, int p_roomNumber) :
    m_askedPlayer(p_askedPlayer),
    m_selectedMurderNumber(p_murderNumber),
    m_selectedWeaponNumber(p_weaponNumber),
    m_selectedRoomNumber(p_roomNumber)
{
    CluedoObject* selectedMurder = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(m_selectedMurderNumber);
    if (selectedMurder) {
        m_selectedMurderString = QString(selectedMurder->getName().c_str());
    }
    CluedoObject* selectedWeapon = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(m_selectedWeaponNumber);
    if (selectedWeapon) {
        m_selectedWeaponString = QString(selectedWeapon->getName().c_str());
    }
    CluedoObject* selectedRoom = CluedoObjectLoader::getInstance().findCluedoObjectByNumber(m_selectedRoomNumber);
    if (selectedRoom) {
        m_selectedRoomString = QString(selectedRoom->getName().c_str());
    }

    setupUi();
}

void SelectObjectToShowUI::setupUi()
{
    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("mainWindowSelectObjectToShow"));
    }

    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    float fW = static_cast<float>(screenGeometry.width()) / static_cast<float>(referenceWidth);
    float fH = static_cast<float>(screenGeometry.height()) / static_cast<float>(referenceHeight);
    this->resize(845 * fW, 879 * fH);

    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_labelAsk = new QLabel(m_centralwidget);
    m_labelAsk->setObjectName(QStringLiteral("labelAsk"));
    m_labelAsk->setGeometry(QRect(10 * fW, 20 * fH, 91 * fW, 16 * fH));
    m_labelAskedPerson = new QLabel(m_centralwidget);
    m_labelAskedPerson->setObjectName(QStringLiteral("labelAskedPerson"));
    m_labelAskedPerson->setGeometry(QRect(110 * fW, 20 * fH, 371 * fW, 16 * fH));
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
    QImage image = Utils::getImage(m_selectedMurderString);
    if (!image.isNull())
    {
        m_imageSelectedMurder->setPixmap(QPixmap::fromImage(image));
    }
    m_imageSelectedWeapon = new QLabel(m_centralwidget);
    m_imageSelectedWeapon->setObjectName(QStringLiteral("imageSelectedWeapon"));
    m_imageSelectedWeapon->setGeometry(QRect(260 * fW, 80 * fH, 211 * fW, 281 * fH));
    m_imageSelectedWeapon->setFrameShape(QFrame::Box);
    m_imageSelectedWeapon->setScaledContents(true);
    image = Utils::getImage(m_selectedWeaponString);
    if (!image.isNull())
    {
        m_imageSelectedWeapon->setPixmap(QPixmap::fromImage(image));
    }
    m_imageSelectedRoom = new QLabel(m_centralwidget);
    m_imageSelectedRoom->setObjectName(QStringLiteral("imageSelectedRoom"));
    m_imageSelectedRoom->setGeometry(QRect(510 * fW, 80 * fH, 281 * fW, 281 * fH));
    m_imageSelectedRoom->setFrameShape(QFrame::Box);
    m_imageSelectedRoom->setScaledContents(true);
    image = Utils::getImage(m_selectedRoomString);
    if (!image.isNull()) 
    {
        m_imageSelectedRoom->setPixmap(QPixmap::fromImage(image));
    }

    m_labelAvailableObjects = new QLabel(m_centralwidget);
    m_labelAvailableObjects->setObjectName(QStringLiteral("labelAvailableObjects"));
    m_labelAvailableObjects->setGeometry(QRect(10 * fW, 400 * fH, 341 * fW, 16 * fH));
    m_labelAvailableMurder = new QLabel(m_centralwidget);
    m_labelAvailableMurder->setObjectName(QStringLiteral("labelAvailableMurder"));
    m_labelAvailableMurder->setGeometry(QRect(10 * fW, 430 * fH, 81 * fW, 16 * fH));
    m_labelAvailableWeapon = new QLabel(m_centralwidget);
    m_labelAvailableWeapon->setObjectName(QStringLiteral("labelAvailableWeapon"));
    m_labelAvailableWeapon->setGeometry(QRect(270 * fW, 430 * fH, 81 * fW, 16 * fH));
    m_labelAvailableRoom = new QLabel(m_centralwidget);
    m_labelAvailableRoom->setObjectName(QStringLiteral("labelAvailableRoom"));
    m_labelAvailableRoom->setGeometry(QRect(520 * fW, 430 * fH, 81 * fW, 16 * fH));
    m_imageAvailableMurder = new QLabel(m_centralwidget);
    m_imageAvailableMurder->setObjectName(QStringLiteral("imageAvailableMurder"));
    m_imageAvailableMurder->setGeometry(QRect(10 * fW, 460 * fH, 211 * fW, 281 * fH));
    m_imageAvailableMurder->setFrameShape(QFrame::Box);
    m_imageAvailableMurder->setScaledContents(true);
    m_imageAvailableWeapon = new QLabel(m_centralwidget);
    m_imageAvailableWeapon->setObjectName(QStringLiteral("imageAvailableWeapon"));
    m_imageAvailableWeapon->setGeometry(QRect(260 * fW, 460 * fH, 211 * fW, 281 * fH));
    m_imageAvailableWeapon->setFrameShape(QFrame::Box);
    m_imageAvailableWeapon->setScaledContents(true);
    m_imageAvailableRoom = new QLabel(m_centralwidget);
    m_imageAvailableRoom->setObjectName(QStringLiteral("imageAvailableRoom"));
    m_imageAvailableRoom->setGeometry(QRect(510 * fW, 460 * fH, 281 * fW, 281 * fH));
    m_imageAvailableRoom->setFrameShape(QFrame::Box);
    m_imageAvailableRoom->setScaledContents(true);
    m_buttonShowMurder = new QPushButton(m_centralwidget);
    m_buttonShowMurder->setObjectName(QStringLiteral("buttonShowMurder"));
    m_buttonShowMurder->setGeometry(QRect(60 * fW, 750 * fH, 111 * fW, 23 * fH));
    m_buttonShowMurder->setEnabled(false);
    m_buttonShowWeapon = new QPushButton(m_centralwidget);
    m_buttonShowWeapon->setObjectName(QStringLiteral("buttonShowWeapon"));
    m_buttonShowWeapon->setGeometry(QRect(310 * fW, 750 * fH, 111 * fW, 23 * fH));
    m_buttonShowWeapon->setEnabled(false);
    m_buttonShowRoom = new QPushButton(m_centralwidget);
    m_buttonShowRoom->setObjectName(QStringLiteral("buttonShowRoom"));
    m_buttonShowRoom->setGeometry(QRect(590 * fW, 750 * fH, 111 * fW, 23 * fH));
    m_buttonShowRoom->setEnabled(false);

    m_buttonOk = new QPushButton(m_centralwidget);
    m_buttonOk->setObjectName(QStringLiteral("buttonOk"));
    m_buttonOk->setGeometry(QRect(10 * fW, 810 * fH, 75 * fW, 23 * fH));
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
    m_labelSelectedMurder->setText(QApplication::translate("mainWindowSelectObjectToShow", "Ausgew\303\244hlter T\303\244ter", nullptr));
    m_labelSelectedWeapon->setText(QApplication::translate("mainWindowSelectObjectToShow", "Ausgew\303\244hlte Waffe", nullptr));
    m_labelSelectedRoom->setText(QApplication::translate("mainWindowSelectObjectToShow", "Ausgew\303\244hlter Raum", nullptr));
    m_imageSelectedMurder->setText(QString());
    m_imageSelectedWeapon->setText(QString());
    m_imageSelectedRoom->setText(QString());
    m_labelAvailableObjects->setText(QApplication::translate("mainWindowSelectObjectToShow", "Karten von obiger Anfrage, die du selber besitzt:", nullptr));
    m_labelAvailableMurder->setText(QApplication::translate("mainWindowSelectObjectToShow", "T\303\244ter", nullptr));
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
    m_buttonShowWeapon->hide();
    m_buttonShowRoom->hide();
}

void SelectObjectToShowUI::buttonShowWeapon_clicked()
{
    m_buttonOk->setEnabled(true);

    m_showWeapon = true;
    m_imageAvailableMurder->hide();
    m_imageAvailableRoom->hide();
    m_buttonShowMurder->hide();
    m_buttonShowRoom->hide();
}

void SelectObjectToShowUI::buttonShowRoom_clicked()
{
    m_buttonOk->setEnabled(true);

    m_showRoom = true;
    m_imageAvailableMurder->hide();
    m_imageAvailableWeapon->hide();
    m_buttonShowMurder->hide();
    m_buttonShowWeapon->hide();
}

void SelectObjectToShowUI::buttonOk_clicked()
{
    if (m_showMurder) {
        GameController::getInstance().askPlayerResponse(m_selectedMurderNumber);
    }
    else if (m_showWeapon) {
        GameController::getInstance().askPlayerResponse(m_selectedWeaponNumber);
    }
    else if (m_showRoom) {
        GameController::getInstance().askPlayerResponse(m_selectedRoomNumber);
    }
    else {
        GameController::getInstance().askPlayerResponse(0);
    }

    this->close();

    emit selectObjectToShowWindow_closed();
}

void SelectObjectToShowUI::initObjectsToShow() {
    Player* selfPlayer = GameController::getInstance().getSelfPlayer();
    if (selfPlayer) {
        std::shared_ptr<PlayerSet> playerSet = selfPlayer->getPlayerSet();
        std::vector<CluedoObject*>& cluedoObjects = playerSet->getCluedoObjects();
        bool hasObject = false;
        for (CluedoObject* cluedoObject : cluedoObjects) {
            if (cluedoObject->getNumber() == m_selectedMurderNumber) {
                hasObject = true;
                m_buttonShowMurder->setEnabled(true);
                QImage image = Utils::getImage(m_selectedMurderString);
                if (!image.isNull())
                {
                    m_imageAvailableMurder->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (cluedoObject->getNumber() == m_selectedWeaponNumber) {
                hasObject = true;
                m_buttonShowWeapon->setEnabled(true);
                QImage image = Utils::getImage(m_selectedWeaponString);
                if (!image.isNull())
                {
                    m_imageAvailableWeapon->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (cluedoObject->getNumber() == m_selectedRoomNumber) {
                hasObject = true;
                m_buttonShowRoom->setEnabled(true);
                QImage image = Utils::getImage(m_selectedRoomString);
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

            m_imageAvailableMurder->hide();
            m_imageAvailableWeapon->hide();
            m_imageAvailableRoom->hide();
            m_buttonShowMurder->hide();
            m_buttonShowWeapon->hide();
            m_buttonShowRoom->hide();
        }
    }
}