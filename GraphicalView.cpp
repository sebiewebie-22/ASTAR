#include "GraphicalView.h"
#include "Controller.h"
#include "Mainwindow.h"
#include "qapplication.h"
#include "qguiapplication.h"
#include "qcoreapplication.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <iostream>
#include <thread>


GraphicalView::GraphicalView()
{
    ProtView = std::make_shared<ProtagonistView>();
}

void GraphicalView::generateView(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene)
{
    //Here we can call all the methods that are required to visualise the game
    //This one is called to represent all tiles of the map
    generateMap(worldPtr, scene);

    //Here we generate the views for the Protagonist(s), Enemies & HealthPacks
    generateProtagonist(worldPtr, scene);
    generateEnemies(worldPtr, scene);
    generateHealthPacks(worldPtr, scene);
}

void GraphicalView::generateMap(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene)
{
    int posX, posY, currentColumn, brightness;
    QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    QBrush grayBrush(Qt::gray);
    QPen grayPen;
    QColor gray;

    posX = 0;
    posY = 0;
    currentColumn = 0;

    for(auto &tile: worldPtr->Tiles)
    {
        //print white or black tile
        if(tile->getValue() == INFINITY){
            scene->addRect(posX, posY, pixelWidth, pixelWidth, blackPen, blackBrush);

        }else{
            //set gray to correct grayscale value using HSV color scale (1st + 2nd argument don't matter, 3rd = brightness -> 0 for black, 255 for white, so opposite of how it's stored in tiles)
            brightness = tile->getValue()*255.0F;
            gray.setHsv(0,0, brightness);
            grayPen.setColor(gray);
            grayBrush.setColor(gray);
            scene->addRect(posX, posY, pixelWidth, pixelWidth, grayPen, grayBrush);

        }

        //set tile positions so they have the coords that correspond to tile sizes
        tile->setXPos(posX);
        tile->setYPos(posY);

        //move to next column
        posX += pixelWidth;
        currentColumn++;

        //if an entire row is completed -> move down a row
        if(currentColumn == worldPtr->getCols()){
            posY += pixelWidth;
            currentColumn = 0;
            posX = worldPtr->getCols()/2-10;
        }
    }
}

void GraphicalView::generateProtagonist(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) {
    int posX, posY;
    const QPixmap &protPixmap(ProtView->originalProtPixmap->scaled(pixelWidth, pixelWidth, Qt::KeepAspectRatio));

    posX = (worldPtr->protje->getXPos())*pixelWidth;
    posY = (worldPtr->protje->getYPos())*pixelWidth;

    //For multiple protagonists, store the ProtagonistView in aggregation
    //ProtagonistViews.push_back(ProtView);

    ProtView->protagonist_pixmapItem->setPos(posX, posY);
    scene->addItem(ProtView->protagonist_pixmapItem);
    ProtView->protagonist_pixmapItem->setPixmap(protPixmap);
}


void GraphicalView::generateEnemies(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) {
    int posX, posY;

    for (auto &enemy: worldPtr->Enemies) {
        std::shared_ptr<EnemyView> EneView = std::make_shared<EnemyView>();
        EnemyViews.push_back(EneView);
        const QPixmap &protPixmap(EneView->originalProtPixmap->scaled(pixelWidth, pixelWidth, Qt::KeepAspectRatio));
        EneView->protPixmapItem->setPixmap(protPixmap);

        posX = (enemy->getXPos())*pixelWidth;
        posY = (enemy->getYPos())*pixelWidth;

        scene->addItem(EneView->protPixmapItem);
        EneView->protPixmapItem->setPos(posX, posY);
        QObject::connect(enemy.get(),&Enemy::dead, this, &GraphicalView::DamageDoneView);
    }
}

void GraphicalView::generateHealthPacks(std::shared_ptr<Model> worldPtr, QGraphicsScene *scene) {
    int posX, posY;

    for (auto &HP: worldPtr->HealthPacks) {
        //create pixmapitem

        std::shared_ptr<HealthPackView> HPView = std::make_shared<HealthPackView>();
        HealthPackViews.push_back(HPView);
        const QPixmap &protPixmap(HPView->originalProtPixmap->scaled(pixelWidth, pixelWidth, Qt::KeepAspectRatio));
        HPView->protPixmapItem->setPixmap(protPixmap);
        HP->setValue(15);

        posX = (HP->getXPos())*pixelWidth;
        posY = (HP->getYPos())*pixelWidth;

        scene->addItem(HPView->protPixmapItem);
        HPView->protPixmapItem->setPos(posX, posY);
    }
}

