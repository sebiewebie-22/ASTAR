#include "Mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"
#include "GraphicalView.h"
#include "TextView.h"
#include "Controller.h"
#include "Initialization.h"
#include <memory>
#include <QApplication>

int main(int argc, char *argv[])
{
    std::shared_ptr<Model> world1 = std::make_shared<Model>();
    world1->createWorld(":/worldImages/maze3.png",0,0,0);

    world1->Tiles = world1->getTiles();
    auto algo = std::make_shared<PathFinder>();
    algo->getPath(0,22,1200,1205,world1,0.9f);
    /*
    std::shared_ptr<Model> testWorld = std::make_shared<Model>();
    QGraphicsScene * scenePtr = nullptr;
    QApplication a(argc, argv);
    MainWindow w= new MainWindow;
    std::shared_ptr<TextView> textView = std::make_shared<TextView>();
    std::shared_ptr<Controller> control = std::make_shared<Controller>();
    std::shared_ptr<GraphicalView> graphicalView = std::make_shared<GraphicalView>();

    Initialization * i= new Initialization(&w, testWorld,control,textView,graphicalView,scenePtr);

    return a.exec();
    */
}

