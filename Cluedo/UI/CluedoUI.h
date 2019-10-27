#pragma once

#include "../GameManager/CluedoObjectLoader.h"
#include <QtWidgets/QMainWindow>

class QWidget;
class QPushButton;
class QListWidget;
class QPushButton;
class QLabel;
class QScrollArea;
class QCheckBox;
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

    public slots:
    void selectedMurder();
    void selectedWeapon();
    void selectedRoom();

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
    QPushButton* m_quitButton;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    CluedoObjectLoader m_cluedoObjectLoader;

    void fillMurderList();
    void fillWeaponList();
    void fillRoomList();
    QString getFilePath(const QString& p_itemText);
    QImage getImage(const QString& p_itemText);
};
