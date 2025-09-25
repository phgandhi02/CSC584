#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include "./utils/breadcrumbs.hpp"

class Boid {
    public:
        Boid();
        void update();
        void draw(sf::RenderWindow& window);
        bool breadcrumbs_on;
    private:
        std::optional<Breadcrumbs> breadcrumbs;
};

#endif // BOID_HPP