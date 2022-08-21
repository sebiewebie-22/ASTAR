#ifndef GRAPHICALVIEW_H
#define GRAPHICALVIEW_H

#include "EnemyView.h"
#include "ProtagonistView.h"
#include "HealthPackView.h"
#include "View.h"

class EnemyView;
class ProtagonistView;
class HealthPackView;
class GraphicalView;

class GraphicalView: public View
{

public:
    //Controllable Views:
    std::vector<std::shared_ptr<EnemyView>> EnemyViews;
    std::shared_ptr<ProtagonistView> ProtView;    //For multiple Protagonists use: public: std::vector<std::shared_ptr<ProtagonistView>> ProtagonistViews;
    std::vector<std::shared_ptr<HealthPackView>> HealthPackViews;

    QGraphicsScene * theScene;
    std::shared_ptr<Controller> named_Controller;

public:
    GraphicalView();
    void generateView(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene);
    void generateMap(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene);
    void generateProtagonist(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene);
    void generateEnemies(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene);
    void generateHealthPacks(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene);
    char getViewModeType(){return 'G';}
    void winScene();
    void PEnemyEffect(int x,int y,int time);
    void updateBars();

public slots:
    void HealingDoneView();
    void DamageDoneView();
    void lostScene();

};

#endif // GRAPHICALVIEW_H
