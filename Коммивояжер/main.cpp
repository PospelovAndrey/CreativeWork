#include "mainwindow.h"
#include "vertex.h"
#include "edge.h"
#include <QApplication>
QVector <Vertex> arr_vertex;
QVector <Edge> arr_edge;
QVector <QVector<int>> arr_lens;
QString edge_text;
int x_2;
int y_2;
int num_2;
int len=0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/1.ico"));
    w.setWindowTitle("Graph");
    w.show();
    return a.exec();
}