void GraphicalView::DamageDoneView()
{

    for(int i=10;i>0;i--){

        const QPixmap &protPixmap(ProtView->redProtPixmap->scaled(pixelWidth*i, pixelWidth*i, Qt::KeepAspectRatio));
        ProtView->protagonist_pixmapItem->setPixmap(protPixmap);
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        std::this_thread::sleep_for(std::chrono::milliseconds(named_Controller->named_Model->animationDelay));

        qApp->processEvents();
    }
    const QPixmap &protPixmap(ProtView->originalProtPixmap->scaled(pixelWidth, pixelWidth, Qt::KeepAspectRatio));
    ProtView->protagonist_pixmapItem->setPixmap(protPixmap);

    updateBars();

    for (int i=0;i<named_Controller->named_Model->Enemies.size();i++) {
        const QPixmap &protPixmap2(EnemyViews[i]->squichedProtPixmap->scaled(pixelWidth*2, pixelWidth*2, Qt::KeepAspectRatio));
        if (named_Controller->named_Model->Enemies[i]->getDefeated()==true){
            if(EnemyViews[i]->Squiched==false){
                EnemyViews[i]->protPixmapItem->setPixmap(protPixmap2);
                //qDebug()    << EnemyViews[i]->protPixmapItem->x();
                EnemyViews[i]->protPixmapItem->setPos( EnemyViews[i]->protPixmapItem->x()-(pixelWidth/2), EnemyViews[i]->protPixmapItem->y()-(pixelWidth/2));
                EnemyViews[i]->Squiched=true;
            }
        }
    }
    named_Controller->named_MainWindow->gView->updateBars();

}

void GraphicalView::lostScene()
{
    //    const QPixmap &protPixmap(ProtView->greenProtPixmap->scaled(pixelWidth*i, pixelWidth*i, Qt::KeepAspectRatio));
    //    ProtView->protagonist_pixmapItem->setPixmap(protPixmap);

}


void GraphicalView::winScene()
{
    //    const QPixmap &protPixmap(ProtView->greenProtPixmap->scaled(pixelWidth*i, pixelWidth*i, Qt::KeepAspectRatio));
    //    ProtView->protagonist_pixmapItem->setPixmap(protPixmap);
}

void GraphicalView::PEnemyEffect(int x, int y, int time)
{
    QPixmap *poison = new QPixmap(":/skull2.png");
    for(int i=x-1;i<x+2;i++)
        {
        for(int j=y-1;j<y+2;j++)
        {
            QGraphicsPixmapItem *poisonPixmapItem = new QGraphicsPixmapItem();
            QPixmap potato= poison->scaled(pixelWidth, pixelWidth, Qt::KeepAspectRatio);
            poisonPixmapItem->setPixmap(potato);
            theScene->addItem(poisonPixmapItem);
            poisonPixmapItem->setPos(i*pixelWidth, j*pixelWidth);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            std::this_thread::sleep_for(std::chrono::milliseconds(named_Controller->named_Model->animationDelay));

            qApp->processEvents();
        }
    }
    qApp->processEvents();
}


void GraphicalView::HealingDoneView()
{
    for(int i=10;i>0;i--){

        const QPixmap &protPixmap(ProtView->greenProtPixmap->scaled(pixelWidth*i, pixelWidth*i, Qt::KeepAspectRatio));
        ProtView->protagonist_pixmapItem->setPixmap(protPixmap);
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        std::this_thread::sleep_for(std::chrono::milliseconds(named_Controller->named_Model->animationDelay));
        qApp->processEvents();
    }
    const QPixmap &protPixmap(ProtView->originalProtPixmap->scaled(pixelWidth, pixelWidth, Qt::KeepAspectRatio));
    ProtView->protagonist_pixmapItem->setPixmap(protPixmap);
    updateBars();

}

void GraphicalView::updateBars(){

    named_Controller->named_MainWindow->ui->progressBar->setValue(named_Controller->named_Model->protje->getHealth());
    named_Controller->named_MainWindow->ui->progressBar_2->setValue(named_Controller->named_Model->protje->getEnergy());
    qApp->processEvents();
}
