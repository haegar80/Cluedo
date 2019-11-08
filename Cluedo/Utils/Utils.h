#pragma once

class QString;
class QImage;

namespace Utils
{
    int generateRandomNumber(int p_minNumber, int p_maxNumber);

    QString getFilePath(const QString& p_itemText);
    QImage getImage(const QString& p_itemText);
};

