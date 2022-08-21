#ifndef VIEWMODE_H
#define VIEWMODE_H

#include "world.h"
#include "Model.h"
#include <QGraphicsScene>
class Controller;
class View;

class View: public QObject
{
public:
    View();
    virtual void generateView(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) = 0;
    virtual void generateMap(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) = 0;
    virtual void generateProtagonist(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) = 0;
    virtual void generateEnemies(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) = 0;
    virtual void generateHealthPacks(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) = 0;
    //    virtual void generateProtagonist(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) = 0;
//    virtual void generateEnemies(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) = 0;
//    virtual void generateHealthPacks(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) = 0;
    //std::shared_ptr<Controller> Kont_Trol;
    virtual char getViewModeType() = 0;

    const int pixelWidth = 35;
    int getPixelWidth() const;
};

#endif // VIEWMODE_H
