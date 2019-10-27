#include "StartGameUI.h"
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QImageReader>
#include <memory>

StartGameUI::StartGameUI()
{
    setupUi();
}

void StartGameUI::setupUi()
{
    if (this->objectName().isEmpty())
    {
        this->setObjectName(QString::fromUtf8("MainWindow"));
    }
    this->resize(570, 211);
    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_lineEditUserName = new QLineEdit(m_centralwidget);
    m_lineEditUserName->setObjectName(QString::fromUtf8("lineEditUserName"));
    m_lineEditUserName->setGeometry(QRect(130, 40, 131, 20));
    m_labelUserName = new QLabel(m_centralwidget);
    m_labelUserName->setObjectName(QString::fromUtf8("labelUserName"));
    m_labelUserName->setGeometry(QRect(50, 40, 81, 16));
    m_labelNumberOfComputerUsers = new QLabel(m_centralwidget);
    m_labelNumberOfComputerUsers->setObjectName(QString::fromUtf8("labelNumberOfComputerUsers"));
    m_labelNumberOfComputerUsers->setGeometry(QRect(300, 40, 121, 16));
    m_comboBoxNumberOfComputerUsers = new QComboBox(m_centralwidget);
    m_comboBoxNumberOfComputerUsers->setObjectName(QString::fromUtf8("comboBoxNumberOfComputerUsers"));
    m_comboBoxNumberOfComputerUsers->setGeometry(QRect(440, 40, 69, 22));
    m_buttonStartGame = new QPushButton(m_centralwidget);
    m_buttonStartGame->setObjectName(QString::fromUtf8("buttonStartGame"));
    m_buttonStartGame->setGeometry(QRect(50, 120, 75, 23));
    this->setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QString::fromUtf8("menubar"));
    m_menubar->setGeometry(QRect(0, 0, 570, 21));
    this->setMenuBar(m_menubar);
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(m_statusbar);

    retranslateUi();

    QObject::connect(m_buttonStartGame, SIGNAL(pressed()), this, SLOT(buttonStartGame_clicked()));

    m_comboBoxNumberOfComputerUsers->insertItem(0, "Kein");
    m_comboBoxNumberOfComputerUsers->insertItem(1, "1");
    m_comboBoxNumberOfComputerUsers->insertItem(2, "2");
    m_comboBoxNumberOfComputerUsers->insertItem(3, "3");
}

void StartGameUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
    m_labelUserName->setText(QApplication::translate("MainWindow", "Benutzername", 0));
    m_labelNumberOfComputerUsers->setText(QApplication::translate("MainWindow", "Anzahl Computergegner"));
    m_buttonStartGame->setText(QApplication::translate("MainWindow", "Start Game", 0));
}

void StartGameUI::buttonStartGame_clicked()
{

}