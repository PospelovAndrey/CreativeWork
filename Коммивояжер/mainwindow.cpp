#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myOpenGLWidget.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("   2xЛКМ  -  добавление  ,  2xПКМ  -  удаление  ,  ПКМ  -  добавление стрелки  ,  '='  -  показать результат" );
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Equal)
    {
        extern QVector <QVector<int>> arr_lens;
        QVector <int> arr_res1;
        QVector <int> arr_res2;
        int len=arr_lens.size();
        int sum=0;
        int M=10000;
        bool flag=true;
        QVector <QVector<int>> data=arr_lens;
        for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (i==k || data[i][k]==0) data[i][k]=M;
        while (flag)
        {
            QVector <int> row(len);
            row.fill(M);
            QVector <int> column(len);
            column.fill(M);
            for (int i=0;i<len;i++) for (int k=0;k<len;k++) row[i]=qMin(row[i],data[i][k]);
            for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (row[i]!=M && data[i][k]!=M) data[i][k]-=row[i];
            for (int i=0;i<len;i++) for (int k=0;k<len;k++) column[k]=qMin(column[k],data[i][k]);
            for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (column[k]!=M && data[i][k]!=M) data[i][k]-=column[k];
            int max_mark_x;
            int max_mark_y;
            int max_mark=-1;
            for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (data[i][k]==0)
            {
                int min1=M;
                int min2=M;
                for (int j=0;j<len;j++) if (j!=k) min1=qMin(min1,data[i][j]);
                for (int j=0;j<len;j++) if (j!=i) min2=qMin(min2,data[j][k]);
                if (min1+min2>max_mark)
                {
                    max_mark=min1+min2;
                    max_mark_x=i;
                    max_mark_y=k;
                }
            }
            sum+=arr_lens[max_mark_x][max_mark_y];
            data[max_mark_y][max_mark_x]=M;
            for (int i=0;i<len;i++)
            {
                data[max_mark_x][i]=M;
                data[i][max_mark_y]=M;
            }
            arr_res1.push_back(max_mark_x);
            arr_res2.push_back(max_mark_y);
            flag=false;
            for (int i=0;i<len;i++) for (int k=0;k<len;k++) if (data[i][k]!=M) flag=true;
        }
        if (arr_res1[0]!=arr_res2[arr_res2.size()-1])
        {
            ui->statusbar->showMessage("Ошибка");
            return;
        }
        QString r="  Кратчайший путь: "+QString::number(arr_res1[0]+1)+"->"+QString::number(arr_res2[0]+1);
                    int x=arr_res2[0];
                    arr_res1.erase(arr_res1.begin());
                    arr_res2.erase(arr_res2.begin());
                    while (arr_res1.size()!=0)
                    {
                        for (int i=0;i<arr_res1.size();i++) if (arr_res1[i]==x)
                        {
                            r+=" -> "+QString::number(arr_res2[i]+1);
                            x=arr_res2[i];
                            arr_res1.erase(arr_res1.begin()+i);
                            arr_res2.erase(arr_res2.begin()+i);
                            break;
                        }
                    }
                    r[0]=' ';
                    r+="   Его длина: "+QString::number(sum);
                    ui->statusbar->showMessage(r);
}
}
