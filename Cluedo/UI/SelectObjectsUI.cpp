#include "SelectObjectsUI.h"
#include "AskPlayerUI.h"
#include "../GameManager/CluedoObjectLoader.h"
#include "../GameManager/GameController.h"
#include "../Model/Player.h"
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
#include <memory>

SelectObjectsUI::SelectObjectsUI()
{
    setupUi();
    fillMurderList();
    fillWeaponList();
    fillRoomList();
}

void SelectObjectsUI::setupUi()
{
    if (this->objectName().isEmpty()) {
        this->setObjectName(QString::fromUtf8("windowSelectObjects"));
    }

    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    float fW = static_cast<float>(screenGeometry.width()) / static_cast<float>(referenceWidth);
    float fH = static_cast<float>(screenGeometry.height()) / static_cast<float>(referenceHeight);
    this->resize(1004 * fW, 652 * fH);

    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_selectionObjectWidget = new QWidget(m_centralwidget);
    m_selectionObjectWidget->setObjectName(QString::fromUtf8("selectionObjectWidget"));
    m_selectionObjectWidget->setGeometry(QRect(60 * fW, 50 * fH, 891 * fW, 511 * fH));
    m_labelMurderList = new QLabel(m_selectionObjectWidget);
    m_labelMurderList->setObjectName(QString::fromUtf8("labelMurderList"));
    m_labelMurderList->setGeometry(QRect(50 * fW, 0, 121 * fW, 16 * fH));
    m_listMurder = new QListWidget(m_selectionObjectWidget);
    m_listMurder->setObjectName(QString::fromUtf8("listMurder"));
    m_listMurder->setGeometry(QRect(50 * fW, 30 * fH, 211 * fW, 131 * fH));
    m_listMurder->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_imageSelectedMurder = new QLabel(m_selectionObjectWidget);
    m_imageSelectedMurder->setObjectName(QString::fromUtf8("imageSelectedMurder"));
    m_imageSelectedMurder->setGeometry(QRect(50 * fW, 200 * fH, 211 * fW, 281 * fH));
    m_imageSelectedMurder->setFrameShape(QFrame::Box);
    m_imageSelectedMurder->setScaledContents(true);
    m_labelWeaponList = new QLabel(m_selectionObjectWidget);
    m_labelWeaponList->setObjectName(QString::fromUtf8("labelWeaponList"));
    m_labelWeaponList->setGeometry(QRect(300 * fW, 0, 121 * fW, 16 * fH));
    m_listWeapon = new QListWidget(m_selectionObjectWidget);
    m_listWeapon->setObjectName(QString::fromUtf8("listWeapon"));
    m_listWeapon->setGeometry(QRect(300 * fW, 30 * fH, 211 * fW, 131 * fH));
    m_listWeapon->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_imageSelectedWeapon = new QLabel(m_selectionObjectWidget);
    m_imageSelectedWeapon->setObjectName(QString::fromUtf8("imageSelectedWeapon"));
    m_imageSelectedWeapon->setGeometry(QRect(300 * fW, 200 * fH, 211 * fW, 281 * fH));
    m_imageSelectedWeapon->setFrameShape(QFrame::Box);
    m_imageSelectedWeapon->setScaledContents(true);
    m_labelRoomList = new QLabel(m_selectionObjectWidget);
    m_labelRoomList->setObjectName(QString::fromUtf8("labelRoomList"));
    m_labelRoomList->setGeometry(QRect(550 * fW, 0, 121 * fW, 16 * fH));
    m_listRoom = new QListWidget(m_selectionObjectWidget);
    m_listRoom->setObjectName(QString::fromUtf8("listRoom"));
    m_listRoom->setGeometry(QRect(550 * fW, 30 * fH, 281 * fW, 131 * fH));
    m_listRoom->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_imageSelectedRoom = new QLabel(m_selectionObjectWidget);
    m_imageSelectedRoom->setObjectName(QString::fromUtf8("imageSelectedRoom"));
    m_imageSelectedRoom->setGeometry(QRect(550 * fW, 200 * fH, 281 * fW, 281 * fH));
    m_imageSelectedRoom->setFrameShape(QFrame::Box);
    m_imageSelectedRoom->setScaledContents(true);
    m_buttonOk = new QPushButton(m_centralwidget);
    m_buttonOk->setObjectName(QStringLiteral("buttonOk"));
    m_buttonOk->setGeometry(QRect(110 * fW, 580 * fH, 121 * fW, 23 * fH));
    m_buttonTellSuspicion = new QPushButton(m_centralwidget);
    m_buttonTellSuspicion->setObjectName(QStringLiteral("buttonTellSuspicion"));
    m_buttonTellSuspicion->setGeometry(QRect(260 * fW, 580 * fH, 181 * fW, 23 * fH));
    m_buttonAbort = new QPushButton(m_centralwidget);
    m_buttonAbort->setObjectName(QStringLiteral("buttonAbort"));
    m_buttonAbort->setGeometry(QRect(804 * fW, 580 * fH, 91 * fW, 23 * fH));
    this->setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QString::fromUtf8("menubar"));
    m_menubar->setGeometry(QRect(0, 0, 800 * fW, 21 * fH));
    this->setMenuBar(m_menubar);
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(m_statusbar);

    retranslateUi();

    QObject::connect(m_listMurder, SIGNAL(itemSelectionChanged()), this, SLOT(selectedMurder()));
    QObject::connect(m_listWeapon, SIGNAL(itemSelectionChanged()), this, SLOT(selectedWeapon()));
    QObject::connect(m_listRoom, SIGNAL(itemSelectionChanged()), this, SLOT(selectedRoom()));
    QObject::connect(m_buttonOk, SIGNAL(pressed()), this, SLOT(buttonOk_clicked()));
    QObject::connect(m_buttonTellSuspicion, SIGNAL(pressed()), this, SLOT(buttonTellSuspicion_clicked()));
    QObject::connect(m_buttonAbort, SIGNAL(pressed()), this, SLOT(close()));
    QObject::connect(&GameController::getInstance(), SIGNAL(askPlayerResponse_ready()), this, SLOT(askPlayerResponse_ready()));

    Player* currentPlayer = GameController::getInstance().getCurrentPlayer();
    if ((Player::PlayerType_SelfServer != currentPlayer->getPlayerType()) && (Player::PlayerType_SelfClient != currentPlayer->getPlayerType()))
    {
        disableSelectingWhenNotCurrentPlayer();
        fillSelectedObjectsWhenNotCurrentPlayer();
    }
}

void SelectObjectsUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("windowSelectObjects", "Select Objects", nullptr));
    m_imageSelectedMurder->setText(QString());
    m_labelMurderList->setText(QApplication::translate("windowSelectObjects", "Auswahl T\303\244ter", nullptr));
    m_labelWeaponList->setText(QApplication::translate("windowSelectObjects", "Auswahl Waffe", nullptr));
    m_labelRoomList->setText(QApplication::translate("windowSelectObjects", "Auswahl Raum", nullptr));
    m_buttonOk->setText(QApplication::translate("windowSelectObjects", "Frage", nullptr));
    m_buttonTellSuspicion->setText(QApplication::translate("mainWindowAskPlayer", "Verdacht aussprechen", nullptr));
    m_buttonAbort->setText(QApplication::translate("windowSelectObjects", "Abbrechen", nullptr));
}

void SelectObjectsUI::selectedMurder()
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
            QImage image = Utils::getImage(itemText);
            if (!image.isNull())
            {
                m_imageSelectedMurder->setPixmap(QPixmap::fromImage(image));
            }
        }
    }
}

void SelectObjectsUI::selectedWeapon()
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
            QImage image = Utils::getImage(itemText);
            if (!image.isNull())
            {
                m_imageSelectedWeapon->setPixmap(QPixmap::fromImage(image));
            }
        }
    }
}

void SelectObjectsUI::selectedRoom()
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
            QImage image = Utils::getImage(itemText);
            if (!image.isNull())
            {
                m_imageSelectedRoom->setPixmap(QPixmap::fromImage(image));
            }
        }
    }
}

