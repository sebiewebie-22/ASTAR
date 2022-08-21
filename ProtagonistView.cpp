#include "ProtagonistView.h"

ProtagonistView::ProtagonistView()
{

}

void ProtagonistView::saveLatestPosition(int x, int y)
{
    previousX = x;
    previousY = y;
}


void ProtagonistView::changeProtPosition(int posX, int posY)
{
//    int xDifference= posX-previousX;
//    int yDifference= posY-previousY;

    int tempX=posX;
    int tempY=posY;

//    bool itsX=false;
//    bool itsY=false;


//    if(xDifference!=0){
//        itsX=true;
//    }
//    else{
//        itsY=true;
//    }

//    for(int x=0;x<11;x++)
//    {
//        if (itsX==true){
//            if(xDifference>0){
//                posX=posX+x;

//            }
//            else{
//                posX=posX-x;
//            }
//        }

//    }

//    tempX=posX;
//    tempY=posY;
//    for(int y=0;y<11;y++)
//    {
//        if (itsY==true){
//            if(yDifference>0){
//                posY=posY+y;
//            }
//            else{
//                posY=posY-y;
//            }
//        }

//    }
    tempX = (posX*pixelWidth);
    tempY = (posY*pixelWidth);
    protagonist_pixmapItem->setPos(tempX, tempY);
    named_GraphicalView->named_Controller->moveXEnemy();
}
