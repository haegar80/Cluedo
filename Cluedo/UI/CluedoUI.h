#pragma once

#include <QtWidgets/QMainWindow>

class StartGameUI;

class QWidget;
class QPushButton;
class QListWidget;
class QPushButton;
class QLabel;
class QMenuBar;
class QStatusBar;
class QString;
class QImage;

/// author: Copyright by Marcel Fuchs
class CluedoUI : public QMainWindow
{
    Q_OBJECT

public:
    CluedoUI();
    virtual ~CluedoUI() = default;

    void setupUi();
    void retranslateUi();

    void updatePlayers();

    public slots:
    void selectedMurder();
    void selectedWeapon();
    void selectedRoom();
    void askPlayers_clicked();
    void buttonStartGame_clicked();

private:
    QWidget * m_centralwidget;
    QWidget* m_selectionObjectWidget;
    QLabel* m_labelMurderList;
    QListWidget* m_listMurder;
    QLabel* m_imageSelectedMurder;
    QLabel* m_labelWeaponList;
    QListWidget* m_listWeapon;
    QLabel* m_imageSelectedWeapon;
    QLabel* m_labelRoomList;
    QListWidget *m_listRoom;
    QLabel* m_imageSelectedRoom;
    QLabel* m_labelPlayers;
    QListWidget* m_listPlayers;
    QPushButton* m_buttonAskPlayers;
    QPushButton* m_buttonStartGame;
    QPushButton* m_quitButton;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    StartGameUI* m_startGameUI;

    void fillMurderList();
    void fillWeaponList();
    void fillRoomList();
    QString getFilePath(const QString& p_itemText);
    QImage getImage(const QString& p_itemText);
};
