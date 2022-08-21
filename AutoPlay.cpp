/*
#include "AutoPlay.h"
#include "ControlMode.h"

AutoPlay::AutoPlay(std::shared_ptr<Model> w): world(w) {

}

Enemy* AutoPlay::getDefeatableEnemyNearby() {
    int dNearest = INFINITY; int d; Enemy* enemyNearby = nullptr;
    bool nearbyAndDefeatable = false;

    for (auto &e : world->Enemies) {
        d = getDistance(e->getXPos(), e->getYPos());

        if (d < dNearest && !e->getDefeated()) {
            if (world->protje->getEnergy() >= getDistance(e->getXPos(), e->getYPos())) {
                if (dynamic_cast<PEnemy*>(e)!=NULL) {
                    if((world->EnemyDamage*2)+1 <= world->protje->getHealth()){
                        nearbyAndDefeatable = true;
                    }
                } else {
                    if(world->EnemyDamage*2 <= world->protje->getHealth()){
                        nearbyAndDefeatable = true;
                    }
                }
            }
        }
        if (nearbyAndDefeatable) {
            enemyNearby = e;
            dNearest = getDistance(e->getXPos(), e->getYPos());
        }
    }

    return enemyNearby;
}

Tile* AutoPlay::getHealNearby() {
    int dNearest = INFINITY; int d; Tile* healNearby = nullptr;

    for (auto &h : world->HealthPacks) {
        d = getDistance(h->getXPos(), h->getYPos());
        if (world->protje->getEnergy() >= d) {
            if (d < dNearest) {
                dNearest = d;
                healNearby = h;
            }
        }
    }
    return healNearby;
}

int AutoPlay::getNrOfEnemies() {
    return world->Enemies.size();
}

int AutoPlay::getDistance(int x, int y) {
    int diffX = std::abs(world->protje->getXPos()-x);
    int diffY = std::abs(world->protje->getYPos()-y);

    return diffX+diffY;
}

void AutoPlay::playGame() {
    auto pf = std::make_shared<PathFinder>;

    int nrOfEnemies = getNrOfEnemies();
    while (nrOfEnemies != 0) {
        //LOOK FOR FIGHT
        auto enemyToFight = getDefeatableEnemyNearby();

        //FIGHT POSSIBLE? FIGHT!
        if (enemyToFight != nullptr) {
            auto pathToEnemy = pf->getPath(world->protje->getXPos(), world->protje->getYPos(), enemyToFight->getXPos(), enemyToFight->getYPos());
            //TODO MOVE ANIMATION
        } else { //NO FIGHT POSSIBLE? HEAL
            auto healNearby = getHealNearby();

            if (healNearby == nullptr) {
                break; //NO MORE OPTIONS ->DEATH
            } else {
                auto pathToHeal = pf->getPath(world->protje->getXPos(), world->protje->getYPos(), healNearby->getXPos(), healNearby->getYPos());
                //TODO MOVE ANIMATION
            }
        }
    }
}
*/
