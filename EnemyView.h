
#ifndef __EnemyView_h__
#define __EnemyView_h__

// #include "GraphicalView.h"
#include "qgraphicsitem.h"
#include "qpixmap.h"
#include <memory>

class GraphicalView;
class EnemyView;

class EnemyView
{
    public:
    std::shared_ptr<GraphicalView> named_GraphicalView;
    QPixmap *originalProtPixmap = new QPixmap(":/worldImages/enemy.png");
    QPixmap *squichedProtPixmap = new QPixmap(":/worldImages/SquichedEnemy.png");
    QPixmap *XEnemyProtPixmap = new QPixmap(":/worldImages/enemyorange.png");
    QPixmap *PEnemyProtPixmap = new QPixmap(":/worldImages/enemyblue.png");

    QGraphicsPixmapItem *protPixmapItem = new QGraphicsPixmapItem();

    bool Squiched=false;
    bool maxRight=false;
    bool maxLeft=false;
    bool toggleMovementDirection=false;
    int moveCounter=0;

};

#endif
