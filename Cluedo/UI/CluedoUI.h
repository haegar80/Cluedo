#pragma once

#include <QtWidgets/QMainWindow>
#include <memory>

class PlayerSet;
class StartGameUI;
class SelectObjectsUI;

class QWidget;
class QPushButton;
class QListWidget;
class QLabel;
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

    void updatePlayers();

    public slots:
    void askPlayers_clicked();
    void buttonStartGame_clicked();
    void game_started();
    void askPlayer_finished();

private:
    QWidget* m_centralwidget;
    QWidget* m_selectionObjectWidget;
    QLabel* m_labelCluedoObjects;
    QLabel* m_labelCluedoObject1;
    QLabel* m_labelCluedoObject2;
    QLabel* m_labelCluedoObject3;
    QLabel* m_labelCluedoObject4;
    QLabel* m_labelCluedoObject5;
    QLabel* m_labelCluedoObject6;
    QLabel* m_imageCluedoObject1;
    QLabel* m_imageCluedoObject2;
    QLabel* m_imageCluedoObject3;
    QLabel* m_imageCluedoObject4;
    QLabel* m_imageCluedoObject5;
    QLabel* m_imageCluedoObject6;
    QLabel* m_labelCurrentPlayer;
    QListWidget* m_listPlayers;
    QPushButton* m_buttonAskPlayers;
    QPushButton* m_buttonStartGame;
    QPushButton* m_quitButton;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    std::shared_ptr<PlayerSet> m_myPlayerSet;

    StartGameUI* m_startGameUI;
    SelectObjectsUI* m_selectObjectsUI;

    int m_currentPlayerIndex{ 0 };

    void nextPlayerReady();

    void hideNotUsedCluedoObjects();
    void fillCluedoObjects();
    QString getFilePath(const QString& p_itemText);
    QImage getImage(const QString& p_itemText);
};
