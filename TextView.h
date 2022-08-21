
#ifndef __TextBased_h__
#define __TextBased_h__

#include "EnemyViewText.h"
 #include "ProtagonistViewText.h"
 #include "HealthPackViewText.h"
#include "View.h"

class EnemyViewText;
class ProtagonistViewText;
class HealthPackViewText;

class TextView: public View
{

    public:
    TextView();
    std::shared_ptr<EnemyViewText> named_EnemyViewText;
    std::shared_ptr<ProtagonistViewText> named_ProtagonistViewText;
    std::shared_ptr<HealthPackViewText> named_TileViewText;

     void generateView(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene);
     void generateMap(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene);
     void generateProtagonist(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) ;
     void generateEnemies(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) ;
     void generateHealthPacks(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene);
     char getViewModeType(){return 'T';}
     void changeView(QPixmap * Qpixmap);

     int getTileHeight(){return tileHeight;}
     int getTileWidth(){return tileWidth;}

private:
    const int tileHeight = 35;
    const int tileWidth = 25;

};

#endif
