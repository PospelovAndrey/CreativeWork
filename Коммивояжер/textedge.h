#ifndef TEXTEDGE_H
#define TEXTEDGE_H

#include <QDialog>

namespace Ui {
class TextEdge;
}

class TextEdge : public QDialog
{
    Q_OBJECT

public:
    explicit TextEdge(QWidget *parent = nullptr);
    ~TextEdge();
private slots:
    void on_Ok_clicked();

private:
    Ui::TextEdge *ui;
};

#endif // TEXTEDGE_H
