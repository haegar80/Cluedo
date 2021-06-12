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
    SelectObjectToShowUI(const QString& p_askedPlayer, int p_murderNumber, int p_weaponNumber, int p_roomNumber);
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

    signals:
    void selectObjectToShowWindow_closed(bool p_objectCouldBeShown);

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    static constexpr int referenceWidth = 1920;
    static constexpr int referenceHeight = 1040;

    QWidget* m_centralwidget;
    QLabel* m_labelAsk;
    QLabel* m_labelAskedPerson;
    QLabel* m_labelSelectedMurder;
    QLabel* m_labelSelectedWeapon;
    QLabel* m_labelSelectedRoom;
    QLabel* m_imageSelectedMurder;
    QLabel* m_imageSelectedWeapon;
    QLabel* m_imageSelectedRoom;
    QLabel* m_labelSelectedMurderName;
    QLabel* m_labelSelectedWeaponName;
    QLabel* m_labelSelectedRoomName;
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
    QString m_selectedMurderString;
    QString m_selectedWeaponString;
    QString m_selectedRoomString;
    int m_selectedMurderNumber;
    int m_selectedWeaponNumber;
    int m_selectedRoomNumber;

    bool m_showMurder{ false };
    bool m_showWeapon{ false };
    bool m_showRoom{ false };

    void initObjectsToShow();
};