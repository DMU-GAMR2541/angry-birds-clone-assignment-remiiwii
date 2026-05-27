#include <gtest/gtest.h>
#include "Enemy.h"
#include "Slingshot.h"
#include "Pig.h"
#include "Bird.h"

/// <summary>
///Taken from the GoogleTest primer. 
/// </summary>

// The fixture for testing class Foo.
class EnemyTest : public testing::Test {
public:
    std::unique_ptr<Enemy> enemy;
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    EnemyTest() {
        // You can do set-up work for each test here.
                    
    }

    ~EnemyTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        enemy = std::make_unique<Enemy>(50); // All enemnies in this test suite start with 50 HP.
                    
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }


};

// Fixture for testing the Slingshot function
class SlingshotTest : public testing::Test {
public:
    std::unique_ptr<Slingshot> slingshot;
protected:
    void SetUp() override {
        slingshot = std::make_unique<Slingshot>();
    }
};


class PigTest : public testing::Test {
public:
    std::unique_ptr<Pig> testpig;
protected:
    void SetUp() override {
        testpig = std::make_unique<Pig> ("../assets/pig.png", 100.0f, 100.0f);
    }
};
TEST_F(PigTest, SpriteRenderTest) {
    ASSERT_TRUE(testpig->checkSpriteRendered());
}
TEST_F(PigTest, pigPositionTests) {
    EXPECT_EQ(testpig->getXPosition(), 100.0f);
    EXPECT_EQ(testpig->getYPosition(), 100.0f);
}


class BirdTest : public testing::Test {
public:
    std::unique_ptr<Bird> bird;
    std::unique_ptr<Pig> pig1;
    std::unique_ptr<Pig> pig2;
    std::unique_ptr<Pig> pig3;
protected:
    void SetUp() override {
        bird = std::make_unique<Bird>("../assets/bird.png", 50.0f, 50.0f);
        pig1 = std::make_unique<Pig>("../assets/pig.png", 250.0f, 200.0f);
        pig2 = std::make_unique<Pig>("../assets/pig.png", 300.0f, 200.0f);
        pig3 = std::make_unique<Pig>("../assets/pig.png", 350.0f, 200.0f);
    }
};
TEST_F(BirdTest, birdPositionTests) {
    EXPECT_EQ(bird->getXPosition(), 50.0f);
    EXPECT_EQ(bird->getYPosition(), 50.0f);
}
TEST_F(BirdTest, comparisonTests) {
    ASSERT_LE(bird->getXPosition(), bird->getYPosition(), pig1->getXPosition(), pig1->getYPosition());
    ASSERT_LE(bird->getXPosition(), bird->getYPosition(), pig2->getXPosition(), pig2->getYPosition());
    ASSERT_LE(bird->getXPosition(), bird->getYPosition(), pig3->getXPosition(), pig3->getYPosition());
}


//A single test, not a fixture. No setup is called.
TEST(Enemy, First_test) {
    Enemy e(100);
    EXPECT_GT(e.getHealth(), 100);
}

TEST_F(EnemyTest, LethalDamagePopsPig) {
    enemy->takeDamage(60);
    EXPECT_TRUE(enemy->checkIfPopped());
}

TEST_F(EnemyTest, ActualLethalKillsPig) {
    enemy->takeDamage(100);
    EXPECT_TRUE(enemy->checkIfPopped());
}

TEST_F(SlingshotTest, PullbackTension) {
    slingshot->pullBack(30);
    EXPECT_EQ(slingshot->getTension(), 30);

    slingshot->pullBack(80);
    EXPECT_EQ(slingshot->getTension(), 100);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}