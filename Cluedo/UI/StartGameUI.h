#pragma once

#include <QtWidgets/QMainWindow>

class QWidget;
class QPushButton;
class QLineEdit;
class QPushButton;
class QLabel;
class QString;
class QImage;
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

    public slots:
    void buttonStartGame_clicked();

private:
    QWidget* m_centralwidget;
    QLineEdit* m_lineEditUserName;
    QLabel* m_labelUserName;
    QLabel* m_labelNumberOfComputerUsers;
    QComboBox* m_comboBoxNumberOfComputerUsers;
    QPushButton* m_buttonStartGame;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;
};
