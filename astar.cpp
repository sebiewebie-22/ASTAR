#include "AStar.h"
#include "ControlMode.h"

AStar::AStar(std::shared_ptr<Model> w, float hw): world(w), heuristic_weight(hw) {
    for (const auto &t : world->Tiles) {
        auto n = new Node(t->getXPos(), t->getYPos(), t->getValue());
        nodes.reserve(1);
        nodes.push_back(n);
    }
}

int AStar::getDistance(int startX, int startY, int endX, int endY) {
    int rd = startX-endX; int cd = startY-endY; int h;
    //Euclidian distance (add sqrt)
    //h = rd*rd+cd*cd;
    //Manhattan distance
    //h = abs(rd)+abs(cd);
    //Chebysev distance
    h = std::max(abs(rd),abs(cd));
    return h;
}

std::vector<Node *> AStar::getPath(Node * cur)
{
    auto path = std::vector<Node *>();
    while(cur!=nullptr){
        path.reserve(1);
        path.push_back(cur);
        cur = cur->getParent();
        //qDebug() << cur->getPosX() << "," << cur->getPosY();
    }
    return path;
}

std::vector<Node*> AStar::get_nearbypoints(Node * current) {
    std::vector<Node*> nnodes;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (abs(i)!=abs(j)) {
                int xcur = current->getPosX(); int ycur = current->getPosY();
                auto next = nodes[getIndex(xcur+i, ycur+j)];
                if (next->getPosX() > 0 && next->getPosX() <= world->getCols() && next->getPosY() > 0 && next->getPosY() <= world->getRows() && next->getValue() != std::numeric_limits<int>::max() && next->getValue() != std::numeric_limits<int>::min()) {
                    nnodes.push_back(next);
                }
            }
        }
    }
    return nnodes;
}

int AStar::getIndex(int x, int y) {
    return ((y*world->getCols())+x);
}

void AStar::setHeuristicWeight(float newHw) {
    heuristic_weight = newHw;
}

std::vector<Node *> AStar::findPath(int startX, int startY, int endX, int endY) {
    auto cmp = [&](Node* a, Node* b) {return a->getFCost(heuristic_weight) > b->getFCost(heuristic_weight);};
    auto openList = std::priority_queue<Node *, std::vector<Node *>, decltype(cmp)>(cmp);
    auto closedList = std::vector<Node *>();

    auto start = nodes[getIndex(startX, startY)];

    auto root = start;
    root->setHCost(getDistance(startX, startY, endX, endY));

    openList.push(start);
    root->setList(1);

    while(!openList.empty()) {
        auto current = openList.top(); openList.pop(); current->setList(0);
        //qDebug() << "new current: " << current->getPosX() << ", " << current->getPosY() << ", " << current->getFCost() << "," << current->getGCost() << "," << current->getHCost();

        //closedList.reserve(1);
        //closedList.push_back(current); //current->triggerClosed(); ???

        if (current->getPosX() == endX && current->getPosY() == endY) {
            qDebug() << "path found";
            return getPath(current);
        }

        for (auto nbp : get_nearbypoints(current)) {
            if (nbp->getList() != 2) {
                int newCost = current->getGCost() + getDistance(current->getPosX(), current->getPosY(), nbp->getPosX(), nbp->getPosY());
                if (nbp->getList() == 0) {
                    nbp->setGCost(newCost);
                    nbp->setHCost(getDistance(nbp->getPosX(), nbp->getPosY(), endX, endY));
                    nbp->setParent(current);
                    nbp->setList(1);
                    openList.push(nbp);
                }
                else if (nbp->getList() == 1 && nbp->getGCost() > newCost){
                    nbp->setGCost(newCost);
                    nbp->setHCost(getDistance(nbp->getPosX(), nbp->getPosY(), endX, endY));
                    nbp->setParent(current);
                }
            }
        }
        current->setList(2);
    }
}

