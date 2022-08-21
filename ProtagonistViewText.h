
#ifndef __ProtagonistViewText_h__
#define __ProtagonistViewText_h__

// #include "TextBased.h"
#include <memory>

class TextView;
class ProtagonistViewText;

class ProtagonistViewText
{
    public:
    std::shared_ptr<TextView> named_TextBased;
};

#endif
