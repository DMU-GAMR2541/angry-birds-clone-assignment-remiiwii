#pragma once
#include <vector>
#include <string>

extern std::vector<std::string> destructorLog;  // Creates a string vector to store the triggered destructors, in order, for testing purposes.

class GameObject {
private:

public:
    ~GameObject()
    {
        destructorLog.push_back("GameObject");  // Effectively appends itself onto the destructorLog vector.
    }
};