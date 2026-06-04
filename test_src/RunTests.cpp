#include <gtest/gtest.h>
#include "Enemy.h"
#include "Slingshot.h"
#include "Pig.h"
#include "Bird.h"
#include "DynamicObject.h"
#include "GameObject.h"

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
        testpig = std::make_unique<Pig> ("../assets/pig.png", 250.0f, 200.0f);
    }
};
TEST_F(PigTest, pigSpriteRenderTest) {     // Simple test to check if the pig sprite has correctly rendered using the boolean b_spriteRendered.
    ASSERT_TRUE(testpig->checkSpriteRendered());    // Function returns the boolean value, unit test asserts that the value will be true.
}
TEST_F(PigTest, pigPositionTests) {     // Fatal expect test to see if the pig has been correctly placed on the right of the bird.
    EXPECT_LE(testpig->getSpriteCoordinates().x, 150.0f);
    EXPECT_LE(testpig->getSpriteCoordinates().y, 150.0f);    // Expects the pig to be placed less than or equal to a value too low to be correct placement, and fails the test if it is placed in the correct position.
}


class BirdTest : public testing::Test {
public:
    std::unique_ptr<Bird> bird;
    std::unique_ptr<Pig> pig1;
    std::unique_ptr<Pig> pig2;
    std::unique_ptr<Pig> pig3;      // Three pigs are needed for a positional relations test.
protected:
    void SetUp() override {
        bird = std::make_unique<Bird>("../assets/bird.png", 50.0f, 50.0f);      // The bird is placed to the left of the window.
        pig1 = std::make_unique<Pig>("../assets/pig.png", 250.0f, 200.0f);      
        pig2 = std::make_unique<Pig>("../assets/pig.png", 300.0f, 200.0f);
        pig3 = std::make_unique<Pig>("../assets/pig.png", 350.0f, 200.0f);      // And the pigs, similarly, to the right of the window, similar to how they would be set up in-game.
    }   
};

TEST_F(BirdTest, birdSpriteRenderTest) {
    ASSERT_TRUE(bird->checkSpriteRendered());   // Bird sprite rendering test, with the same functionality as pigSpriteRenderTest.
}
TEST_F(BirdTest, birdPositionTest) {
    EXPECT_EQ(bird->getSpriteCoordinates().x, 50.0f);
    EXPECT_EQ(bird->getSpriteCoordinates().y, 50.0f);   // Expects the bird to be in the same position, unlike the pigPositionTest.
}
TEST_F(BirdTest, positionRelationTests) {   // Used to ensure the bird sprite is placed to the left of three different pig sprites.   
    ASSERT_LE(bird->getSpriteCoordinates().x, pig1->getSpriteCoordinates().x);
    ASSERT_LE(bird->getSpriteCoordinates().y, pig1->getSpriteCoordinates().y);
    // ^^ Asserts that the bird's X and Y co-ordinates are less than the first pig's, placing the bird object to the left of the pig. As this is an assert, failing this will stop the rest of the test for efficiency.
    ASSERT_LE(bird->getSpriteCoordinates().x, pig2->getSpriteCoordinates().x);
    ASSERT_LE(bird->getSpriteCoordinates().y, pig2->getSpriteCoordinates().y);
    // ^^ Repeats, for the second pig. Also asserts less-than, so the third pig's test will be cancelled if the second pig is placed incorrectly in relation to the bird (or vice-verca).
    ASSERT_LE(bird->getSpriteCoordinates().x, pig3->getSpriteCoordinates().x);
    ASSERT_LE(bird->getSpriteCoordinates().y, pig3->getSpriteCoordinates().y);
    // ^^ The third and final pig is tested with the same method.
}
TEST_F(BirdTest, birdMovementTest) {
    bird->moveSpriteBy(100.0f, 100.0f);     // Using SFML's move function, takes two float values and moves the bird object by that given amount. In this case, 100.0f. 
    EXPECT_GE(bird->getSpriteCoordinates().x, 150.0f);
    EXPECT_GE(bird->getSpriteCoordinates().y, 150.0f);  // Expects the bird object to have moved by at least 100.0f in both X and Y directions.
}

std::vector<std::string> destructorLog;

TEST(Bird, destructorSequence) {
    destructorLog.clear();  // Clears the created destructorLog vector in anticipation of the destructor sequence test.

    {
        Bird bird("../assets/bird.png", 50.0f, 50.0f);  // Creates a bird object purely to trigger its destructor.
    }

    EXPECT_EQ(destructorLog[0], "Bird");
    EXPECT_EQ(destructorLog[1], "DynamicObject");
    EXPECT_EQ(destructorLog[2], "GameObject");  // Destructors trigger from the bottom of the inheritence "ladder," starting with Bird, moving to DynamicObject, and finally GameObject.
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