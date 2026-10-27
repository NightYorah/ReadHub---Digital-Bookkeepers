#include "uploadwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UploadWindow w;
    w.show();
    return QApplication::exec();
}
