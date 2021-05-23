#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/1.ico"));
    w.setWindowTitle("TimeCalculator");
    w.show();
    return a.exec();
}
