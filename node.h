#ifndef NODE_H
#define NODE_H

#include <memory>
#include "world.h" //world access?

#include "qdebug.h"

class Node;

class Node
{
private:
    //attributes
    int posX;
    int posY;
    Node * parent;
    int value, gCost, hCost;//fCost;
    //bool open = false;
    //bool closed = false;
    int list;

public:
    //methods
    Node(int x, int y, int value, Node * p = nullptr);
    int getPosX();
    int getPosY();
    int getGCost();
    int getHCost();
    int getFCost(float heuristic_weight);
    int getList();
    int getValue();
    //bool getOpen();
    //bool getClosed();
    Node * getParent();
    void setPosX(int newPosX);
    void setPosY(int newPosY);
    void setGCost(int newGCost);
    void setHCost(int newHCost);
    void setFCost(int newFCost);
    //void triggerOpen();
    //void triggerClosed();
    void setList(int newList);
    void setValue(int newValue);
    void setParent(Node * newParent);

    bool operator<(const Node& a);
};

#endif
