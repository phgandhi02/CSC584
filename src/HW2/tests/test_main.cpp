#include <gtest/gtest.h>
#include "boid.hpp"
#include "../include/steering/kinematic_align.hpp"

// Test initialization of a single boid
TEST(BoidTest, InitializeBoid) {
   // create a texture object to load the boid image.
    sf::Texture texture; 
    if(!texture.loadFromFile("../assets/boid-sm.png")){
        std::cerr << "Asset didn't load properly" << std::endl;
    }; // Load texture

    Boid boid(texture, 250.0f, sf::Vector2f(100.f, 200.f));

    EXPECT_FLOAT_EQ(boid.getPosition().x, 100.0f);
    EXPECT_FLOAT_EQ(boid.getPosition().y, 200.0f);
    EXPECT_EQ(boid.breadcrumbs_on, true);
};

// Test initialization of a single boid with Align behavior
TEST(BoidTest, InitializeBoidAlign) {
   // create a texture object to load the boid image.
    sf::Texture texture; 
    if(!texture.loadFromFile("../assets/boid-sm.png")){
        std::cerr << "Asset didn't load properly" << std::endl;
    }; // Load texture

    Boid boid(texture, 250.0f, sf::Vector2f(0.0f, 0.0f));

    auto align_behavior = std::make_unique<KinematicAlign>();
    auto steeringOutput = boid.align(std::move(align_behavior));
    auto defaultSteeringOutput = KinematicSteeringOutput();
    bool test = steeringOutput.operator==(defaultSteeringOutput);

    EXPECT_TRUE(test);
};