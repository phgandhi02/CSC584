#ifndef BOIDS_HPP
#define BOIDS_HPP

#include "./boid.hpp"
#include <iostream>

class BoidsAlgorithm{
    public:
        // BoidsAlgorithm(std::vector<Boid> &boids,float separation, float alignment, float cohesion);
        BoidsAlgorithm() = default;
        ~BoidsAlgorithm() = default;
        void update();
    private:
        // const std::vector<Boid> m_boids;
        float m_separation;
        float m_alignment;
        float m_cohesion;
};

#endif // BOIDS_HPP