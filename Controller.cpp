#include "Controller.h"
#include "Mainwindow.h"
#include "View.h"
#include "Model.h"
#include "ControlMode.h"
#include "ui_mainwindow.h"
#include <memory>
#include <iostream>
#include <algorithm>
#include "qapplication.h"
#include <QApplication>
#include<bits/stdc++.h>
#include <QTime>
 #include <QThread>

using namespace std;

Controller::Controller()
{

}

Controller::~Controller()
{

}

void Controller::setNamed_Model(std::shared_ptr<Model> newNamed_Model)
{
    named_Model = newNamed_Model;

}

void Controller::graphicalMovement(QKeyEvent *event)
{
    named_MainWindow->gView->ProtView->saveLatestPosition(named_Model->protje->getXPos(), named_Model->protje->getYPos());

    if(animationDelayPause==false)
    {
        if(event->key() == Qt::Key_Z){
            if(blackTileCheck(1)==false){
                //for (int i=0;i<10;i++){
                named_Model->protje->setYPos(named_Model->protje->getYPos()-1);
                //}
            }}
        if(event->key() == Qt::Key_S){
            if(blackTileCheck(2)==false){
                named_Model->protje->setYPos(named_Model->protje->getYPos()+1);
            }}
        if(event->key() == Qt::Key_Q){
            if(blackTileCheck(3)==false){
                named_Model->protje->setXPos(named_Model->protje->getXPos()-1);
            }
        }
        if(event->key() == Qt::Key_D){
            if(blackTileCheck(4)==false){
                named_Model->protje->setXPos(named_Model->protje->getXPos()+1);
            }
        }
        enemyCheck(named_Model->protje->getXPos(), named_Model->protje->getYPos());
        healthPackCheck(named_Model->protje->getXPos(), named_Model->protje->getYPos());
    }
    animationDelay();

}

bool Controller:: blackTileCheck(int x){
    int pw = named_MainWindow->gView->pixelWidth;

    QObject::disconnect(named_Model->protje.get(),&Protagonist::healthChanged, named_MainWindow->gView.get(), &GraphicalView::HealingDoneView);
    if(effectPause==false)
    QObject::connect(named_Model->protje.get(),&Protagonist::healthChanged, named_MainWindow->gView.get(), &GraphicalView::DamageDoneView);

    for (auto &tile: named_Model->Tiles) {
        if (x==1){
            if (tile->getXPos() == named_Model->protje->getXPos()*pw && tile->getYPos()+pw == named_Model->protje->getYPos()*pw){
                if(tile->getValue()==INFINITY)
                {
                    named_Model->protje->setHealth(named_Model->protje->getHealth()-wallBump());
                    return true;
                }
            }
        }
        if (x==2){
            if (tile->getXPos() == named_Model->protje->getXPos()*pw && tile->getYPos()-pw == named_Model->protje->getYPos()*pw){
                if(tile->getValue()==INFINITY)
                {
                    named_Model->protje->setHealth(named_Model->protje->getHealth()-wallBump());
                    return true;
                }

            }

        }
        if (x==3){
            if (tile->getXPos()+pw == named_Model->protje->getXPos()*pw && tile->getYPos() == named_Model->protje->getYPos()*pw){
                if(tile->getValue()==INFINITY)
                {
                    named_Model->protje->setHealth(named_Model->protje->getHealth()-wallBump());
                    return true;
                }
            }

        }
        if (x==4){
            if (tile->getXPos()-pw == named_Model->protje->getXPos()*pw && tile->getYPos() == named_Model->protje->getYPos()*pw){
                if(tile->getValue()==INFINITY)
                {
                    named_Model->protje->setHealth(named_Model->protje->getHealth()-wallBump());
                    return true;
                }
            }

        }
    }
    QObject::disconnect(named_Model->protje.get(),&Protagonist::healthChanged, named_MainWindow->gView.get(), &GraphicalView::DamageDoneView);
    if(effectPause==false)
    QObject::connect(named_Model->protje.get(),&Protagonist::healthChanged, named_MainWindow->gView.get(), &GraphicalView::HealingDoneView);

    return false;
}

void Controller::healthPackCheck(int posX,int posY){
    int index = 0;
    for (auto &HP: named_Model->HealthPacks) {
        if (HP->getXPos() == posX && HP->getYPos() == posY) {
            if(named_Model->HealthPacks[index]->getValue()>0){
                if ((named_Model->protje->getEnergy()+named_Model->HealthPacks[index]->getValue())<100){
                    named_Model->protje->setEnergy((named_Model->protje->getEnergy())+named_Model->HealthPacks[index]->getValue());}

                else if ((named_Model->protje->getEnergy()+named_Model->HealthPacks[index]->getValue())>=100){
                    named_Model->protje->setEnergy(100);
                }

                if ((named_Model->protje->getHealth()+named_Model->HealthPacks[index]->getValue())<100){
                    named_Model->protje->setHealth((named_Model->protje->getHealth())+named_Model->HealthPacks[index]->getValue());
                }

                else if ((named_Model->protje->getHealth()+named_Model->HealthPacks[index]->getValue())>=100){
                    named_Model->protje->setHealth(100);
                }

                named_Model->HealthPacks[index]->setValue(0);
                named_MainWindow->gView->HealthPackViews[index]->named_GraphicalView=named_MainWindow->gView;
                named_MainWindow->gView->HealthPackViews[index]->healthPackTakenView();
            }
        }
        index++;
    }
    return;
}

