
#ifndef __EnemyViewText_h__
#define __EnemyViewText_h__

// #include "TextBased.h"
#include <memory>

class TextView;
class EnemyViewText;

class EnemyViewText
{
	public: TextView* _unnamed_TextBased_;
    std::shared_ptr<TextView> named_TextBased;
};

#endif
