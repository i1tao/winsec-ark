#include "WinsecArkGuiQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WinsecArkGuiQt w;
    w.show();
    return a.exec();
}
