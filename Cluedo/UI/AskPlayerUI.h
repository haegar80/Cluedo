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
class AskPlayerUI : public QMainWindow
{
    Q_OBJECT

public:
    AskPlayerUI(bool p_showShowedObject, const QString& p_askedPlayer, const QString& p_selectedMurderString, const QString& p_selectedWeaponString, const QString& p_selectedRoomString);
    AskPlayerUI(bool p_showShowedObject, const QString& p_askedPlayer, int p_selectedMurderNumber, int p_selectedWeaponNumber, int p_selectedRoomNumber);
    virtual ~AskPlayerUI() = default;

    void setupUi();
    void retranslateUi();
    void updateShownCluedoObject(Player* p_player);

    signals:
    void askPlayerWindow_closed();
    void askPlayerFromOtherPlayerWindow_closed();

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
    QLabel* m_labelPlayer;
    QLabel* m_labelPlayerName;
    QLabel* m_labelPlayerNoObjects;
    QLabel* m_labelPlayerNameNoObjects1;
    QLabel* m_labelPlayerNameNoObjects2;
    QLabel* m_labelPlayerNameNoObjects3;
    QLabel* m_labelPlayerNameNoObjects4;
    QLabel* m_labelPlayerNameNoObjects5;
    QLabel* m_labelPlayerNameNoObjects6;
    QLabel* m_labelShowedObject;
    QLabel* m_imageShowedObject;
    QPushButton* m_buttonOk;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;
    
    bool m_showShowedObject{ false };
    const QString m_askedPlayer{ "" };
    QPixmap m_selectedMurder;
    QPixmap m_selectedWeapon;
    QPixmap m_selectedRoom;
    QString m_selectedMurderString;
    QString m_selectedWeaponString;
    QString m_selectedRoomString;

    void createImages();
    void checkAndupdateImageWithShownObject(Player* p_player, CluedoObject* p_shownCluedoObject);
    void updateImageWithShownObject(CluedoObject* p_shownCluedoObject);
    void hideLabels();
    void updatePlayerLabelWithShownObject(PlayerSet* p_playerSet, CluedoObject* p_shownCluedoObject);
    void updatePlayerNoObjectLabels(PlayerSet* p_playerSet);
};