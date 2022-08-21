#include "Initialization.h"
#include "XEnemy.h"

Initialization::Initialization(MainWindow * mw,std::shared_ptr<Model> m,std::shared_ptr<Controller> c, std::shared_ptr<TextView> tv, std::shared_ptr<GraphicalView> gv, QGraphicsScene * scenePtr)
{
    model=m;
    graphicalView=gv;
    textView=tv;
    controller=c;
    scene=scenePtr;
    w=mw;

    model->named_Controller = controller;
    w->named_Controller=model->named_Controller;
    model->named_Controller->named_MainWindow=w;
    model->named_Controller->setNamed_Model(model);

    initializeScene();
    initBars();
    initConnections();

}

void Initialization::initBars()
{
    //Initialize status bars
    graphicalView->updateBars();
}


void Initialization::initializeScene(){

    //Preparing World&Scene
    w->show();
    w->setGraphicalView(graphicalView);
    w->setTextView(textView);
    model->createWorld(":/worldImages/simple1.png", 4, 4, 0);
    initTiles();
    scene = w->getScenePtr();

    //Generate the view graphically or textually
    graphicalView->theScene = scene;
    graphicalView->generateView(model, scene);
    initEnemyViews();
    w->setCurrentViewMode(graphicalView);
    graphicalView->ProtView->named_GraphicalView= graphicalView;
    graphicalView->named_Controller= controller;
}

void Initialization::initTiles()
{
    //Get characters & Items:
    model->Tiles = model->getTiles();
    model->protje = model->getProtagonist();
    model->Enemies = model->getEnemies();
    model->HealthPacks = model->getHealthPacks();

    //Preparing PEnemies & XEnemies
    Enemy *Etje;
    PEnemy *Ptje;
    XEnemy *Xtje;
    int XEnemycounter =0;

    for(auto &enemy:model->Enemies){
        Etje = enemy.get();
        Ptje = dynamic_cast<PEnemy*>(Etje);
        std::unique_ptr<PEnemy> UPtje(Ptje);


        if (UPtje == NULL && XEnemycounter<XEnemyAmount){
            std::vector<std::unique_ptr<Enemy>>::iterator itr = std::find(model->Enemies.begin(), model->Enemies.end(), enemy);
            int index= std::distance(model->Enemies.begin(), itr);

            std::unique_ptr<XEnemy> Xen= std::make_unique<XEnemy>(enemy->getXPos(),enemy->getYPos(),enemy->getValue());
            model->Enemies.at(index) = std::move(Xen);
            Xtje=Xen.get();
            std::unique_ptr<XEnemy> UXtje(Xtje);
            model->XEnemies.push_back(std::move(UXtje));
            XEnemycounter++;
        }

        if(UPtje != NULL){
            model->PEnemies.push_back(std::move(UPtje));
        }
    }

    //Set protagonist at starting position:
    model->protje->setXPos(1);
    model->protje->setYPos(1);
}

void Initialization::initEnemyViews()
{
    for(auto &enemy:model->Enemies){
        Enemy *Etje;
        PEnemy *Ptje;
        XEnemy *Xtje;

        std::vector<std::unique_ptr<Enemy>>::iterator itr = std::find(model->Enemies.begin(), model->Enemies.end(), enemy);
        int index= std::distance(model->Enemies.begin(), itr);

        Etje = enemy.get();
        if(dynamic_cast<PEnemy*>(Etje)!=NULL)
        {
            const QPixmap &specificEnemyView2(graphicalView->EnemyViews[index]->PEnemyProtPixmap->scaled(graphicalView->pixelWidth, graphicalView->pixelWidth, Qt::KeepAspectRatio));
            graphicalView->EnemyViews[index]->protPixmapItem->setPixmap(specificEnemyView2);
        }
        if(dynamic_cast<XEnemy*>(Etje)!=NULL)
        {
            const QPixmap &specificEnemyView(graphicalView->EnemyViews[index]->XEnemyProtPixmap->scaled(graphicalView->pixelWidth, graphicalView->pixelWidth, Qt::KeepAspectRatio));
            graphicalView->EnemyViews[index]->protPixmapItem->setPixmap(specificEnemyView);
        }
    }
}

void Initialization::initConnections() //Connections <3
{
    QObject::connect(model->protje.get(),&Protagonist::posChanged,controller.get() , &Controller::changeProtPosition);
    QObject::connect(controller.get(),&Controller::lost, graphicalView.get(), &GraphicalView::lostScene);
    QObject::connect(model->protje.get(),&Protagonist::posChanged,graphicalView->ProtView.get(), &ProtagonistView::changeProtPosition);
    QObject::connect(model->protje.get(),&Protagonist::healthChanged, graphicalView.get(), &GraphicalView::HealingDoneView);
    QObject::connect(w->ui->horizontalSlider,&QAbstractSlider::valueChanged, model.get(), &Model::setAnimationSpeed);
}
