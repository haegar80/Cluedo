#pragma once

#include <QtWidgets/QMainWindow>

class QCloseEvent;
class QWidget;
class QLabel;
class QCheckBox;
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
    QLabel* m_labelPlayer1;
    QLabel* m_labelPlayer2;
    QLabel* m_labelPlayer3;
    QCheckBox* m_checkBoxPlayer1;
    QCheckBox* m_checkBoxPlayer2;
    QCheckBox* m_checkBoxPlayer3;
    QLabel* m_labelShowedObject;
    QLabel* m_imageShowedObject;
    QPushButton* m_buttonOk;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;
    
    const QPixmap* m_selectedMurder;
    const QPixmap* m_selectedWeapon;
    const QPixmap* m_selectedRoom;
};