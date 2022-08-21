#ifndef __ProtagonistView_h__
#define __ProtagonistView_h__

#include "GraphicalView.h"
#include "Controller.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <memory>

class GraphicalView;
class ProtagonistView;

class ProtagonistView : public QObject
{
    Q_OBJECT

    public:
    ProtagonistView();
    std::shared_ptr<GraphicalView> named_GraphicalView;

    QPixmap *originalProtPixmap = new QPixmap(":/worldImages/protagonist.png");
    QPixmap *redProtPixmap = new QPixmap(":/worldImages/RedMario.png");
    QPixmap *greenProtPixmap = new QPixmap(":/worldImages/GreenMario.png");
    QGraphicsPixmapItem *protagonist_pixmapItem = new QGraphicsPixmapItem();

    void saveLatestPosition(int x,int y);
    int previousX;
    int previousY;
    void setUpViews();
    int pixelWidth = 35;

public slots:
    void changeProtPosition(int x,int y);
};

#endif
