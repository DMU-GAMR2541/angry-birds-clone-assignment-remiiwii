#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "DynamicObject.h"
#include "Pig.h"
#include <vector>
#include <memory>

class PigMemoryPool {
private:
    struct PoolEntry {
        std::unique_ptr<Pig> pig;
        bool b_active = false;
    };

    std::vector<PoolEntry> pool;
    PoolEntry entry;

public:
    const std::vector<PoolEntry>& getPool() const {
        return pool;
    }

    PigMemoryPool(size_t maxPigs) {     // Creation of memory pool that takes a maximum amount of pigs as an inout.
        for (size_t i = 0; i < maxPigs; i++) {      // Looped for each pig defined by the value inputted into the function.
            pool.reserve(maxPigs);      // Immediately reserves a custom amount of "pig" objects in memory.
            pool.push_back(std::move(entry));   // Pushes created pig into the memory pool.
        }
    }

    Pig* acquire(float x, float y) {
        for (auto& entry : pool) {
            if (!entry.b_active) {  // Finds inactive part of memory pool for use.
                entry.pig = std::make_unique<Pig>("../assets/pig.png", x, y);   // Creates of a unique pig based on inputted x and y values.
                entry.b_active = true;  // Marks reserved memory as active, as an on-screen pig object now uses it.
                return entry.pig.get();     // Returns the pig.
            }
        }
        return nullptr;
    }

    void release(Pig* pig) {    // Function to release the pig object once it is no longer needed.
        for (auto& entry : pool) {
            if (entry.pig.get() == pig) {
                entry.b_active = false;     // Marks memory as inactive to release the pig.
                return;
            }
        }
    }
};