void SelectObjectsUI::buttonOk_clicked()
{
    if (m_selectedMurder && m_selectedWeapon && m_selectedRoom) {
        Player* currentPlayer = GameController::getInstance().getCurrentPlayer();

        QString currentPlayerName = QString(currentPlayer->getName().c_str());
        m_askPlayerUI = new AskPlayerUI(true, currentPlayerName, m_listMurder->selectedItems().at(0)->text(), m_listWeapon->selectedItems().at(0)->text(), m_listRoom->selectedItems().at(0)->text());
        m_askPlayerUI->setWindowModality(Qt::ApplicationModal);
        m_askPlayerUI->setAttribute(Qt::WA_DeleteOnClose);

        QObject::connect(m_askPlayerUI, SIGNAL(askPlayerWindow_closed()), this, SLOT(askPlayerWindow_closed()));

        if ((Player::PlayerType_SelfServer == currentPlayer->getPlayerType()) || (Player::PlayerType_SelfClient == currentPlayer->getPlayerType()))
        {
            GameController::getInstance().askPlayer(m_listMurder->currentRow(), m_listWeapon->currentRow(), m_listRoom->currentRow());
            m_askPlayerUI->show();
        }
    }
}

void SelectObjectsUI::buttonTellSuspicion_clicked()
{
    if (m_selectedMurder && m_selectedWeapon && m_selectedRoom)
    {
        bool suspicionIsCorrect = GameController::getInstance().tellSuspicion(m_listMurder->currentRow(), m_listWeapon->currentRow(), m_listRoom->currentRow());

        QMessageBox msgBox;
        std::stringstream resultText;
        resultText << "Du hast " << (suspicionIsCorrect ? "GEWONNEN!" : "VERLOREN!");
        msgBox.setText(resultText.str().c_str());
        msgBox.exec();
    }
}

void SelectObjectsUI::askPlayerResponse_ready() {
    Player* currentPlayer = GameController::getInstance().getCurrentPlayer();
    m_askPlayerUI->updateShownCluedoObject(currentPlayer);
}

void SelectObjectsUI::askPlayerWindow_closed()
{
    emit askPlayer_finished();

    close();
}

void SelectObjectsUI::fillMurderList()
{
    std::vector<CluedoObject*> murders = CluedoObjectLoader::getInstance().getMurders();
    for (CluedoObject* murder : murders)
    {
        m_listMurder->addItem(QString::fromStdString(murder->getName()));
    }
}

void SelectObjectsUI::fillWeaponList()
{
    std::vector<CluedoObject*> weapons = CluedoObjectLoader::getInstance().getWeapons();
    for (CluedoObject* weapon : weapons)
    {
        m_listWeapon->addItem(QString(weapon->getName().c_str()));
    }
}

void SelectObjectsUI::fillRoomList()
{
    std::vector<CluedoObject*> rooms = CluedoObjectLoader::getInstance().getRooms();
    for (CluedoObject* room : rooms)
    {
        m_listRoom->addItem(QString(room->getName().c_str()));
    }
}

void SelectObjectsUI::disableSelectingWhenNotCurrentPlayer()
{
    m_listMurder->setEnabled(false);
    m_listWeapon->setEnabled(false);
    m_listRoom->setEnabled(false);
    m_buttonTellSuspicion->hide();
}

void SelectObjectsUI::fillSelectedObjectsWhenNotCurrentPlayer()
{
    Player* currentPlayer = GameController::getInstance().getCurrentPlayer();
    std::shared_ptr<PlayerSet> currentPlayerSet = currentPlayer->getPlayerSet();
    
    CluedoObject* murder = currentPlayerSet->getLastAskedMurder();
    if (nullptr != murder)
    {
        QImage image = Utils::getImage(QString(murder->getName().c_str()));
        if (!image.isNull())
        {
            m_imageSelectedMurder->setPixmap(QPixmap::fromImage(image));
        }
    }
    
    CluedoObject* weapon = currentPlayerSet->getLastAskedWeapon();
    if (nullptr != weapon)
    {
        QImage image = Utils::getImage(QString(weapon->getName().c_str()));
        if (!image.isNull())
        {
            m_imageSelectedWeapon->setPixmap(QPixmap::fromImage(image));
        }
    }

    CluedoObject* room = currentPlayerSet->getLastAskedRoom();
    if (nullptr != room)
    {
        QImage image = Utils::getImage(QString(room->getName().c_str()));
        if (!image.isNull())
        {
            m_imageSelectedRoom->setPixmap(QPixmap::fromImage(image));
        }
    }

    std::stringstream buttonText;
    buttonText << currentPlayer->getName() << " fragt";

    m_buttonOk->setText(QApplication::translate("windowSelectObjects", buttonText.str().c_str(), nullptr));
}