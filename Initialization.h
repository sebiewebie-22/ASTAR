#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include "Mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"
#include "GraphicalView.h"
#include "TextView.h"
#include "Controller.h"
#include <memory>
#include <QApplication>

class Initialization
{
public:
    Initialization(MainWindow * mw,std::shared_ptr<Model> m,std::shared_ptr<Controller> c, std::shared_ptr<TextView> tv, std::shared_ptr<GraphicalView> gv, QGraphicsScene * scenePtr);
    std::shared_ptr<Model> model;
    MainWindow * w;
    std::shared_ptr<Controller> controller;
    std::shared_ptr<TextView> textView;
    std::shared_ptr<GraphicalView> graphicalView;
    QGraphicsScene * scene;

    int XEnemyAmount = 1;
    void initBars();
    void initializeScene();
    void initTiles();
    void initEnemyViews();
    void initConnections();


};

#endif // INITIALIZATION_H
