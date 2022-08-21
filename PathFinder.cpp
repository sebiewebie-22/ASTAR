#include "pathfinder.h"

#include "Model.h"
#include <QDebug>


PathFinder::PathFinder()
{

}

std::vector<Node *> PathFinder::getPath(int startx, int starty, int endx, int endy, std::shared_ptr<Model> world,int heuristic_weight)
{
    std::vector<Node *> path;

    auto algo = std::make_shared<AStar>(world, heuristic_weight); //TODO WORLD?
    qDebug() << "PF: algo init";

    auto t0 = std::chrono::system_clock::now();
    qDebug() << "PF: chrono init";
    path = algo->findPath(startx,starty,endx,endy);
    auto t1 = std::chrono::system_clock::now();

    std::string s = std::to_string(std::chrono::duration<double>(t1 - t0).count()) + 's';
    std::cout<<s<<std::endl;

    return path;
}
