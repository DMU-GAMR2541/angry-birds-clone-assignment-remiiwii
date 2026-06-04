#pragma once
#include <vector>
#include <string>

extern std::vector<std::string> destructorLog;

class GameObject {
private:

public:
    ~GameObject()
    {
        destructorLog.push_back("GameObject");
    }
};