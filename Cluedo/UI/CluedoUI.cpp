#include "CluedoUI.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <memory>;

CluedoUI::CluedoUI()
{
    setupUi();
    fillMurderList();
    fillWeaponList();
    fillRoomList();
}

void CluedoUI::setupUi()
{
    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("MainWindow"));
    }

    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    this->resize(screenGeometry.width(), screenGeometry.height());
    this->setMinimumSize(QSize(200, 200));

    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_selectionObjectWidget = new QWidget(m_centralwidget);
    m_selectionObjectWidget->setObjectName(QString::fromUtf8("selectionObjectWidget"));
    m_selectionObjectWidget->setGeometry(QRect(60, 50, 891, 681));
    m_labelMurderList = new QLabel(m_selectionObjectWidget);
    m_labelMurderList->setObjectName(QString::fromUtf8("labelMurderList"));
    m_labelMurderList->setGeometry(QRect(50, 0, 81, 16));
    m_listMurder = new QListWidget(m_selectionObjectWidget);
    m_listMurder->setObjectName(QString::fromUtf8("listMurder"));
    m_listMurder->setGeometry(QRect(50, 30, 211, 131));
    m_listMurder->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_imageSelectedMurder = new QLabel(m_selectionObjectWidget);
    m_imageSelectedMurder->setObjectName(QString::fromUtf8("imageSelectedMurder"));
    m_imageSelectedMurder->setGeometry(QRect(50, 200, 211, 131));
    m_imageSelectedMurder->setFrameShape(QFrame::Box);
    m_imageSelectedMurder->setScaledContents(true);
    m_labelWeaponList = new QLabel(m_selectionObjectWidget);
    m_labelWeaponList->setObjectName(QString::fromUtf8("labelWeaponList"));
    m_labelWeaponList->setGeometry(QRect(300, 0, 91, 16));
    m_listWeapon = new QListWidget(m_selectionObjectWidget);
    m_listWeapon->setObjectName(QString::fromUtf8("listWeapon"));
    m_listWeapon->setGeometry(QRect(300, 30, 211, 131));
    m_listWeapon->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_labelRoomList = new QLabel(m_selectionObjectWidget);
    m_labelRoomList->setObjectName(QString::fromUtf8("labelRoomList"));
    m_labelRoomList->setGeometry(QRect(550, 0, 81, 16));
    m_listRoom = new QListWidget(m_selectionObjectWidget);
    m_listRoom->setObjectName(QString::fromUtf8("listRoom"));
    m_listRoom->setGeometry(QRect(550, 30, 211, 131));
    m_listRoom->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_quitButton = new QPushButton(m_centralwidget);
    m_quitButton->setObjectName(QString::fromUtf8("quitButton"));
    m_quitButton->setGeometry(QRect(20, screenGeometry.height() - 73, 75, 23));
    this->setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QString::fromUtf8("menubar"));
    m_menubar->setGeometry(QRect(0, 0, 800, 21));
    this->setMenuBar(m_menubar);
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(m_statusbar);

    retranslateUi();

    QObject::connect(m_listMurder, SIGNAL(itemSelectionChanged()), this, SLOT(selectedMurder()));
    QObject::connect(m_listWeapon, SIGNAL(itemSelectionChanged()), this, SLOT(selectedWeapon()));
    QObject::connect(m_listRoom, SIGNAL(itemSelectionChanged()), this, SLOT(selectedRoom()));
    QObject::connect(m_quitButton, SIGNAL(pressed()), this, SLOT(close()));
}

void CluedoUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("MainWindow", "Cluedo", 0));
    m_imageSelectedMurder->setText(QString());
    m_labelMurderList->setText(QApplication::translate("MainWindow", "Auswahl T\303\244ter", 0));
    m_labelWeaponList->setText(QApplication::translate("MainWindow", "Auswahl Waffe", 0));
    m_labelRoomList->setText(QApplication::translate("MainWindow", "Auswahl Raum", 0));
    m_quitButton->setText(QApplication::translate("MainWindow", "Quit", 0));
}

void CluedoUI::selectedMurder()
{
    
}

void CluedoUI::selectedWeapon()
{
   
}

void CluedoUI::selectedRoom()
{
  
}

void CluedoUI::fillMurderList()
{
    std::vector<CluedoObject*> murders = m_cluedoObjectLoader.getMurders();
    for (CluedoObject* murder : murders)
    {
        m_listMurder->addItem(QString::fromStdString(murder->getName()));
    }
}

void CluedoUI::fillWeaponList()
{
    std::vector<CluedoObject*> weapons = m_cluedoObjectLoader.getWeapons();
    for (CluedoObject* weapon : weapons)
    {
        m_listWeapon->addItem(QString(weapon->getName().c_str()));
    }
}

void CluedoUI::fillRoomList()
{
    std::vector<CluedoObject*> rooms = m_cluedoObjectLoader.getRooms();
    for (CluedoObject* room : rooms)
    {
        m_listRoom->addItem(QString(room->getName().c_str()));
    }
}