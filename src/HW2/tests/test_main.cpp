#include <gtest/gtest.h>
#include "boid.hpp"
#include "../include/steering/kinematic_align.hpp"

// Test initialization of a single boid
TEST(BoidTesting, InitializeBoid)
{
    // create a texture object to load the boid image.
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/boid-sm.png"))
    {
        std::cerr << "Asset didn't load properly" << std::endl;
    }; // Load texture

    Boid boid(texture, 250.0f, sf::Vector2f(100.f, 200.f));
    Static character = boid.getCharacter();
    EXPECT_FLOAT_EQ(character.getPosition().x, 100.0f);
    EXPECT_FLOAT_EQ(character.getPosition().y, 200.0f);
    EXPECT_EQ(boid.breadcrumbs_on, true);
};

class BoidTest : public testing::Test
{
protected:
    BoidTest() : texture(createTexture()), boid(texture, 250.0f, sf::Vector2f(0.0f, 0.0f)) {
                 };

    KinematicSteeringOutput steeringOutput;
    const sf::Texture texture;
    Boid boid;
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

private:
    static sf::Texture createTexture()
    {
        sf::Texture texture;
        if (!texture.loadFromFile("../assets/boid-sm.png"))
        {
            std::cerr << "Asset didn't load properly" << std::endl;
        }
        return texture;
    };
};

TEST_F(BoidTest, BoidTextureInitialization)
{
    sf::Texture test_texture;
    if (!test_texture.loadFromFile("../assets/boid-sm.png"))
    {
        std::cerr << "Asset didn't load properly" << std::endl;
    }
    EXPECT_EQ(texture.getSize(), test_texture.getSize());
}

TEST_F(BoidTest, InitializeAlign)
{
    auto align_behavior = std::make_unique<KinematicAlign>();
    boid.m_controller = std::move(align_behavior);
    boid.update(0.01f);
    KinematicSteeringOutput steeringOutput = boid.getSteering();
    auto defaultSteeringOutput = KinematicSteeringOutput();
    bool test = (steeringOutput == defaultSteeringOutput);

    EXPECT_TRUE(test);
}

TEST_F(BoidTest, InitializeArrive)
{
    auto arrive_behavior = std::make_unique<KinematicArrive>();
    arrive_behavior->timeToTarget = 1.0f;
    arrive_behavior->target = Static(sf::Vector2f(100.0f, 100.0f), sf::degrees(0.0f));
    boid.m_controller = std::move(arrive_behavior);
    boid.update(1.f);
    KinematicSteeringOutput steeringOutput = boid.getSteering();
    auto character = boid.getCharacter();

    auto defaultSteeringOutput = KinematicSteeringOutput(sf::Vector2f(100.f, 100.f), sf::degrees(0));
    auto test_character = Static(sf::Vector2f(100,100),sf::radians(-0.785398));
    bool test = (steeringOutput == defaultSteeringOutput 
        && test_character.getPosition() == character.getPosition());
    
    PrintKinematicSteeringOutput();
    PrintCharacterPhysVars();
    EXPECT_TRUE(test);
    EXPECT_FLOAT_EQ(test_character.getOrientationFloat(), character.getOrientationFloat());
}
