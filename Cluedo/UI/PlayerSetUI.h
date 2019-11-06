#pragma once

#include <QtWidgets/QMainWindow>
#include <memory>

class PlayerSet;

class QWidget;
class QPushButton;
class QLabel;
class QStatusBar;
class QMenuBar;
class QString;
class QImage;

/// author: Copyright by Marcel Fuchs
class PlayerSetUI : public QMainWindow
{
    Q_OBJECT

public:
    PlayerSetUI(std::shared_ptr<PlayerSet> p_playerSet);
    virtual ~PlayerSetUI() = default;

    void setupUi();
    void retranslateUi();

    public slots:


private:
    std::shared_ptr<PlayerSet> m_playerSet;

    QWidget* m_centralwidget;
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
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;

    void hideNotUsedCluedoObjects();
    void fillCluedoObjects();
    QString getFilePath(const QString& p_itemText);
    QImage getImage(const QString& p_itemText);
};
