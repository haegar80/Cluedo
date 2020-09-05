#pragma once

#include <QtWidgets/QMainWindow>

class QWidget;
class QPushButton;
class QLabel;
class QString;
class QStatusBar;
class QMenuBar;

/// author: Copyright by Marcel Fuchs
class WaitRemotePlayerUI : public QMainWindow
{
    Q_OBJECT

public:
    WaitRemotePlayerUI(int p_numberOfExpectedRemoteUsers);
    virtual ~WaitRemotePlayerUI() = default;

    void setupUi();
    void retranslateUi();

    signals:
    void game_allRemoteUsersAvailable();
    void game_remoteUserNotAvailable();

    public slots:
    void game_newRemoteUserConnected();
    void buttonCancel_clicked();

private:
    int m_numberOfExpectedRemoteUsers{ 0 };

    QWidget* m_centralwidget;
    QLabel* m_labelWaitRemotePlayer;
    QPushButton* m_buttonCancel;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;
};
