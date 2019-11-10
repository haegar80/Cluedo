#pragma once

#include <QtWidgets/QMainWindow>

class CluedoObject;
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
    AskPlayerUI(const QPixmap* p_selectedMurder, const QPixmap* p_selectedWeapon, const QPixmap* p_selectedRoom);
    virtual ~AskPlayerUI() = default;

    void setupUi();
    void retranslateUi();
    void updateShownCluedoObject();

    signals:
    void askPlayerWindow_closed();

protected:
    void closeEvent(QCloseEvent* event) override;
private:
    QWidget* m_centralwidget;
    QLabel* m_labelSelectedMurder;
    QLabel* m_labelSelectedWeapon;
    QLabel* m_labelSelectedRoom;
    QLabel* m_imageSelectedMurder;
    QLabel* m_imageSelectedWeapon;
    QLabel* m_imageSelectedRoom;
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
    
    const QPixmap* m_selectedMurder;
    const QPixmap* m_selectedWeapon;
    const QPixmap* m_selectedRoom;

    void hideLabels();
    void updatePlayerLabelWithShownObject(PlayerSet* p_playerSet, CluedoObject* p_shownCluedoObject);
    void updatePlayerNoObjectLabels(PlayerSet* p_playerSet);
};