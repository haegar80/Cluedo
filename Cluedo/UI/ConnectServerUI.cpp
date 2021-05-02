#include "ConnectServerUI.h"
#include "../GameManager/GameController.h"
#include "../Message/MessageIds.h"
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <sstream>

ConnectServerUI::ConnectServerUI()
{
    setupUi();
}

void ConnectServerUI::setupUi()
{
    if (this->objectName().isEmpty())
    {
        this->setObjectName(QString::fromUtf8("MainWindow"));
    }
    this->resize(333, 194);
    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_labelIPAddressServer = new QLabel(m_centralwidget);
    m_labelIPAddressServer->setObjectName(QString::fromUtf8("labelIPAddressServer"));
    m_labelIPAddressServer->setGeometry(QRect(30, 20, 101, 16));
    m_lineEditIPAddressServer = new QLineEdit(m_centralwidget);
    m_lineEditIPAddressServer->setObjectName(QString::fromUtf8("lineEditIPAddressServer"));
    m_lineEditIPAddressServer->setGeometry(QRect(130, 20, 111, 20));
    m_labelPlayerName = new QLabel(m_centralwidget);
    m_labelPlayerName->setObjectName(QStringLiteral("labelPlayerName"));
    m_labelPlayerName->setGeometry(QRect(30, 60, 81, 16));
    m_lineEditPlayerName = new QLineEdit(m_centralwidget);
    m_lineEditPlayerName->setObjectName(QStringLiteral("lineEditPlayerName"));
    m_lineEditPlayerName->setGeometry(QRect(130, 60, 111, 20));
    m_buttonOk = new QPushButton(m_centralwidget);
    m_buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
    m_buttonOk->setGeometry(QRect(30, 110, 75, 21));
    m_buttonCancel = new QPushButton(m_centralwidget);
    m_buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
    m_buttonCancel->setGeometry(QRect(160, 110, 81, 21));
    this->setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QString::fromUtf8("menubar"));
    m_menubar->setGeometry(QRect(0, 0, 570, 21));
    this->setMenuBar(m_menubar);
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(m_statusbar);

    retranslateUi();

    QObject::connect(m_buttonOk, SIGNAL(pressed()), this, SLOT(buttonOk_clicked()));
    QObject::connect(m_buttonCancel, SIGNAL(pressed()), this, SLOT(buttonCancel_clicked()));
}

void ConnectServerUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("MainWindow", "WaitRemotePlayer", 0));
    m_labelIPAddressServer->setText(QApplication::translate("MainWindow", "IP Addresse Server", 0));
    m_labelPlayerName->setText(QApplication::translate("MainWindow", "Benutzername", 0));
    m_buttonOk->setText(QApplication::translate("MainWindow", "Ok", 0));
    m_buttonCancel->setText(QApplication::translate("MainWindow", "Abbrechen", 0));
}

void ConnectServerUI::buttonOk_clicked()
{
    connectToServer();
}

void ConnectServerUI::buttonCancel_clicked()
{
    this->close();
}

void ConnectServerUI::connectToServer() {
#if WIN32
    if (m_tcpWinSocketClient) {
        bool initSuccessful = m_tcpWinSocketClient->init(m_lineEditIPAddressServer->text().toStdString());
        if (initSuccessful) {
            bool connectSuccessful = m_tcpWinSocketClient->connectToServer();
            if (connectSuccessful) {
                GameController& gameController = GameController::getInstance();
                Player* player = gameController.createNewPlayer(m_lineEditPlayerName->text().toStdString(), Player::PlayerType_SelfClient);

                std::stringstream ss;
                constexpr int DummyIndexNumber = 0;
                ss << MessageIds::PlayersList << ":";
                ss << DummyIndexNumber;
                ss << player->getName() << ";";
                m_tcpWinSocketClient->sendData(ss.str());

                emit game_started_client();
            }
            else {
                // todo send signal
            }
            this->close();
        }
    }
#endif
}