#ifndef __Controller_h__
#define __Controller_h__


#include <memory>
#include <QKeyEvent>

#include "PathFinder.h"

class View;
class Model;
class MainWindow;
class ControlMode;
class Controller;

class Controller: public QObject
{
    Q_OBJECT

    public:
    Controller();
    ~Controller();

    std::shared_ptr<Model> named_Model;
    MainWindow * named_MainWindow;

    void graphicalMovement(QKeyEvent *event);
    void setNamed_Model(std::shared_ptr<Model> newNamed_Model);
    bool blackTileCheck(int x);
    void enemyCheck(int posX, int posY);
    void healthPackCheck(int posX, int posY);
    int  wallBump();
    void moveXEnemy();
    void animationDelay();
    void pathFinder(int xend, int yend);
    bool effectPause=false;
    bool animationDelayPause=false;

signals:
    void lost();
public slots:
    void changeProtPosition(int x, int y);

};

#endif
