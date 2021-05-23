
#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

class myOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    myOpenGLWidget( QWidget *parent);
public slots:
    void redraw();
protected:
    void draw_vertex(int x, int y, QString text,QPainter *painter);
    void draw_edge(int x1, int y1, int x2, int y2,QPainter *painter,QString text);
    void draw(QPainter *painter, QPaintEvent *event);
    void paintEvent(QPaintEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent*event)override;
    void mouseReleaseEvent(QMouseEvent*event)override;
    void mouseMoveEvent(QMouseEvent*event)override;
};

#endif // MYOPENGLWIDGET_H
