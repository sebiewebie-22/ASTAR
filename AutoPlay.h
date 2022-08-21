#ifndef __AutoPlay_h__
#define __AutoPlay_h__

#include "ControlMode.h"
#include "Model.h"
#include "PathFinder.h"


// __interface ControlMode;
class AutoPlay;

class AutoPlay: public ControlMode
{
public:
    AutoPlay(std::shared_ptr<Model> world);
    Enemy* getDefeatableEnemyNearby();
    Tile* getHealNearby();
    int getNrOfEnemies();
    int getDistance(int x, int y);
    void playGame();

private:
    std::shared_ptr<Model> world;
};

#endif
