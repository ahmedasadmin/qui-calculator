#include "mainwindow.h"
#include "ui_mainwindow.h"
double CalcVal = 0.0;


bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->txtDisplay->setText("START YOUR MYSTERIOUS CALCS");

    QPushButton* numButtons[10];
    for (int i = 0; i < 10; ++i){
            QString btnName = "btnNo" + QString::number(i);
            numButtons[i] = MainWindow::findChild<QPushButton*>(btnName);
            connect(numButtons[i], SIGNAL(released()), this, SLOT(numberPressed()) ) ;
    }
    connect(ui->btnNoMultiplication, SIGNAL(released()), this, SLOT(MathButtonPressed()) ) ;
    connect(ui->btnDivision, SIGNAL(released()), this, SLOT(MathButtonPressed()) ) ;
    connect(ui->btnNoAdd, SIGNAL(released()), this, SLOT(MathButtonPressed()) ) ;
    connect(ui->btnNoSub, SIGNAL(released()), this, SLOT(MathButtonPressed()) ) ;
    connect(ui->btnNoEqual, SIGNAL(released()), this, SLOT(EqualButton()) ) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numberPressed(){
    QPushButton* button = (QPushButton*) sender();
    QString butVal = button->text();
    QString displayVal = ui->txtDisplay->text();


    if (displayVal[0].isDigit()){
        QString newVal = displayVal + butVal;
        ui->txtDisplay->setText(newVal);
    }
    else{
          ui->txtDisplay->setText(butVal);
    }

}

void MainWindow::MathButtonPressed()
{
     divTrigger = false;
     multTrigger = false;
     addTrigger = false;
     subTrigger = false;

     QString displayVal = ui->txtDisplay->text();
     CalcVal = displayVal.toDouble();
     QPushButton* button = (QPushButton *) sender();
     QString butVal = button->text();


     if(QString::compare(butVal,"/", Qt::CaseInsensitive) == 0){

         divTrigger = true;

     }else if(QString::compare(butVal,"x", Qt::CaseInsensitive) == 0){

         multTrigger = true;

     }else if(QString::compare(butVal,"+", Qt::CaseInsensitive) == 0){

         addTrigger = true;

     } else if(QString::compare(butVal,"-", Qt::CaseInsensitive) == 0){

         subTrigger = true;

     }

      ui->txtDisplay->clear();
}

void MainWindow::EqualButton()
{
    double  solution = 0.0;
    QString displayVal = ui->txtDisplay->text();
    double dbDisplayVal = displayVal.toDouble();
    if (addTrigger || subTrigger || divTrigger || multTrigger){
        if(addTrigger){
            solution = dbDisplayVal + CalcVal;
        }
       if(subTrigger){
            solution = dbDisplayVal - CalcVal;
        }
      if(divTrigger){
            solution = dbDisplayVal/ CalcVal;
        }
       if (multTrigger){
            solution = dbDisplayVal * CalcVal;
        }
    }
    ui->txtDisplay->setText(QString::number(solution));
}
