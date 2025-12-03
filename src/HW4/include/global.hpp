#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <random>

constexpr unsigned int MAP_HEIGHT = 40;
constexpr unsigned int MAP_WIDTH = 40;
constexpr unsigned int CELL_SIZE = 20;

enum Cell {Empty = ' ', Wall = '#' };

class RandomNumGen
{
public:
    RandomNumGen(float lower_limit, float higher_limit) {
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 m_gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> m_distrib(static_cast<int>(lower_limit),static_cast<int>(higher_limit));
    }
    ~RandomNumGen() = default;
    int getRandomInt() {return m_distrib(m_gen);}
private:
    // Seed the random number generator before using any random numbers in the program.
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_distrib;
};

#endif // GLOBAL_HPP