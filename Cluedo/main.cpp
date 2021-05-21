#include "UI/CluedoUI.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication a(argc, argv);
    CluedoUI mainWindow;
    mainWindow.show();

    return a.exec();
}