#ifndef BOIDS_HPP
#define BOIDS_HPP

#include "../boid.hpp"
#include <iostream>

class BoidsAlgorithm{
    public:
        BoidsAlgorithm(std::vector<std::unique_ptr<Boid>>& boids,double separation, double alignment, double cohesion);
        std::vector<std::unique_ptr<Boid>> boids;
        void update();
    private:
        const std::vector<std::unique_ptr<Boid>>& m_boids;
        const double m_separation;
        const double m_alignment;
        const double m_cohesion;
};

#endif // BOIDS_HPP