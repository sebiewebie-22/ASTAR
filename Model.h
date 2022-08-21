#ifndef __Model_h__
#define __Model_h__

// #include "Controller.h"
#include "world.h"
#include "XEnemy.h"
#include <memory>
#include <iostream>


class Controller;
class XEnemy;
class Model;

class Model: public QObject,public World, public std::enable_shared_from_this<Model>
{
    Q_OBJECT
    public:
    Model();
    ~Model();

    std::unique_ptr<Protagonist> protje;
    std::vector<std::unique_ptr<Enemy>> Enemies;
    std::vector<std::unique_ptr<PEnemy>> PEnemies;
    std::vector<std::unique_ptr<XEnemy>> XEnemies;
    std::vector<std::unique_ptr<Tile>> HealthPacks;
    std::vector<std::unique_ptr<Tile>> Tiles;
    std::shared_ptr<Controller> named_Controller;

    bool xTooLow=false;
    bool xTooHigh=false;
    bool yTooHigh=false;
    bool yTooLow=false;

    int animationDelay=0;
    int EnemyDamage = 5;
    int HealthPackHeal = 3;
    int EnergyChange = 10;
    int sweat = 1;

    //For multiple protagonists:
    //std::vector<std::unique_ptr<Protagonist>> protjes;

    void setAnimationSpeed(int newAnimationSpeed);
};

#endif
