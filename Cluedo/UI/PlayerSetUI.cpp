#include "PlayerSetUI.h"
#include "../Model/PlayerSet.h"
#include "../GameManager/GameController.h"
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QImageReader>

PlayerSetUI::PlayerSetUI(PlayerSet* p_playerSet) : m_playerSet(p_playerSet)
{
    setupUi();
}

void PlayerSetUI::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("MainWindow"));
    this->resize(946, 600);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    m_labelCluedoObjects = new QLabel(m_centralwidget);
    m_labelCluedoObjects->setObjectName(QString::fromUtf8("labelCluedoObjects"));
    m_labelCluedoObjects->setGeometry(QRect(40, 20, 141, 16));

    m_labelCluedoObject1 = new QLabel(m_centralwidget);
    m_labelCluedoObject1->setObjectName(QString::fromUtf8("labelCluedoObject1"));
    m_labelCluedoObject1->setGeometry(QRect(40, 50, 111, 13));
    m_labelCluedoObject2 = new QLabel(m_centralwidget);
    m_labelCluedoObject2->setObjectName(QString::fromUtf8("labelCluedoObject2"));
    m_labelCluedoObject2->setGeometry(QRect(180, 50, 111, 13));
    m_labelCluedoObject3 = new QLabel(m_centralwidget);
    m_labelCluedoObject3->setObjectName(QString::fromUtf8("labelCluedoObject3"));
    m_labelCluedoObject3->setGeometry(QRect(320, 50, 111, 13));
    m_labelCluedoObject4 = new QLabel(m_centralwidget);
    m_labelCluedoObject4->setObjectName(QString::fromUtf8("labelCluedoObject4"));
    m_labelCluedoObject4->setGeometry(QRect(460, 50, 111, 13));
    m_labelCluedoObject5 = new QLabel(m_centralwidget);
    m_labelCluedoObject5->setObjectName(QString::fromUtf8("labelCluedoObject5"));
    m_labelCluedoObject5->setGeometry(QRect(600, 50, 111, 13));
    m_labelCluedoObject6 = new QLabel(m_centralwidget);
    m_labelCluedoObject6->setObjectName(QString::fromUtf8("labelCluedoObject6"));
    m_labelCluedoObject6->setGeometry(QRect(740, 50, 111, 13));

    m_imageCluedoObject1 = new QLabel(m_centralwidget);
    m_imageCluedoObject1->setObjectName(QString::fromUtf8("imageCluedoObject1"));
    m_imageCluedoObject1->setGeometry(QRect(40, 80, 120, 160));
    m_imageCluedoObject1->setFrameShape(QFrame::Box);
    m_imageCluedoObject1->setScaledContents(true);
    m_imageCluedoObject2 = new QLabel(m_centralwidget);
    m_imageCluedoObject2->setObjectName(QString::fromUtf8("imageCluedoObject2"));
    m_imageCluedoObject2->setGeometry(QRect(180, 80, 120, 160));
    m_imageCluedoObject2->setFrameShape(QFrame::Box);
    m_imageCluedoObject2->setScaledContents(true);
    m_imageCluedoObject3 = new QLabel(m_centralwidget);
    m_imageCluedoObject3->setObjectName(QString::fromUtf8("imageCluedoObject3"));
    m_imageCluedoObject3->setGeometry(QRect(320, 80, 120, 160));
    m_imageCluedoObject3->setFrameShape(QFrame::Box);
    m_imageCluedoObject3->setScaledContents(true);
    m_imageCluedoObject4 = new QLabel(m_centralwidget);
    m_imageCluedoObject4->setObjectName(QString::fromUtf8("imageCluedoObject4"));
    m_imageCluedoObject4->setGeometry(QRect(460, 80, 120, 160));
    m_imageCluedoObject4->setFrameShape(QFrame::Box);
    m_imageCluedoObject4->setScaledContents(true);
    m_imageCluedoObject5 = new QLabel(m_centralwidget);
    m_imageCluedoObject5->setObjectName(QString::fromUtf8("imageCluedoObject5"));
    m_imageCluedoObject5->setGeometry(QRect(600, 80, 120, 160));
    m_imageCluedoObject5->setFrameShape(QFrame::Box);
    m_imageCluedoObject5->setScaledContents(true);
    m_imageCluedoObject6 = new QLabel(m_centralwidget);
    m_imageCluedoObject6->setObjectName(QString::fromUtf8("imageCluedoObject6"));
    m_imageCluedoObject6->setGeometry(QRect(740, 80, 120, 160));
    m_imageCluedoObject6->setFrameShape(QFrame::Box);
    m_imageCluedoObject6->setScaledContents(true);

    this->setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QString::fromUtf8("menubar"));
    m_menubar->setGeometry(QRect(0, 0, 946, 21));
    this->setMenuBar(m_menubar);
    m_statusbar = new QStatusBar(this);
    m_statusbar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(m_statusbar);

    retranslateUi();

    GameController::getInstance().selectAndDistributeCluedoObjects();
    hideNotUsedCluedoObjects();
    fillCluedoObjects();

    GameController::getInstance().startGameRounds();
}

void PlayerSetUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("PlayerSet", "PlayerSet", 0));
    m_labelCluedoObjects->setText(QApplication::translate("PlayerSet", "Deine T\303\244ter/Waffen/R\303\244ume", 0));
    m_labelCluedoObject1->setText(QString());
    m_labelCluedoObject2->setText(QString());
    m_labelCluedoObject3->setText(QString());
    m_labelCluedoObject4->setText(QString());
    m_labelCluedoObject5->setText(QString());
    m_labelCluedoObject6->setText(QString());
    m_imageCluedoObject1->setText(QString());
    m_imageCluedoObject2->setText(QString());
    m_imageCluedoObject3->setText(QString());
    m_imageCluedoObject4->setText(QString());
    m_imageCluedoObject5->setText(QString());
    m_imageCluedoObject6->setText(QString());
}

void PlayerSetUI::hideNotUsedCluedoObjects()
{
    int numberOfCluedoObjects = m_playerSet->getNumberOfCluedoObjects();

    switch (numberOfCluedoObjects)
    {
    case 0:
        m_labelCluedoObject1->hide();
        m_imageCluedoObject1->hide();
    case 1:
        m_labelCluedoObject2->hide();
        m_imageCluedoObject2->hide();
    case 2:
        m_labelCluedoObject3->hide();
        m_imageCluedoObject3->hide();
    case 3:
        m_labelCluedoObject4->hide();
        m_imageCluedoObject4->hide();
    case 4:
        m_labelCluedoObject5->hide();
        m_imageCluedoObject5->hide();
    case 5:
        m_labelCluedoObject6->hide();
        m_imageCluedoObject6->hide();
        break;
    default:
        break;
    }
}

void PlayerSetUI::fillCluedoObjects()
{
    if (nullptr != m_playerSet)
    {
        std::vector<CluedoObject*>& cluedoObjects = m_playerSet->getCluedoObjects();
        int index = 1;
        for (CluedoObject* cluedoObject : cluedoObjects)
        {
            QString name = QString::fromStdString(cluedoObject->getName());
            if (1 == index)
            {
                m_labelCluedoObject1->setText(name);
                QImage image = getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject1->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (2 == index)
            {
                m_labelCluedoObject2->setText(name);
                QImage image = getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject2->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (3 == index)
            {
                m_labelCluedoObject3->setText(name);
                QImage image = getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject3->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (4 == index)
            {
                m_labelCluedoObject4->setText(name);
                QImage image = getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject4->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (5 == index)
            {
                m_labelCluedoObject5->setText(name);
                QImage image = getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject5->setPixmap(QPixmap::fromImage(image));
                }
            }
            else if (6 == index)
            {
                m_labelCluedoObject6->setText(name);
                QImage image = getImage(name);
                if (!image.isNull())
                {
                    m_imageCluedoObject6->setPixmap(QPixmap::fromImage(image));
                }
            }
            index++;
        }
    }
}

QString PlayerSetUI::getFilePath(const QString& p_itemText)
{
    QString path = p_itemText;
    QString extension(".jpg");
    path += extension;

    QDir dirPath(QString("Pics"));
    if (dirPath.exists())
    {
        QFileInfo file(dirPath, path);
        path = file.absoluteFilePath();
    }

    return path;
}

QImage PlayerSetUI::getImage(const QString& p_itemText)
{
    QImageReader imageReader(getFilePath(p_itemText));
    imageReader.setAutoTransform(true);
    QImage image = imageReader.read();

    return image;
}