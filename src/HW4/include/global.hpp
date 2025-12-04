#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>

const float TIME_STEP = 0.0069444444;

constexpr unsigned int MAP_HEIGHT = 40;
constexpr unsigned int MAP_WIDTH = 40;
constexpr unsigned int CELL_SIZE = 20;

// convert MAP_SKETCH into map
std::array<std::string, MAP_HEIGHT> MAP_SKETCH = {
"########################################",
"#           #                          #",
"#           #                          #",
"#           #                          #",
"#           #                          #",
"#           #                          #",
"#           #                          #",
"#####   ###################   ##########",
"#                  #                   #",
"#                  #                   #",
"#                  #                   #",
"#                  #                   #",
"#                  #                   #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                  #                   #",
"#                  #                   #",
"#                  #                   #",
"#                  #                   #",
"#                  #                   #",
"#                  #                   #",
"########   ###################   #######",
"#                         #            #",
"#                         #            #",
"#                         #            #",
"#                         #            #",
"#                         #            #",
"#                         #            #",
"#                         #            #",
"#                         #            #",
"#                         #            #",
"###################   ##################",
"#                                      #",
"#                                      #",
"#                                      #",
"#########                              #",
"#                                      #",
"#                                      #",
"########################################"};


const auto IDLE_WONDERING_CAT_TEXTURE_RECT = sf::IntRect(sf::Vector2i(198,15),sf::Vector2i(378,500));
const auto PLAYER_CAPTURED_CAT_TEXTURE_RECT = sf::IntRect(sf::Vector2i(206,540),sf::Vector2i(346,496));
const auto LEFT_CHASING_CAT_TEXTURE_RECT = sf::IntRect(sf::Vector2i(1393,447),sf::Vector2i(-605,-400));
const auto LEFT_CHASING_CAT_TEXTURE_ORIGIN = sf::Vector2f(-LEFT_CHASING_CAT_TEXTURE_RECT.size.x/2, LEFT_CHASING_CAT_TEXTURE_RECT.size.y/2 + 250);
const auto RIGHT_CHASING_CAT_TEXTURE_RECT = sf::IntRect(sf::Vector2i(837,575),sf::Vector2i(605,400));
const auto RIGHT_CHASING_CAT_TEXTURE_ORIGIN = sf::Vector2f(RIGHT_CHASING_CAT_TEXTURE_RECT.size.x/2, RIGHT_CHASING_CAT_TEXTURE_RECT.size.y/2 + 150);

const auto RIGHT_PLAYER_TEXTURE_RECT = sf::IntRect(sf::Vector2i(1537,95),sf::Vector2i(319,335));
const auto LEFT_PLAYER_TEXTURE_RECT = sf::IntRect(sf::Vector2i(2617,343),sf::Vector2i(-334,-332));
const auto LEFT_PLAYER_TEXTURE_ORIGIN = sf::Vector2f(-LEFT_PLAYER_TEXTURE_RECT.size.x/2, LEFT_PLAYER_TEXTURE_RECT.size.y/2 + 150);

enum Cell {Empty = ' ', Wall = '#' };

class RandomNumGen
{
public:
    RandomNumGen(int lower_limit, int higher_limit):
        m_gen(), m_distrib(static_cast<int>(lower_limit),static_cast<int>(higher_limit)) {
        // ;  // a seed source for the random number engine
        // std::mt19937 this->m_gen(rd()); // mersenne_twister_engine seeded with rd()
        // std::uniform_int_distribution<> this->m_distrib();
    }
    ~RandomNumGen() = default;
    int getRandomInt() {return m_distrib(m_gen);}
private:
    // Seed the random number generator before using any random numbers in the program.
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_distrib;
};

void draw_map(std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> map, sf::RenderWindow &window)
{
    auto FLOOR_BROWN = sf::Color(210,180,140);
    auto WALL_DARK_BROWN = sf::Color(139,69,19);

    auto cell_shape = sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    for (unsigned int i = 0; i < MAP_HEIGHT; i++)
    {
        for (unsigned int j = 0; j < MAP_WIDTH; j++)
        {
            // indicies are switched because of SFML x-y direction convention
            cell_shape.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i)));

            // map prints sideways so indices are switched.
            switch (map[i][j])
            {
            case Cell::Wall:
                cell_shape.setFillColor(WALL_DARK_BROWN);
                break;

            default:
                cell_shape.setFillColor(FLOOR_BROWN);
                break;
            }
            window.draw(cell_shape);
        }
    }
};

#endif // GLOBAL_HPP