int Controller::wallBump()
{
    int randNum = (rand() % 3) + 1;
    if(randNum==1){
        qDebug()<<"Mario bumped into a wall. You lost 3 health.";
        return 3;
        //mody->protje->setValue(newProtValue);
    }
    if(randNum==2){
        qDebug()<<"Mario cannot seem to go trough dark void. You lost 5 health.";
        return 5;
    }
    if(randNum==3){
        qDebug()<<"Mario was guided to the dark side. You lost 7 health.";
        return 7;
    }
    return 0;
}

void Controller::moveXEnemy()
{
    for (auto &enemy: named_Model->Enemies) {
        Enemy *Etje;
        std::vector<std::unique_ptr<Enemy>>::iterator itr = std::find(named_Model->Enemies.begin(), named_Model->Enemies.end(), enemy);
        int index= std::distance(named_Model->Enemies.begin(), itr);

        Etje = enemy.get();
        if(dynamic_cast<XEnemy*>(Etje)!=NULL)
        {
            std::shared_ptr<EnemyView> eView = named_MainWindow->gView->EnemyViews[index];
            if(enemy->getDefeated()==false){
                if(eView->toggleMovementDirection==false){
                    if(eView->moveCounter % 2 == 0){
                        named_Model->Enemies[index]->setXPos(named_Model->Enemies[index]->getXPos()+1);
                        eView->protPixmapItem->setPos(eView->protPixmapItem->x()+named_MainWindow->gView->pixelWidth,eView->protPixmapItem->y());
                    }

                    eView->moveCounter++;
                    if(eView->moveCounter>4){
                        eView->toggleMovementDirection=true;}
                }

                else if(eView->toggleMovementDirection==true){
                    if(eView->moveCounter % 2 == 0){
                        named_Model->Enemies[index]->setXPos(named_Model->Enemies[index]->getXPos()-1);
                        eView->protPixmapItem->setPos(eView->protPixmapItem->x()-named_MainWindow->gView->pixelWidth,eView->protPixmapItem->y());
                    }
                    eView->moveCounter--;
                    if(eView->moveCounter<0){
                        eView->toggleMovementDirection=false;}
                }
            }
        }
    }
}


void Controller::changeProtPosition(int x, int y)
{
    named_Model->protje->setEnergy(named_Model->protje->getEnergy()-named_Model->sweat);
    named_MainWindow->gView->updateBars();
    qDebug() << named_MainWindow->ui->horizontalSlider->value();

}

void Controller::enemyCheck(int posX, int posY) {
    int defeatedEnemyCounter=0;
    for (auto &enemy: named_Model->Enemies) {
        Enemy *Etje;
        if(enemy->getDefeated()==false){
            if (enemy->getXPos() == posX && enemy->getYPos() == posY) {
                QObject::disconnect(named_Model->protje.get(),&Protagonist::healthChanged, named_MainWindow->gView.get(), &GraphicalView::HealingDoneView);

                if (((named_Model->protje->getHealth())-(named_Model->EnemyDamage))>0 && ((named_Model->protje->getEnergy())-(named_Model->EnergyChange))>0 ){
                    Etje = enemy.get();

                    //In case of PEnemy
                    if(dynamic_cast<PEnemy*>(Etje)!=NULL)
                    {
                        named_MainWindow->gView->PEnemyEffect(enemy->getXPos(),enemy->getYPos(),(named_Model->EnemyDamage)*2*300);
                        named_Model->protje->setEnergy(100);

                        for(int x=0;x<(named_Model->EnemyDamage)*2;x++){
                            effectPause=true;
                            named_Model->protje->setHealth((named_Model->protje->getHealth())-1);
                            named_MainWindow->gView->updateBars();
                            named_Model->protje->setXPos(enemy->getXPos());
                            named_Model->protje->setYPos(enemy->getYPos());
                            std::this_thread::sleep_for(std::chrono::milliseconds(300));
                            qApp->processEvents();
                        }
                        enemy->setDefeated(true);
                    }

                    //In case of Enemy
                    else{
                        named_Model->protje->setHealth((named_Model->protje->getHealth())-(named_Model->EnemyDamage));
                        named_Model->protje->setEnergy(100);
                        enemy->setDefeated(true);
                    }

                    //Add more cases eventually...

                }
                else {
                    qDebug() << "You lost";
                    emit lost();
                }

            }
        }
        else{
            defeatedEnemyCounter++;
        }
    }

    if(defeatedEnemyCounter == named_Model->Enemies.size()){
        qDebug() << "You won!";

        qApp->closeAllWindows();
        qApp->processEvents();
    }
    return;
}

void Controller::animationDelay()
{
    animationDelayPause=true;
    QTime dieTime= QTime::currentTime().addMSecs((named_Model->animationDelay)*5);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    animationDelayPause=false;
}
/*
void Controller::pathFinder(int xend, int yend) {
    auto pathfind = std::make_shared<PathFinder>();
    auto path = pathfind->getPath(named_Model->protje->getXPos(),named_Model->protje->getYPos(),xend,yend,named_Model,1);
    if (path != nullptr) {
        named_Model->protje->setYPos(yend);
        named_Model->protje->setXPos(xend);
        //visualize function (graphicalview?)
    }
}
*/
