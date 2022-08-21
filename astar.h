#ifndef __AStar_h__
#define __AStar_h__

#include "ControlMode.h"
#include "node.h" //create node
#include "Model.h"
#include <iostream>
#include <queue>
#include <unordered_set>

// __interface ControlMode;
class AStar;

class AStar//: public ControlMode
{
private:
    //variables
    std::shared_ptr<Node> start;
    std::shared_ptr<Node> end;
    float heuristic_weight;
    std::shared_ptr<Model> world;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<Node*> nodes;
    //std::priority_queue<Node*, std::vector<Node*>, cmp> openList;

public:
    //methods
    AStar(std::shared_ptr<Model> world, float heuristic_weight);
    std::vector<Node *> findPath(int startX, int startY, int endX, int endY);
    std::vector<Node*> get_nearbypoints(Node * cur_node);
    int getDistance(int startX, int startY, int endX, int endY);
    std::vector<Node *> getPath(Node * n);
    int getIndex(int x, int y);
    void setHeuristicWeight(float newHeuristicWeight);
};

#endif
