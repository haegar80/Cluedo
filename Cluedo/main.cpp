#include "UI/CluedoUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CluedoUI mainWindow;
    mainWindow.show();

    return a.exec();
}