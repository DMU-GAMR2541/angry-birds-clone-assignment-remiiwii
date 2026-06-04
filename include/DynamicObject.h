#pragma once
#include <iostream>
#include "GameObject.h"

class DynamicObject : public virtual GameObject {
private:

public:
    ~DynamicObject()
    {
        destructorLog.push_back("DynamicObject");
    }
};