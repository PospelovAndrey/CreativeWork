#include "myOpenGLWidget.h"
#include "textedge.h"
#include "vertex.h"
#include "edge.h"
#include <QBrush>
#include <QFont>
#include <QPushButton>
double pi=3.1415;
double angle=pi/10;
int HeadEdge=15;
bool fl=false;
QFont glFont;
myOpenGLWidget::myOpenGLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
}
void myOpenGLWidget::draw_vertex(int x, int y, QString text,QPainter *painter)
{
    int c1=x-20;
    int c2=y-15;
    int c3=40;
    int c4=30;
    painter->drawEllipse(QRectF(x-35,y-35,70,70));
    painter->drawText(QRect(c1,c2,c3,c4),Qt::AlignCenter,text);
}
void myOpenGLWidget::draw_edge(int x1, int y1, int x2, int y2,QPainter *painter,QString text)
{
    double l=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
        int xl1=(x2-x1)/l*37+x1;
        int yl1=(y2-y1)/l*37+y1;
        int xl2=x2-(x2-x1)/l*35;
        int yl2=y2-(y2-y1)/l*35;
        int c1=(xl2+xl1)/2-30;
        int c2=(yl2+yl1)/2-30;
        int c3=40;
        int c4=30;
        painter->drawLine(xl1,yl1,xl2,yl2);
            double b;
            if      (x2==xl2 && yl2<y2) b=pi*3/2;
            else if (y2==yl2 && xl2<x2) b=pi;
            else if (x2==xl2 && yl2>y2) b=pi/2;
            else if (y2==yl2 && xl2>x2) b=0;
            else if (xl2>x2 && yl2<y2)  b=2*pi+atan(1.0*(y2-yl2)/(x2-xl2));
            else if (xl2<x2 && yl2<y2)  b=atan(1.0*(y2-yl2)/(x2-xl2))+pi;
            else if (xl2<x2 && yl2>y2)  b=atan(1.0*(y2-yl2)/(x2-xl2))+pi;
            else if (xl2>x2 && yl2>y2)  b=atan(1.0*(y2-yl2)/(x2-xl2));
            int xs1=cos(b+angle)*HeadEdge+xl2;
            int ys1=sin(b+angle)*HeadEdge+yl2;
            int xs2=cos(b-angle)*HeadEdge+xl2;
            int ys2=sin(b-angle)*HeadEdge+yl2;
            painter->drawLine(xl2,yl2,xs1,ys1);
            painter->drawLine(xl2,yl2,xs2,ys2);
    painter->drawText(QRect(c1,c2,c3,c4),Qt::AlignCenter,text);
}
void myOpenGLWidget::draw(QPainter *painter, QPaintEvent *event)
{
    painter->fillRect(event->rect(),QBrush(QColor(225, 225, 225)));
    painter->setBrush(QBrush(QColor(255, 255, 255)));
    painter->setPen(QPen(QColor(0,0,0)));
    glFont.setPixelSize(25);
    painter->setFont(glFont);
    extern QVector<Vertex> arr_vertex;
    extern QVector<Edge> arr_edge;
    for (int i=0;i<arr_vertex.size();i++)
    {
        draw_vertex(arr_vertex[i].x,
                 arr_vertex[i].y,
                 QString::number(i+1),
                 painter);
    }
    for (int i=0;i<arr_edge.size();i++)
    {
        draw_edge(arr_edge[i].x1,
                  arr_edge[i].y1,
                  arr_edge[i].x2,
                  arr_edge[i].y2,
                  painter,
                  QString::number(arr_edge[i].length));
    }
}
void myOpenGLWidget::redraw()
{
    this->update();
}
void myOpenGLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    draw(&painter,event);
    painter.end();
}
void myOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    extern QVector<Vertex> arr_vertex;
    extern QVector<Edge> arr_edge;
    extern QVector <QVector<int>> arr_lens;
    extern int len;
    extern int x_2;
    extern int y_2;
    extern int num_2;
    extern QString edge_text;
    int l=edge_text.toInt();
    if (event->button() == Qt::RightButton)
    {
        if (!fl)
            {
                for (int i=0;i<len;i++)
                {
                    int x1=event->x();
                    int y1=event->y();
                    int x2=arr_vertex[i].x;
                    int y2=arr_vertex[i].y;
                    if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1400)
                    {
                        x_2=x2;
                        y_2=y2;
                        num_2=i;
                        fl=true;
                        break;
                    }
                }
            }
            else if (fl)
            {
                for (int i=0;i<len;i++)
                {
                    int x1=event->x();
                    int y1=event->y();
                    int x2=arr_vertex[i].x;
                    int y2=arr_vertex[i].y;
                    if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1400)
                    {
                        TextEdge wind;
                        wind.setModal(true);
                        wind.exec();
                        l=edge_text.toInt();
                        Edge a(x_2,y_2,x2,y2,l);
                        arr_lens[num_2][i]=l;
                        arr_edge.push_back(a);
                    }
                    fl=false;
                }
            }
    }
    else if((event->button() == Qt::LeftButton))
    {
        for (int i=0;i<len;i++)
        {
            int x1=event->x();
            int y1=event->y();
            int x2=arr_vertex[i].x;
            int y2=arr_vertex[i].y;
            if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1400)
            {
                arr_vertex[i].flag=true;
                break;
            }
        }
    }
    update();
}
void myOpenGLWidget::mouseDoubleClickEvent(QMouseEvent *event){
    extern QVector<Vertex> arr_vertex;
    extern QVector<Edge> arr_edge;
    extern QVector <QVector<int>> arr_lens;
    extern int len;
    if((event->button() == Qt::LeftButton))
    {
        Vertex a(event->x(),event->y());
        arr_vertex.push_back(a);
        len++;
        QVector <int> row(len);
        row.fill(0);
        arr_lens.append(row);
        for (int i=0;i<len-1;i++) arr_lens[i].append(0);
    }
    else if(event->button() == Qt::RightButton)
    {
    for (int i=0;i<len;i++)
    {
        int x1=event->x();
        int y1=event->y();
        int x2=arr_vertex[i].x;
        int y2=arr_vertex[i].y;
        if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<1400)
        {
            QVector<Edge> arr_edge_new;
            for (int j=0;j<arr_edge.size();j++)
            {
                if (!(arr_edge[j].x1==arr_vertex[i].x && arr_edge[j].y1==arr_vertex[i].y)
                   && !(arr_edge[j].x2==arr_vertex[i].x && arr_edge[j].y2==arr_vertex[i].y))
                {
                    arr_edge_new.push_back(arr_edge[j]);
                }
            }
            arr_edge=arr_edge_new;
            arr_vertex.erase(arr_vertex.begin()+i);
            len--;
            for (int j=0;j<len;j++) arr_lens[j].erase(arr_lens[j].begin()+i);
            arr_lens.erase(arr_lens.begin()+i);
            fl=false;
            break;
        }
    }
    }
    update();

}
void myOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    extern QVector<Vertex> arr_vertex;
    extern int len;
    for (int i=0;i<len;i++) arr_vertex[i].flag=false;
    update();
}
void myOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    extern QVector<Vertex> arr_vertex;
    extern QVector<Edge> arr_edge;
    extern int len;
        for (int i=0;i<len;i++)
        {
            if (arr_vertex[i].flag)
            {
                for (int j=0;j<arr_edge.size();j++)
                {
                    if (arr_edge[j].x1==arr_vertex[i].x && arr_edge[j].y1==arr_vertex[i].y)
                    {
                        arr_edge[j].x1=event->x();
                        arr_edge[j].y1=event->y();
                    }
                    if (arr_edge[j].x2==arr_vertex[i].x && arr_edge[j].y2==arr_vertex[i].y)
                    {
                        arr_edge[j].x2=event->x();
                        arr_edge[j].y2=event->y();
                    }
                }
                arr_vertex[i].x=event->x();
                arr_vertex[i].y=event->y();
                break;
            }
        }
    update();
}









