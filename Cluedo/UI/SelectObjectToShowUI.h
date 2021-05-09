#pragma once

#include <QtWidgets/QMainWindow>

class CluedoObject;
class Player;
class PlayerSet;

class QCloseEvent;
class QWidget;
class QLabel;
class QPushButton;
class QMenuBar;
class QStatusBar;
class QString;
class QPixmap;

/// author: Copyright by Marcel Fuchs
class SelectObjectToShowUI : public QMainWindow
{
    Q_OBJECT

public:
    SelectObjectToShowUI(const QString& p_askedPlayer, const QString& p_selectedMurder, const QString& p_selectedWeapon, const QString& p_selectedRoom);
    virtual ~SelectObjectToShowUI() = default;

    void setupUi();
    void retranslateUi();

    bool getShowMurder() {
        return m_showMurder;
    }

    bool getShowWeapon() {
        return m_showWeapon;
    }

    bool getShowRoom() {
        return m_showRoom;
    }

    public slots:
    void buttonShowMurder_clicked();
    void buttonShowWeapon_clicked();
    void buttonShowRoom_clicked();
    void buttonOk_clicked();

private:
    QWidget* m_centralwidget;
    QLabel* m_labelAsk;
    QLabel* m_labelAskedPerson;
    QLabel* m_labelSelectedMurder;
    QLabel* m_labelSelectedWeapon;
    QLabel* m_labelSelectedRoom;
    QLabel* m_imageSelectedMurder;
    QLabel* m_imageSelectedWeapon;
    QLabel* m_imageSelectedRoom;
    QLabel* m_labelAvailableObjects;
    QLabel* m_labelAvailableMurder;
    QLabel* m_labelAvailableWeapon;
    QLabel* m_labelAvailableRoom;
    QLabel* m_imageAvailableMurder;
    QLabel* m_imageAvailableWeapon;
    QLabel* m_imageAvailableRoom;
    QPushButton* m_buttonShowMurder;
    QPushButton* m_buttonShowWeapon;
    QPushButton* m_buttonShowRoom;
    QPushButton* m_buttonOk;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;
    
    const QString m_askedPlayer{ "" };
    const QString m_selectedMurder;
    const QString m_selectedWeapon;
    const QString m_selectedRoom;

    bool m_showMurder{ false };
    bool m_showWeapon{ false };
    bool m_showRoom{ false };

    void initObjectsToShow();
};