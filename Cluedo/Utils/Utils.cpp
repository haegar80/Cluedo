#include "Utils.h"
#include <QtCore/QDir>
#include <QImageReader>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

namespace Utils
{
    int generateRandomNumber(int p_minNumber, int p_maxNumber)
    {
        /* generate random number between 1 and 10: */
        int randomNumber = 0;
        if (p_maxNumber > 0)
        {
            randomNumber = rand() % p_maxNumber + p_minNumber;
        }

        return randomNumber;
    }

    QString getFilePath(const QString& p_itemText)
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

    QImage getImage(const QString& p_itemText)
    {
        QImageReader imageReader(getFilePath(p_itemText));
        imageReader.setAutoTransform(true);
        QImage image = imageReader.read();

        return image;
    }
}