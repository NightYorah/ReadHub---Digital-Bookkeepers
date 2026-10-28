#include "mainwindow.h"
#include "loginwindow.h"
#include "uploadwindow.h"
#include "readwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    return QApplication::exec();
}
