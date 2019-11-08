#include "AskPlayerUI.h"
#include "../GameManager/GameController.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QCheckBox>
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
    m_labelPlayer->setGeometry(QRect(20, 360, 47, 13));
    m_labelPlayer1 = new QLabel(m_centralwidget);
    m_labelPlayer1->setObjectName(QStringLiteral("labelPlayer1"));
    m_labelPlayer1->setGeometry(QRect(20, 390, 141, 16));
    m_labelPlayer1->setAutoFillBackground(false);
    m_labelPlayer1->setFrameShape(QFrame::Box);
    m_labelPlayer1->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayer2 = new QLabel(m_centralwidget);
    m_labelPlayer2->setObjectName(QStringLiteral("labelPlayer2"));
    m_labelPlayer2->setGeometry(QRect(20, 420, 141, 16));
    m_labelPlayer2->setFrameShape(QFrame::Box);
    m_labelPlayer2->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_labelPlayer3 = new QLabel(m_centralwidget);
    m_labelPlayer3->setObjectName(QStringLiteral("labelPlayer3"));
    m_labelPlayer3->setGeometry(QRect(20, 450, 141, 16));
    m_labelPlayer3->setFrameShape(QFrame::Box);
    m_labelPlayer3->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    m_checkBoxPlayer1 = new QCheckBox(m_centralwidget);
    m_checkBoxPlayer1->setObjectName(QStringLiteral("checkBoxPlayer1"));
    m_checkBoxPlayer1->setGeometry(QRect(170, 390, 70, 17));
    m_checkBoxPlayer2 = new QCheckBox(m_centralwidget);
    m_checkBoxPlayer2->setObjectName(QStringLiteral("checkBoxPlayer2"));
    m_checkBoxPlayer2->setGeometry(QRect(170, 420, 70, 17));
    m_checkBoxPlayer3 = new QCheckBox(m_centralwidget);
    m_checkBoxPlayer3->setObjectName(QStringLiteral("checkBoxPlayer3"));
    m_checkBoxPlayer3->setGeometry(QRect(170, 450, 70, 17));
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
    m_labelPlayer->setText(QApplication::translate("mainWindowAskPlayer", "Spieler", nullptr));
    m_labelPlayer1->setText(QString());
    m_labelPlayer2->setText(QString());
    m_labelPlayer3->setText(QString());
    m_checkBoxPlayer1->setText(QString());
    m_checkBoxPlayer2->setText(QString());
    m_checkBoxPlayer3->setText(QString());
    m_labelShowedObject->setText(QApplication::translate("mainWindowAskPlayer", "Gezeigter Murder/Waffe/Raum", nullptr));
    m_imageShowedObject->setText(QString());
    m_buttonOk->setText(QApplication::translate("mainWindowAskPlayer", "Ok", nullptr));
}

void AskPlayerUI::closeEvent(QCloseEvent* event)
{
    emit askPlayerWindow_closed();
}