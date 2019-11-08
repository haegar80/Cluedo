#pragma once

#include <QtWidgets/QMainWindow>

class PlayerSetUI;
class QWidget;
class QPushButton;
class QLineEdit;
class QLabel;
class QString;
class QStatusBar;
class QComboBox;
class QMenuBar;

/// author: Copyright by Marcel Fuchs
class StartGameUI : public QMainWindow
{
    Q_OBJECT

public:
    StartGameUI();
    virtual ~StartGameUI() = default;

    void setupUi();
    void retranslateUi();

    signals:
    void game_started();

    public slots:
    void buttonStartGame_clicked();

private:
    PlayerSetUI * m_playerSetUI;

    QWidget* m_centralwidget;
    QLineEdit* m_lineEditPlayerName;
    QLabel* m_labelPlayerName;
    QLabel* m_labelNumberOfComputerPlayers;
    QComboBox* m_comboBoxNumberOfComputerPlayers;
    QPushButton* m_buttonStartGame;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    void gameStarted();
};
