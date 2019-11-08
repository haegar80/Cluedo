#pragma once

#include <QtWidgets/QMainWindow>

class AskPlayerUI;

class QWidget;
class QPushButton;
class QListWidget;
class QLabel;
class QMenuBar;
class QStatusBar;
class QString;
class QImage;

/// author: Copyright by Marcel Fuchs
class SelectObjectsUI : public QMainWindow
{
    Q_OBJECT

public:
    SelectObjectsUI();
    virtual ~SelectObjectsUI() = default;

    void setupUi();
    void retranslateUi();

    public slots:
    void selectedMurder();
    void selectedWeapon();
    void selectedRoom();
    void buttonOk_clicked();
    void askPlayerWindow_closed();

private:
    QWidget* m_centralwidget;
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
    QPushButton* m_buttonOk;
    QPushButton* m_buttonAbort;
    QPushButton* m_quitButton;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    AskPlayerUI* m_askPlayerUI;

    bool m_selectedMurder{ false };
    bool m_selectedWeapon{ false };
    bool m_selectedRoom{ false };

    void fillMurderList();
    void fillWeaponList();
    void fillRoomList();
    QString getFilePath(const QString& p_itemText);
    QImage getImage(const QString& p_itemText);
};