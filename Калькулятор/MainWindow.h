#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void input();
    void HMS();
    void operations();
    void on_pushButton_eq_clicked();
    void output(int);
    void on_pushButton_conv_clicked();
    void on_pushButton_AC_clicked();
    void on_pushButton_CE_clicked();
};
#endif // MAINWINDOW_H
