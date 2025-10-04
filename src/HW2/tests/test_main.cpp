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

    EXPECT_FLOAT_EQ(boid.getPosition().x, 100.0f);
    EXPECT_FLOAT_EQ(boid.getPosition().y, 200.0f);
    EXPECT_EQ(boid.breadcrumbs_on, true);
};

// Test initialization of a single boid with Align behavior
TEST(BoidTesting, InitializeBoidAlign)
{
    // create a texture object to load the boid image.
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/boid-sm.png"))
    {
        std::cerr << "Asset didn't load properly" << std::endl;
    }; // Load texture

    Boid boid(texture, 250.0f, sf::Vector2f(0.0f, 0.0f));

    auto align_behavior = std::make_unique<KinematicAlign>();
    auto steeringOutput = boid.align(std::move(align_behavior));
    auto defaultSteeringOutput = KinematicSteeringOutput();
    bool test = steeringOutput.operator==(defaultSteeringOutput);

    EXPECT_TRUE(test);
};

class BoidTest : public testing::Test
{
protected:
    BoidTest() : texture(createTexture()), boid(texture, 250.0f, sf::Vector2f(100.f, 200.f))
    {
    };

    KinematicSteeringOutput steeringOutput;
    const sf::Texture texture;
    Boid boid;

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
    steeringOutput = boid.align(std::move(align_behavior));
    auto defaultSteeringOutput = KinematicSteeringOutput();
    bool test = steeringOutput.operator==(defaultSteeringOutput);

    EXPECT_TRUE(test);
}