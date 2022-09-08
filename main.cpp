#include "ventana.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ventana w;
    w.show();

    return a.exec();
}
