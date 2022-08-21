
#ifndef __TileViewText_h__
#define __TileViewText_h__

// #include "TextBased.h"
#include <memory>

class TextView;
class HealthPackViewText;

class HealthPackViewText
{
	public: TextView* _unnamed_TextBased_;
    std::shared_ptr<TextView> named_TextBased;
};

#endif
