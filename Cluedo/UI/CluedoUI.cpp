#include "CluedoUI.h"
#include "StartGameUI.h"
#include "AskPlayerUI.h"
#include "../Model/Player.h"
#include "../GameManager/CluedoObjectLoader.h"
#include "../GameManager/GameController.h"
#include <QtCore/QDir>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QImageReader>

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
    m_imageSelectedMurder->setGeometry(QRect(50, 200, 211, 281));
    m_imageSelectedMurder->setFrameShape(QFrame::Box);
    m_imageSelectedMurder->setScaledContents(true);
    m_labelWeaponList = new QLabel(m_selectionObjectWidget);
    m_labelWeaponList->setObjectName(QString::fromUtf8("labelWeaponList"));
    m_labelWeaponList->setGeometry(QRect(300, 0, 91, 16));
    m_listWeapon = new QListWidget(m_selectionObjectWidget);
    m_listWeapon->setObjectName(QString::fromUtf8("listWeapon"));
    m_listWeapon->setGeometry(QRect(300, 30, 211, 131));
    m_listWeapon->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_imageSelectedWeapon = new QLabel(m_selectionObjectWidget);
    m_imageSelectedWeapon->setObjectName(QString::fromUtf8("imageSelectedWeapon"));
    m_imageSelectedWeapon->setGeometry(QRect(300, 200, 211, 281));
    m_imageSelectedWeapon->setFrameShape(QFrame::Box);
    m_imageSelectedWeapon->setScaledContents(true);
    m_labelRoomList = new QLabel(m_selectionObjectWidget);
    m_labelRoomList->setObjectName(QString::fromUtf8("labelRoomList"));
    m_labelRoomList->setGeometry(QRect(550, 0, 81, 16));
    m_listRoom = new QListWidget(m_selectionObjectWidget);
    m_listRoom->setObjectName(QString::fromUtf8("listRoom"));
    m_listRoom->setGeometry(QRect(550, 30, 281, 131));
    m_listRoom->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_imageSelectedRoom = new QLabel(m_selectionObjectWidget);
    m_imageSelectedRoom->setObjectName(QString::fromUtf8("imageSelectedRoom"));
    m_imageSelectedRoom->setGeometry(QRect(550, 200, 281, 281));
    m_imageSelectedRoom->setFrameShape(QFrame::Box);
    m_imageSelectedRoom->setScaledContents(true);
    m_labelPlayers = new QLabel(m_centralwidget);
    m_labelPlayers->setObjectName(QString::fromUtf8("labelPlayers"));
    m_labelPlayers->setGeometry(QRect(970, 50, 47, 13));
    m_listPlayers = new QListWidget(m_centralwidget);
    m_listPlayers->setObjectName(QString::fromUtf8("listPlayers"));
    m_listPlayers->setEnabled(false);
    m_listPlayers->setGeometry(QRect(970, 80, 256, 131));
    m_buttonAskPlayers = new QPushButton(m_centralwidget);
    m_buttonAskPlayers->setObjectName(QString::fromUtf8("buttonAskPlayers"));
    m_buttonAskPlayers->setEnabled(false);
    m_buttonAskPlayers->setGeometry(QRect(970, 230, 121, 23));
    m_buttonStartGame = new QPushButton(m_centralwidget);
    m_buttonStartGame->setObjectName(QString::fromUtf8("buttonStartGame"));
    m_buttonStartGame->setGeometry(QRect(60, screenGeometry.height() - 73, 75, 23));
    m_quitButton = new QPushButton(m_centralwidget);
    m_quitButton->setObjectName(QString::fromUtf8("quitButton"));
    m_quitButton->setGeometry(QRect(170, screenGeometry.height() - 73, 75, 23));
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
    QObject::connect(m_buttonAskPlayers, SIGNAL(pressed()), this, SLOT(askPlayers_clicked()));
    QObject::connect(m_buttonStartGame, SIGNAL(pressed()), this, SLOT(buttonStartGame_clicked()));
    QObject::connect(m_quitButton, SIGNAL(pressed()), this, SLOT(close()));

    auto playerUpdateCallback = [this]() { updatePlayers(); };
    GameController::getInstance().registerPlayerUpdateCallback(playerUpdateCallback);
}

void CluedoUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("MainWindow", "Cluedo", 0));
    m_imageSelectedMurder->setText(QString());
    m_labelMurderList->setText(QApplication::translate("MainWindow", "Auswahl T\303\244ter", 0));
    m_labelWeaponList->setText(QApplication::translate("MainWindow", "Auswahl Waffe", 0));
    m_labelRoomList->setText(QApplication::translate("MainWindow", "Auswahl Raum", 0));
    m_labelPlayers->setText(QApplication::translate("MainWindow", "Mitspieler", 0));
    m_buttonAskPlayers->setText(QApplication::translate("MainWindow", "Frage Mitspieler", 0));
    m_buttonStartGame->setText(QApplication::translate("MainWindow", "Starte Spiel", 0));
    m_quitButton->setText(QApplication::translate("MainWindow", "Quit", 0));
}