/*
AStar::AStar(std::shared_ptr<Model> w, int hw)
{
    world = w;
    for(auto & t : world->Tiles) {
        auto n = new Node(t->getXPos(), t->getYPos(), nullptr, t->getValue());
        nodes.push_back(n);
    }
    heuristic_weight = hw;
}

//if this nearbyPoint is in a spot that is illegal such as a wall
std::vector<Node*> AStar::get_nearbypoints(Node * current) {
    std::vector<Node*> nnodes;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (abs(i)!=abs(j)) {
                int xcur = current->xpos; int ycur = current->ypos;
                auto next = nodes[getIndex(xcur+i, ycur+j)];
                qDebug() << "VALUE:" << next->value;
                if (next->xpos > 0 && next->xpos <= world->getCols() && next->ypos > 0 && next->ypos <= world->getRows() && next->value != std::numeric_limits<int>::max() && next->value != std::numeric_limits<int>::min()) {
                    nnodes.push_back(next);
                }
            }
        }
    }
    return nnodes;
}

//TOTHINK PLACE IN NODE CLASS?
int AStar::getGCost(Node * cur) {
    return cur->value+cur->parent->gCost;
}
int AStar::getHCost(int xstart, int ystart, int xend, int yend) {
    int rd = xstart-xend; int cd = ystart-yend; int h;
    //Euclidian distance (add sqrt)
    h = rd*rd+cd*cd;
    //Manhattan distance
    //h = abs(rd)+abs(cd);
    //Chebysev distance
    //h = max(abs(rd),abs(cd));
    return h;
}
int AStar::getFCost(Node * cur, int hw) {
    return cur->gCost + hw*cur->hCost;
}

std::shared_ptr<std::vector<Node>> AStar::getPath(Node * n)
{
    auto path = std::make_shared<std::vector<Node>>();
    while(n!=nullptr){
        path->push_back(*n);
        n = n->parent;
    }
    return path;
}

int AStar::getIndex(int x, int y) {
    return ((y*world->getCols())+x);
}

void AStar::setHeuristicWeight(int newHW) {
    heuristic_weight = newHW;
}

std::shared_ptr<std::vector<Node>> AStar::findPath(int xstart, int ystart, int xend, int yend) {
    //data structures
    auto cmp = [&](Node* a, Node* b) {return getFCost(a,heuristic_weight) > getFCost(b,heuristic_weight);};
    auto openList = std::make_shared<std::priority_queue<Node *, std::vector<Node *>, decltype(cmp)>>(cmp);

    //create the rootNode
    auto root = nodes[getIndex(xstart, ystart)]; root->parent=nullptr;
    root->gCost = 0; root->hCost = getHCost(xstart, ystart, xend, yend);

    //push rootnode into open
    openList->push(root);
    root->created = true;

    //while openList is not empty
    while(!openList->empty()) {
        //Pop the node with the best finalCost and assign it to currentNode
        auto current = openList->top(); openList->pop(); current->open = false;
        qDebug() << "new current: " << current->xpos << ", " << current->ypos << ", " << getFCost(current, heuristic_weight) << "," << current->hCost << "," << current->gCost;
        //if currentNode's x and y are equal to the goalPoint, then
        if (current->checkEnd(xend,yend)) {
            //push the nodes that are part of the path into solution
            qDebug() << "Path found";
            return getPath(current);
        }
        //for every nearby point around the currentNode do the following
        for (auto nbp : get_nearbypoints(current)) {
            qDebug() << "checking nbp" << nbp->xpos << ", " << nbp->ypos;
            //if a node for this nearbyPoint has been created before , then
            if (nbp->created) {
                //if this nearbyPoint would make a node better than oldNode
                auto old = nbp;
                int newCost = nbp->value+current->gCost;
                qDebug() << "NEW" << newCost;
                qDebug() << "OLD" << old->gCost;
                if (newCost < old->gCost) {
                    //update the oldNode
                    old->gCost = newCost;
                    old->parent = current;
                    //if the oldNode is in closed (TODO Vergelijking nearbyPoint en oldNode?)
                    if (old->closed) {
                        //pop it from closed and push it into open
                        old->closed = false;
                        openList->push(old);
                        qDebug() << "updated old node + added to open list";
                    }
                } else {
                    qDebug() << "skip nbp";
                    continue; //else skip to the next nearbypoint
                }
            }
            //create successorNode
            auto successor = nbp; successor->parent = current;
            successor->hCost = getHCost(successor->xpos, successor->ypos, xend, yend); successor->gCost = getGCost(successor);
            //push successorNode into open
            openList->push(successor); successor->created = true;
            qDebug() << "new node created";
        }
        //push the currentNode into closed
        current->closed = true;
        qDebug() << "current node closed";
    }
    qDebug() << "End node can't be reached";
    return nullptr;
}

//qDebug() << "new current: " << current->xpos << ", " << current->ypos << ", " << getFCost(current, heuristic_weight) << "," << current->hCost << "," << current->gCost;
//qDebug() << "--------------------";
//while(!openListCopy.empty()) {
  //  qDebug() << openListCopy.top()->xpos << ", " << openListCopy.top()->ypos << "," << getFCost(openListCopy.top(), heuristic_weight);
    //openListCopy.pop();
//}
*/
