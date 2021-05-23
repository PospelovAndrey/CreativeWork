#include "textedge.h"
#include "ui_textedge.h"

TextEdge::TextEdge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextEdge)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

TextEdge::~TextEdge()
{
    delete ui;
}
void TextEdge::on_Ok_clicked()
{
    extern QString edge_text;
    edge_text = ui->Val->text();
    this->close();
}


