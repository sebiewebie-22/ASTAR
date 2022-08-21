
#include "HealthPackView.h"

//#include "Graphical.h"


void HealthPackView::healthPackTakenView()
{
    const QPixmap &protPixmap(HPTakenProtPixmap->scaled(named_GraphicalView->pixelWidth,named_GraphicalView->pixelWidth, Qt::KeepAspectRatio));
    protPixmapItem->setPixmap(protPixmap);
}
