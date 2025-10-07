#include <gtest/gtest.h>
#include "boid.hpp"
#include "../include/steering/kinematic_align.hpp"

// Test initialization of a single boid
TEST(BoidTesting, InitializeBoid)
{
    // create a texture object to load the boid image.
    sf::Texture texture;
    if (!texture.loadFromFile("/home/prem/code/CSC584/src/HW2/assets/boid-sm.png"))
    {
        std::cerr << "Asset didn't load properly" << std::endl;
    }; // Load texture
    auto window = sf::RenderWindow(sf::VideoMode({800, 600}), "CSC584 HW2: Steering Behaviors");
    Static startPos = Static(sf::Vector2f(100, 100), sf::degrees(0.0f));

    Boid boid(texture, startPos, window);
    Static character = boid.getCharacter();
    EXPECT_FLOAT_EQ(character.getPosition().x, 100.0f);
    EXPECT_FLOAT_EQ(character.getPosition().y, 100.0f);
    EXPECT_EQ(boid.breadcrumbs_on, true);
};

class BoidTest : public testing::Test
{
protected:
    BoidTest() : texture(createTexture()), window(createWindow(800, 600)), boid(texture, Static(sf::Vector2f(400, 300), sf::degrees(0.0f)), window) {};

    KinematicSteeringOutput steeringOutput;
    const sf::Texture texture;
    Boid boid;
    sf::RenderWindow window;
    void PrintKinematicSteeringOutput()
    {
        KinematicSteeringOutput kinematicSteeringOutput = boid.getSteering();
        std::cout << "Velocity: " << kinematicSteeringOutput.getVelocity().x << ","
                  << kinematicSteeringOutput.getVelocity().y << " | Rotation: "
                  << kinematicSteeringOutput.getRotationFloat() << std::endl;
    }
    void PrintCharacterPhysVars()
    {
        Static character = boid.getCharacter();
        std::cout << "Position: " << character.getPosition().x << ","
                  << character.getPosition().y << " | Orientation: "
                  << character.getOrientationFloat() << std::endl;
    }
    void Expect_EQ_Static(Static test_character)
    {
        EXPECT_EQ_Position(test_character);
        EXPECT_EQ_Orientation(test_character);
    }
    void EXPECT_EQ_SteeringOutput(KinematicSteeringOutput testSteering)
    {
        EXPECT_EQ_Velocity(testSteering);
        EXPECT_EQ_Rotation(testSteering);
    }
    void EXPECT_EQ_Position(Static test_character)
    {
        PrintCharacterPhysVars();
        auto position = boid.getCharacter().getPosition();
        EXPECT_FLOAT_EQ(position.x, test_character.getPosition().x);
        EXPECT_FLOAT_EQ(position.y, test_character.getPosition().y);
    }
    void EXPECT_EQ_Orientation(Static test_character)
    {
        PrintCharacterPhysVars();
        auto orientation = boid.getCharacter().getOrientationFloat();
        EXPECT_FLOAT_EQ(orientation, test_character.getOrientationFloat());
    }
    void EXPECT_EQ_Velocity(KinematicSteeringOutput testSteering)
    {
        PrintKinematicSteeringOutput();
        auto velocity = boid.getSteering().getVelocity();
        EXPECT_FLOAT_EQ(velocity.x, testSteering.getVelocity().x);
        EXPECT_FLOAT_EQ(velocity.y, testSteering.getVelocity().y);
    }
    void EXPECT_EQ_Rotation(KinematicSteeringOutput testSteering)
    {
        PrintKinematicSteeringOutput();
        auto rotation = boid.getSteering().getRotationFloat();
        EXPECT_FLOAT_EQ(rotation, testSteering.getRotationFloat());
    }

private:
    static sf::Texture createTexture()
    {
        sf::Texture texture;
        if (!texture.loadFromFile("/home/prem/code/CSC584/src/HW2/assets/boid-sm.png"))
        {
            std::cerr << "Asset didn't load properly" << std::endl;
        }
        return texture;
    };
    static sf::RenderWindow createWindow(unsigned int windowSizeX, unsigned int windowSizeY)
    {
        auto window = sf::RenderWindow(sf::VideoMode({windowSizeX, windowSizeY}), "CSC584 HW2: Steering Behaviors");
        return window;
    };
};

TEST_F(BoidTest, BoidTextureInitialization)
{
    sf::Texture test_texture;
    if (!test_texture.loadFromFile("/home/prem/code/CSC584/src/HW2/assets/boid-sm.png"))
    {
        std::cerr << "Asset didn't load properly" << std::endl;
    }
    EXPECT_EQ(texture.getSize(), test_texture.getSize());
}

TEST_F(BoidTest, InitializeAlign)
{
    auto align_behavior = std::make_unique<KinematicAlign>();
    boid.controller = std::move(align_behavior);
    boid.update(0.01f);
    KinematicSteeringOutput steeringOutput = boid.getSteering();
    auto defaultSteeringOutput = KinematicSteeringOutput();
    bool test = (steeringOutput == defaultSteeringOutput);

    EXPECT_TRUE(test);
}

TEST_F(BoidTest, AlignUp)
{
    auto align_behavior = std::make_unique<KinematicAlign>();
    boid.controller = std::move(align_behavior);
    boid.update(0.01f);
    KinematicSteeringOutput steeringOutput = boid.getSteering();
    auto defaultSteeringOutput = KinematicSteeringOutput();
    bool test = (steeringOutput == defaultSteeringOutput);

    EXPECT_TRUE(test);
}