void CluedoUI::updatePlayers()
{
    std::vector<Player*>& players = GameController::getInstance().getPlayers();

    for (Player* player : players)
    {
        m_listPlayers->addItem(QString::fromStdString(player->getName()));
    }

    if (m_listPlayers->count() > 0)
    {
        m_listPlayers->item(m_currentPlayerIndex)->setSelected(true);
        m_buttonAskPlayers->setEnabled(true);
    }
}

void CluedoUI::nextPlayerReady()
{
    m_currentPlayerIndex++;
    if (m_listPlayers->count() == m_currentPlayerIndex)
    {
        m_currentPlayerIndex = 0;
    }
    m_listPlayers->item(m_currentPlayerIndex)->setSelected(true);
}

void CluedoUI::selectedMurder()
{
    m_selectedMurder = false;
    QList<QListWidgetItem*> selectedItems = m_listMurder->selectedItems();
    if (selectedItems.count() > 0)
    {
        QListWidgetItem* item = m_listMurder->selectedItems().at(0);
        if (nullptr != item)
        {
            m_selectedMurder = true;
            QString itemText = item->text();
            QImage image = getImage(itemText);
            if (!image.isNull())
            {
                m_imageSelectedMurder->setPixmap(QPixmap::fromImage(image));
            }
        }
    }
}

void CluedoUI::selectedWeapon()
{
    m_selectedWeapon = false;
    QList<QListWidgetItem*> selectedItems = m_listWeapon->selectedItems();
    if (selectedItems.count() > 0)
    {
        QListWidgetItem* item = m_listWeapon->selectedItems().at(0);
        if (nullptr != item)
        {
            m_selectedWeapon = true;
            QString itemText = item->text();
            QImage image = getImage(itemText);
            if (!image.isNull())
            {
                m_imageSelectedWeapon->setPixmap(QPixmap::fromImage(image));
            }
        }
    }
}

void CluedoUI::selectedRoom()
{
    m_selectedRoom = false;
    QList<QListWidgetItem*> selectedItems = m_listRoom->selectedItems();
    if (selectedItems.count() > 0)
    {
        QListWidgetItem* item = m_listRoom->selectedItems().at(0);
        if (nullptr != item)
        {
            m_selectedRoom = true;
            QString itemText = item->text();
            QImage image = getImage(itemText);
            if (!image.isNull())
            {
                m_imageSelectedRoom->setPixmap(QPixmap::fromImage(image));
            }
        }
    }
}

void CluedoUI::askPlayers_clicked()
{
    std::vector<Player*>& players = GameController::getInstance().getPlayers();
    Player* currentPlayer = players.at(m_currentPlayerIndex);
    if (currentPlayer->getSelf())
    {
        if (m_selectedMurder && m_selectedWeapon && m_selectedRoom)
        {
            m_askPlayerUI = new AskPlayerUI(m_imageSelectedMurder->pixmap(), m_imageSelectedWeapon->pixmap(), m_imageSelectedRoom->pixmap());
            m_askPlayerUI->setWindowModality(Qt::ApplicationModal);
            m_askPlayerUI->setAttribute(Qt::WA_DeleteOnClose);

            QObject::connect(m_askPlayerUI, SIGNAL(askPlayerWindow_closed()), this, SLOT(askPlayerWindow_closed()));

            m_askPlayerUI->show();

            GameController::getInstance().askPlayer(m_listMurder->currentRow(), m_listWeapon->currentRow(), m_listRoom->currentRow(), m_listPlayers->currentRow());
        }
    }
    else
    {
        nextPlayerReady();
    }   
}

void CluedoUI::askPlayerWindow_closed()
{
    nextPlayerReady();
}

void CluedoUI::buttonStartGame_clicked()
{
    m_startGameUI = new StartGameUI();
    m_startGameUI->setWindowModality(Qt::ApplicationModal);
    m_startGameUI->setAttribute(Qt::WA_DeleteOnClose);
    m_startGameUI->show();

    m_buttonStartGame->setDisabled(true);
}

void CluedoUI::fillMurderList()
{
    std::vector<CluedoObject*> murders = CluedoObjectLoader::getInstance().getMurders();
    for (CluedoObject* murder : murders)
    {
        m_listMurder->addItem(QString::fromStdString(murder->getName()));
    }
}

void CluedoUI::fillWeaponList()
{
    std::vector<CluedoObject*> weapons = CluedoObjectLoader::getInstance().getWeapons();
    for (CluedoObject* weapon : weapons)
    {
        m_listWeapon->addItem(QString(weapon->getName().c_str()));
    }
}

void CluedoUI::fillRoomList()
{
    std::vector<CluedoObject*> rooms = CluedoObjectLoader::getInstance().getRooms();
    for (CluedoObject* room : rooms)
    {
        m_listRoom->addItem(QString(room->getName().c_str()));
    }
}

QString CluedoUI::getFilePath(const QString& p_itemText)
{
    QString path = p_itemText;
    QString extension(".jpg");
    path += extension;

    QDir dirPath(QString("Pics"));
    if (dirPath.exists())
    {
        QFileInfo file(dirPath, path);
        path = file.absoluteFilePath();
    }

    return path;
}

QImage CluedoUI::getImage(const QString& p_itemText)
{
    QImageReader imageReader(getFilePath(p_itemText));
    imageReader.setAutoTransform(true);
    QImage image = imageReader.read();

    return image;
}