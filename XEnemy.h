#ifndef __XEnemy_h__
#define __XEnemy_h__
#include "Model.h"

class XEnemy;

class XEnemy: public Enemy
{
    Q_OBJECT
public:
    XEnemy(int xPosition, int yPosition, float strength);
    ~XEnemy() override = default;
    float getSpeedLevel() const;
};

#endif
