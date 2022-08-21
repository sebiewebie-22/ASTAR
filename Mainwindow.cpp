#include "Mainwindow.h"
#include "Controller.h"
#include "ui_mainwindow.h"
#include <iostream>
//#include "Controller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    //For loop decides if protagonist control goes to graphical method or text method
    if(currentViewMode->getViewModeType() == 'T') // T means TextView
    {
        //named_Controller->textMovement(event);

    }else if(currentViewMode->getViewModeType() == 'G') // G means GraphicalView
    {
        named_Controller->graphicalMovement(event);
        //qDebug() << "test";

    }else
    {
        qDebug() << "currentViewMode did not return valid character. The View Mode might not be set correctly.";
    }
}

