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

public:
    PigMemoryPool(size_t maxPigs) {
        pool.reserve(maxPigs);
        for (size_t i = 0; i < maxPigs; i++) {
            PoolEntry entry;
            entry.pig = std::make_unique<Pig>("../assets/pig.png", -1000.0f, -1000.0f);
            pool.push_back(std::move(entry));
        }
    }

    Pig* acquire(float x, float y) {
        for (auto& entry : pool) {
            if (!entry.b_active) {
                entry.pig = std::make_unique<Pig>("../assets/pig.png", x, y);
                entry.b_active = true;
                return entry.pig.get();
            }
        }
        return nullptr;
    }

    void release(Pig* pig) {
        for (auto& entry : pool) {
            if (entry.pig.get() == pig) {
                entry.b_active = false;
                return;
            }
        }
    }

    const std::vector<PoolEntry>& getPool() const {
        return pool;
    }
};