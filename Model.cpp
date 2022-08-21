
#include "Model.h"
#include "Controller.h"
#include "Mainwindow.h"
#include <iostream>
#include <memory>

Model::Model(){

}

Model::~Model()
{

}

void Model::setAnimationSpeed(int newAnimationSpeed)
{
    animationDelay = newAnimationSpeed;
}

