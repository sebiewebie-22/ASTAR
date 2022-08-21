#include "node.h"

Node::Node(int x, int y, int v, Node * p) {
    posX = x;
    posY = y;
    parent = p;
    value = v;
}

int Node::getPosX() {
    return posX;
}

int Node::getPosY() {
    return posY;
}

int Node::getGCost() {
    return gCost;
}

int Node::getHCost() {
    return hCost;
}

int Node::getFCost(float hw) { //TODO IMPLEMENT HEURISTIC
    return hw*hCost + gCost;
}
/*
bool Node::getOpen() {
    return open;
}
*/
int Node::getList() {
    return list;
}

int Node::getValue() {
    return value;
}

/*
bool Node::getClosed() {
    return closed;
}
*/
Node * Node::getParent() {
    return parent;
}


void Node::setPosX(int newPosX) {
    posX = newPosX;
}

void Node::setPosY(int newPosY) {
    posY = newPosY;
}

void Node::setGCost(int newGCost) {
    gCost = newGCost;
}

void Node::setHCost(int newHCost) {
    hCost = newHCost;
}

void Node::setList(int newList) {
    list = newList;
}

void Node::setValue(int newValue) {
    value = newValue;
}

/*
void Node::triggerOpen() {
    open = !open;
}

void Node::triggerClosed() {
    closed = !closed;
}
*/
void Node::setParent(Node * newParent) {
    parent = newParent;
}
/*
bool Node::operator<(const Node& a) {
    return getFCost() < a.getFCost();
}
*/
/*
void Node::calculateFCost(int eX, int eY, int hw) {
    fCost = gCost + getHCost(eX, eY);
}

void Node::updateGCost() {
    gCost = value + parent->gCost;
}

int Node::getHCost(int eX, int eY) {
    int rd = xpos-eX; int cd = ypos-eY; int h;
    //Euclidian distance (add sqrt)
    //h = rd*rd+cd*cd;
    //Manhattan distance
    h = abs(rd)+abs(cd);
    //Chebysev distance
    //h = max(abs(rd),abs(cd));
    return h;
}

bool Node::checkEnd(int x, int y) {
    return (xpos==x && ypos==y);
}
*/
