#include "../include/boids_colony.hpp"
#include "../include/steering/kinematic_align.hpp"
#include "../include/steering/kinematic_seek.hpp"
#include "../include/steering/kinematic_flee.hpp"
#include "../include/steering/kinematic_arrive.hpp"
#include "../include/delegated_steering/wander.hpp"

#include <random>

float sampleDifference(float leftBound, float rightBound)
{
    srand(static_cast<unsigned>(time(0)));
    static std::default_random_engine rand_gen;
    std::uniform_real_distribution<> dis(leftBound, rightBound);
    float randomValue = dis(rand_gen);
    return randomValue;
};

BoidsColony::BoidsColony(const sf::Texture &texture, sf::RenderWindow &window,
                         float separation, float cohesion, float alignment, int boidCount)
    : separation(separation), cohesion(cohesion), alignment(alignment), m_inputHandler(window),
    m_boidCount(boidCount)
{
    
    for (int i = 0; i < boidCount; i++)
    {
        auto windowSizeX = (float)window.getSize().x;
        auto windowSizeY = (float)window.getSize().y;

        auto startPos = sf::Vector2f(sampleDifference(0, windowSizeX), sampleDifference(0, windowSizeY));
        auto startOrient = sf::degrees(sampleDifference(0, 360));

        Static startChar = Static(startPos, startOrient);
        boids.emplace_back(texture, startChar, window);
        boids[i].speed = 200;
        boids[i].breadcrumbs.delay = 100;
        boids[i].breadcrumbs.decay = 150;
        // std::cout << startPos.x << " | " << startPos.y << std::endl;
    }
};

void BoidsColony::setSteering(Boid &self)
{
    auto separationFlee = KinematicAlign();
    auto cohesionSeek = KinematicSeek();
    auto alignArrive = KinematicArrive(1.0f);

    auto separationForce = sf::Vector2f();
    auto cohesionForce = sf::Vector2f();
    auto alignmentForce = sf::Vector2f();

    for (Boid &boid : boids)
    {
        const auto fleeDirection = self.getCharacter().getPosition() - boid.getCharacter().getPosition();
        const auto fleeDistance = fleeDirection.length();
        if (separationRadius > fleeDistance && fleeDistance > 0.0f)
        {
            auto fleeVector = fleeDirection / fleeDistance;
            separationForce += fleeVector;
        }

        const auto cohesionDirection = boid.getCharacter().getPosition() - self.getCharacter().getPosition();
        const auto cohesionDistance = cohesionDirection.length();
        if (cohesionRadius > cohesionDistance && cohesionDistance > 0.0f)
        {
            auto cohesionVector = cohesionDirection / cohesionDistance;
            cohesionForce += cohesionVector;
        }

        const auto alignmentDirection = boid.getSteering().getVelocity() - self.getSteering().getVelocity();
        const auto alignmentDistance = alignmentDirection.length();
        if (alignmentRadius > alignmentDistance && alignmentDistance > 0.0f)
        {
            alignmentForce += boid.getSteering().getVelocity();
        }
    }

    alignmentForce /= (float) m_boidCount;
    separationFlee.target = Static(sf::Vector2f(self.getCharacter().getPosition() + separationForce), self.getCharacter().getOrientation());
    cohesionSeek.target = Static(sf::Vector2f(self.getCharacter().getPosition() + cohesionForce), self.getCharacter().getOrientation());
    alignArrive.target = Static(sf::Vector2f(self.getCharacter().getPosition() + alignmentForce), self.getCharacter().getOrientation());

    // auto character = self.getCharacter();
    // auto separationOutput = separationFlee.getSteering(character);
    // auto cohesionOutput = cohesionSeek.getSteering(character);
    // auto alignmentOutput = alignArrive.getSteering(character);

    auto boidSteering = KinematicSeek();
    boidSteering.target = Static(self.getCharacter().getPosition() + separation * separationForce + cohesion * cohesionForce + alignment * alignmentForce, self.getCharacter().getOrientation());

    if (separationForce + cohesionForce + alignmentForce == sf::Vector2f())
    {
        self.controller = std::move(std::make_unique<Wander>(m_windowSizeX, m_windowSizeY));
        std::cout << "Boid wandering" << std::endl;
    }
    else
    {
        self.controller = std::move(std::make_unique<KinematicSeek>(boidSteering));
    }
};

// Implement update() method
void BoidsColony::update()
{
    // Your update logic here
    for (Boid &boid : boids)
    {
        setSteering(boid);
        if (mouseInputOn)
        {
            // Assign target from mouse click using input handler object.
            auto target = m_inputHandler.update(); // update will return a Static object with null_output false;
            // set the target for the controller equal to the target from the input handler (ie. mouse)
            if (target.null_output == false){
                boid.controller = std::move(std::make_unique<KinematicSeek>());
                boid.controller->target = target;
                // std::cout << target.getPosition().x << " | " << target.getPosition().y << std::endl;
            }
            
        }
        boid.update(0.01f);
    }
}

void BoidsColony::draw(sf::RenderWindow &window)
{
    m_windowSizeX = window.getSize().x;
    m_windowSizeY = window.getSize().y;
    // Your update logic here
    for (Boid &boid : boids)
    {
        boid.draw(window);
    }
}