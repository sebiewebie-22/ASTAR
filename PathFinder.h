#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "node.h"
#include "AStar.h"


class PathFinder
{
public:
    PathFinder();
    std::vector<Node *>  getPath(int startx, int starty, int endx, int endy, std::shared_ptr<Model> world, int heuristic);
};

#endif // PATHFINDER_H
