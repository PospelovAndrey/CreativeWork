#include "MainWindow.h"
#include "ui_mainwindow.h"
double num_first;
double num_second;
QString new_label;
QString first_num_label;
QString OP_label;
bool flagH=false;
bool flagM=false;
bool flagS=false;
bool flagOP=false;
bool flagConv=false;
bool flagMin=false;
bool flagEq=false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(input()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(input()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(input()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(input()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(input()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(input()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(input()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(input()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(input()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(input()));
    connect(ui->pushButton_H,SIGNAL(clicked()),this,SLOT(HMS()));
    connect(ui->pushButton_M,SIGNAL(clicked()),this,SLOT(HMS()));
    connect(ui->pushButton_S,SIGNAL(clicked()),this,SLOT(HMS()));
    connect(ui->pushButton_int,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(operations()));
    ui->pushButton_H->setCheckable(true);
    ui->pushButton_M->setCheckable(true);
    ui->pushButton_S->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_int->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::input()
{
    if(!flagH || !flagM || !flagS)
    {
    double all_num;
    QPushButton *button = (QPushButton *)sender();
    all_num=(ui->label_down->text()+button->text()).toDouble();
    new_label=QString::number(all_num,'g',3);
    ui->label_down->setText(new_label);
    }
}
void MainWindow::HMS()
{
    if(!ui->label_down->text().contains("e"))
    {
    if(flagConv) on_pushButton_conv_clicked();
    else if(ui->label_down->text()!="0"&&ui->label_down->text()!="")
    {
    if(ui->pushButton_H->isChecked() && !flagH)
    {
      ui->label_up->setText(ui->label_up->text()+" "+new_label+"ч");
     ui->pushButton_H->setChecked(false);
     num_second+=(ui->label_down->text().toDouble())*3600;
     ui->label_down->setText("");
     flagH=true;
    }
    else if(ui->pushButton_M->isChecked() && !flagM)
    {
      ui->label_up->setText(ui->label_up->text()+" "+new_label+"м");
      ui->pushButton_M->setChecked(false);
      num_second+=(ui->label_down->text().toDouble())*60;
      ui->label_down->setText("");
      flagM=true;
    }
    else if(ui->pushButton_S->isChecked() && !flagS)
    {
      ui->label_up->setText(ui->label_up->text()+" "+new_label+"c");
      ui->pushButton_S->setChecked(false);
      num_second+=(ui->label_down->text().toDouble());
      ui->label_down->setText("");
      flagS=true;
    }
    }
    }
    else
    {
    ui->label_up->setText("Ошибка ввода");
    ui->label_down->setText("");
    }
}

void MainWindow::operations()
{
 if(flagH || flagM || flagS)
{
OP_label=ui->label_up->text();
QPushButton *button = (QPushButton *)sender();
if(ui->label_up->text().contains("="))
{
 ui->label_up->setText(ui->label_down->text());
 ui->label_down->setText("");
 flagEq=true;
}
if(((ui->label_up->text().contains("-")||ui->label_up->text().contains("Инт")||ui->label_up->text().contains("+")) && num_first!=0))
{
  flagOP=true;
  on_pushButton_eq_clicked();
  ui->label_up->setText(ui->label_up->text()+" "+button->text()+"");
  OP_label=ui->label_up->text();
  ui->label_down->setText("");
  num_second=0;
  flagOP=false;
  flagH=false;
  flagM=false;
  flagS=false;
}
else
   {
   ui->label_up->setText(ui->label_up->text()+" "+button->text()+"");
   OP_label=ui->label_up->text();
   flagH=false;
   flagM=false;
   flagS=false;
   if(!flagEq)
   {
   num_first=num_second;
   }
   num_second=0;   
}
}

first_num_label=ui->label_up->text();

}



void MainWindow::on_pushButton_eq_clicked()
{
    if(flagH || flagM || flagS)
    {
 int res;
 if(!(ui->label_up->text().contains("="))&& num_second!=0 && num_first!=0 )
    ui->label_up->setText(ui->label_up->text()+" = ");
 if(OP_label.contains("+"))
 {
     res=num_first+num_second;
     num_first=res;
     output(res);
 }
 else if(OP_label.contains("-"))
 {
     if(num_first>=num_second)
         res=num_first-num_second;
     else
     {
         res=num_second-num_first;
         flagMin=true;
     }
     //if(flagConv)
     if(!flagMin)
     num_first=res;
     else
         num_first=-res;
     output(res);
 }
 else if(OP_label.contains("Инт"))
 {
  if(num_first>=num_second)
      res=num_first-num_second;
  else res=num_second-num_first;
  num_first=res;
  output(res);
 }
}
}
void MainWindow::output(int res)
{
    if (res==0)
    {
    if(flagOP||flagConv)
    ui->label_up->setText("0 ");
    else
    ui->label_down->setText("0");
    }

    int resH=res/3600;
    int resM=(res%3600)/60;
    int resS=(res%3600)%60;
    QString resultH=QString::number(resH,'g',5);
    QString resultM=QString::number(resM,'g',5);
    QString resultS=QString::number(resS,'g',5);
    if (flagMin)
        ui->label_down->setText("-");
    if(resH!=0)
    {
    if(flagOP||flagConv)
    ui->label_up->setText(ui->label_down->text()+resultH+"ч ");
    else
    ui->label_down->setText(ui->label_down->text()+resultH+"ч ");
    }
    if (resM!=0)
    {
        if(flagOP || flagConv)

        ui->label_up->setText(ui->label_up->text()+resultM+"м ");
        else
        ui->label_down->setText(ui->label_down->text()+resultM+"м ");
    }
    if (resS!=0)
    {
        if(flagOP||flagConv)
        ui->label_up->setText(ui->label_up->text()+resultS+"с");
        else
        ui->label_down->setText(ui->label_down->text()+resultS+"с");
    }
}

void MainWindow::on_pushButton_conv_clicked()
{
if((flagH || flagM || flagS)||num_second!=0)
{
    if(ui->label_down->text()!="0")
    {
    bool flagOT=false;
    double d_res;
    QString result;
    flagConv=true;
    if(num_first==0)
    num_first=num_second;
    if(num_first<0)
    {
     num_first=-num_first;
     flagOT=true;
    }
    if(!(ui->label_up->text().contains("=")))
       ui->label_up->setText(ui->label_up->text()+(" = "));
    if(ui->pushButton_H->isChecked())
        {
       d_res=num_first/3600;
       if(flagOT)
       d_res=-d_res;
       result=QString::number(d_res,'g',5);
       if(!flagOP)
       ui->label_down->setText(result+"ч ");
       ui->pushButton_H->setChecked(false);
        }
    if(ui->pushButton_M->isChecked())
        {
        d_res=num_first/60;
        if(flagOT)
        d_res=-d_res;
        result=QString::number(d_res,'g',5);
        if(!flagOP)
        ui->label_down->setText(result+"м ");
        ui->pushButton_M->setChecked(false);
        }
    if(ui->pushButton_S->isChecked())
        {
        d_res=num_first;
        if(flagOT)
        d_res=-d_res;
        result=QString::number(d_res,'g',5);
        if(!flagOP)
        ui->label_down->setText(result+"с ");
        ui->pushButton_S->setChecked(false);
        }
    flagH=false;
    flagM=false;
    flagS=false;
}
}
}

void MainWindow::on_pushButton_AC_clicked()
{
    num_first=0;
    num_second=0;
    new_label="";
    OP_label="";
    ui->pushButton_H->setChecked(false);
    ui->pushButton_M->setChecked(false);
    ui->pushButton_S->setChecked(false);
    first_num_label="";
    flagEq=false;
    flagH=false;
    flagM=false;
    flagS=false;
    flagOP=false;
    flagConv=false;
    flagMin=false;
    ui->label_down->setText("0");
    ui->label_up->setText("");
}

void MainWindow::on_pushButton_CE_clicked()
{
 if(num_second!=0 && num_first!=0)
 {
 num_second=0;
 flagH=false;
 flagM=false;
 flagS=false;
 flagMin=false;
 flagEq=false;
 ui->pushButton_H->setChecked(false);
 ui->pushButton_M->setChecked(false);
 ui->pushButton_S->setChecked(false);
 ui->label_down->setText("");
 ui->label_up->setText(first_num_label);
 }
 else
 {
  ui->label_down->setText("");
 }
}







