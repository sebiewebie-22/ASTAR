
#ifndef __TileView_h__
#define __TileView_h__

 #include "GraphicalView.h"
#include "qgraphicsitem.h"
#include "qpixmap.h"
#include <memory>

class GraphicalView;
class HealthPackView;

class HealthPackView
{
    public:
    std::shared_ptr<GraphicalView> named_GraphicalView;
    QPixmap *originalProtPixmap = new QPixmap(":/worldImages/healthpack.png");
    QPixmap *blackProtPixmap = new QPixmap(":/worldImages/BlackHealthPack.vpp");
    QPixmap *HPTakenProtPixmap = new QPixmap(":/worldImages/whitetile.png");
    QGraphicsPixmapItem *protPixmapItem = new QGraphicsPixmapItem();

    void healthPackTakenView();
};

#endif
