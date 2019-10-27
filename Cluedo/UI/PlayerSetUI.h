#pragma once

#include <QtWidgets/QMainWindow>

class QWidget;
class QPushButton;
class QLabel;
class QStatusBar;
class QMenuBar;

/// author: Copyright by Marcel Fuchs
class PlayerSetUI : public QMainWindow
{
    Q_OBJECT

public:
    PlayerSetUI();
    virtual ~PlayerSetUI() = default;

    void setupUi();
    void retranslateUi();

    public slots:


private:
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
};
