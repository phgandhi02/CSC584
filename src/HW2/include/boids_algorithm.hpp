#ifndef BOIDS_HPP
#define BOIDS_HPP

#include "./boid.hpp"
#include <iostream>

class BoidsAlgorithm{
    public:
        BoidsAlgorithm(std::vector<Boid> boids,float separation, float alignment, float cohesion);
        void update();
    private:
        const std::vector<Boid> m_boids;
        const float m_separation;
        const float m_alignment;
        const float m_cohesion;
};

#endif // BOIDS_HPP