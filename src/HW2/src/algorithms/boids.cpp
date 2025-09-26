#include "../../include/algorithms/boids.hpp"

BoidsAlgorithm::BoidsAlgorithm(
    std::vector<std::unique_ptr<Boid>>& boids,
    double separation, 
    double alignment, 
    double cohesion
)
        : m_boids(boids), m_separation(separation), m_alignment(alignment), m_cohesion(cohesion){
    
};

// Implement update() method
void BoidsAlgorithm::update() {
    // Your update logic here
}