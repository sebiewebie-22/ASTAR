#include "XEnemy.h"


XEnemy::XEnemy(int xPosition, int yPosition, float strength) : Enemy(xPosition, yPosition, strength)
{
setXPos(xPosition);
setYPos(yPosition);
setValue(strength);
}
