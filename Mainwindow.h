#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "world.h"
#include "GraphicalView.h"
#include "TextView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Controller;
class ProtagonistView;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    std::shared_ptr<Controller> named_Controller;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene * getScenePtr(){return scene;}

    //Viewer settings
    std::shared_ptr<View> currentViewMode;
    std::shared_ptr<GraphicalView> gView;
    std::shared_ptr<TextView> tView;

    //Functions
    void setGraphicalView(std::shared_ptr<GraphicalView> newGraphView){gView = newGraphView;}
    void setTextView(std::shared_ptr<TextView> newTextView){tView = newTextView;}
    void setCurrentViewMode(std::shared_ptr<View> newCurrentViewMode){currentViewMode = newCurrentViewMode;}
    std::shared_ptr<View> getCurrentViewMode(){return currentViewMode;}

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    void keyPressEvent(QKeyEvent*event) override;

};
#endif // MAINWINDOW_H
