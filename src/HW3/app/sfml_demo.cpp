#include "../include/global.hpp"
#include "../include/graph.hpp"
#include "../include/pathfinding_algos.hpp"

// Boid libs
#include "../include/movement/boid.hpp"

// SFML libs
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// STL
#include <memory>
#include <iostream>
#include <random>

void boid_movement(Boid &boid, sf::Window &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::I))
    {
        boid.speed *= 1.01f;
        std::cout << "New Speed: " << boid.speed << " | Reset to default with \"K\" key" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::M))
    {
        boid.speed *= 0.99f;
        std::cout << "New Speed: " << boid.speed << " | Reset to default with \"K\" key" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::O))
    {
        boid.smoothing *= 1.01f;
        std::cout << "New Smoothing: " << boid.smoothing << " | Reset to default with \"K\" key" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::U))
    {
        boid.smoothing *= 0.99f;
        std::cout << "New Smoothing: " << boid.smoothing << " | Reset to default with \"K\" key" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::K))
    {
        boid.speed = 100.f;
        boid.smoothing = 0.2f;
        std::cout << "Speed set to default: " << boid.speed << std::endl;
        std::cout << "Smoothing set to default: " << boid.smoothing << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q))
    {
        boid.controller = std::move(std::make_unique<KinematicAlign>());
        std::cout << "Boid Aligning" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
    {
        boid.controller = std::move(std::make_unique<KinematicArrive>(0.5f));
        std::cout << "Boid Arriving" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E))
    {
        boid.controller = std::move(std::make_unique<KinematicFlee>());
        std::cout << "Boid Fleeing" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R))
    {
        boid.controller = std::move(std::make_unique<KinematicSeek>());
        std::cout << "Boid Seeking" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::T))
    {
        boid.controller = std::move(std::make_unique<KinematicWander>());
        std::cout << "Boid Kinematic Wander" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::F))
    {
        boid.controller = std::move(std::make_unique<KinematicFace>());
        std::cout << "Boid Kinematic Face" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
    {
        boid.controller = std::move(std::make_unique<Wander>(window.getSize().x, window.getSize().y));
        std::cout << "Boid Wander" << std::endl;
    }
};

void draw_map(std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> map, sf::RenderWindow &window)
{
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
                cell_shape.setFillColor(sf::Color::Blue);
                break;

            default:
                cell_shape.setFillColor(sf::Color::White);
                break;
            }
            window.draw(cell_shape);
        }
    }
};

std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> generate_scene()
{
    std::array<std::string, MAP_HEIGHT> map_sketch = {
        "######################################  ",
        "##        #        ##        #          ",
        "                  ###### ### # ### ###  ",
        "                   ##                   ",
        "   ## # ##### # ## ## ## # ##### # ##   ",
        "#     #   #   #    ##    #   #   #      ",
        "#   # ### # ### ######## ### # ### ###  ",
        "    # #       # #      # #       # #    ",
        "##### # ##### # ######## # ##### # ### #",
        "        #   #              #   #        ",
        "##### # ##### # ######## # ##### # ### #",
        "    # #       # #      # #       # #    ",
        " #### # ##### # ######## # ##### # ###  ",
        " #        #        ##        #          ",
        " # ## ### # ### ## ## ## ### # ### ##   ",
        " ## #     #     # #### #     #     # #  ",
        " ## # # ##### # # #### # # ##### # # #  ",
        " #    #   #   #    ##    #   #   #      ",
        " # ###### # ###### ## ###### # ######   ",
        " #                 ##                   ",
        " #        #        ##        #          ",
        " #### ### # ### ######## ### # ### ###  ",
        " #                 ##                   ",
        " # ## # ##### # ## ## ## # ##### # ##   ",
        " #    #   #   #    ##    #   #   #      ",
        " #### ### # ### ######## ### # ### ###  ",
        "    # #       # #      # #       # #    ",
        "##### # ##### # ######## # ##### # ### #",
        "        #   #              #   #        ",
        "##### # ##### # ######## # ##### # ### #",
        "    # #       # #      # #       # #    ",
        " #### # ##### # ######## # ##### # ###  ",
        " #        #        ##        #          ",
        " # ## ### # ### ## ## ## ### # ### ##   ",
        " ## #     #     # #### #     #     # #  ",
        " ## # # ##### # # #### # # ##### # # #  ",
        " #    #   #   #    ##    #   #   #      ",
        " # ###### # ###### ## ###### # ######   ",
        " #                 ##                   ",
        " #####################################  "};

    // convert map_sketch into map
    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> map = convert_sketch_to_map(map_sketch);
    return map;
}

int main()
{
    /* ------------------------------- Setup Boid ------------------------------- */

    std::cout << "Program Running!" << std::endl;
    // Seed the random number generator before using random numbers.
    srand(static_cast<unsigned>(time(0)));
    // create window object to render game.
    auto window = sf::RenderWindow(sf::VideoMode({800u, 800u}), "CSC584 HW2: Steering Behaviors");
    // set the framerate limit to 144 fps.
    window.setFramerateLimit(144);
    // create a texture object to load the boid image.
    sf::Texture texture;
    if (!texture.loadFromFile("/home/prem/code/CSC584/src/HW3/assets/boid-sm.png")) // make sure the texture loads correctly.
        return EXIT_FAILURE;

    // Convention for position: origin at the top-left corner. x axis points towards right on screen. y-axis points down on screen.
    Static startPos = Static(sf::Vector2f(2 * CELL_SIZE + CELL_SIZE / 2, 1 * CELL_SIZE + CELL_SIZE / 2), sf::degrees(0.0f));

    Boid boid(texture, startPos, window);
    boid.speed = 50.0f;
    auto seek_behavior = std::make_unique<KinematicSeek>();
    boid.controller = std::move(seek_behavior);
    boid.mouseInputOn = false;
    auto map = generate_scene();

    /* ------------------------------- Setup graph ------------------------------ */
    // Need to make a graph out of the window.
    Graph graph = Graph();
    std::cout << "Generating a graph!" << std::endl;
    auto edges = GenMapGraph(map);
    window.display();

    for (Connection &edge : edges)
    {
        graph.addEdge(edge);
    }

    /* -------------------------- Setup Pathfinding Var ------------------------- */
    auto pathfinding = Pathfinding();
    std::vector<Connection> path;
    // stores the node value for start, current, mouse input, and the next target.
    unsigned int startNode, currentNode, mouseNode, targetNode, goalNode;
    goalNode = 1055;        // known empty cell
    sf::Vector2f targetPos; // stores the position of the next target
    sf::Vector2f goalPos;   // stores the position of the goal
    Static target;
    auto boid_position = boid.getPosition();

    /* -------------------- Input Target Position from Mouse -------------------- */
    auto inputHandler = InputHandler(window); // create input handler object
    Static noTarget = Static();
    Static mouse;

    /* -------------------------------------------------------------------------- */
    /*                                  Game Loop                                 */
    /* -------------------------------------------------------------------------- */
    while (window.isOpen())
    {
        window.clear(sf::Color::White); // clear the window with a white background.
        mouse = inputHandler.update();  // holds the position data for mouse

        while (const std::optional event = window.pollEvent()) // event polling loop.
        {
            if (event->is<sf::Event::Closed>()) // If user closes the window, close the application.
            {
                window.close();
            }

            boid_movement(boid, window); // change boid movement algorithm based on keyboard input
        }
        boid_position = boid.getPosition(); // store boid position

        draw_map(map, window); // draw map

        if (!mouse.operator==(noTarget))
        {
            boid_position = boid.getPosition();
            path = std::vector<Connection>{};
            goalPos = mouse.getPosition();
            goalNode = calculateNodeIndex(goalPos);
            goalNode = (goalNode < MAP_WIDTH * MAP_WIDTH + MAP_HEIGHT) ? goalNode : 1055;
        }

        if (path.empty()) // Initialize Dijkstra's to plan a path to a known free cell.
        {
            if (currentNode != goalNode)
            {
                /* ------------------------ Run Dijkstra's Algorithm ------------------------ */
                boid_position = boid.getPosition();
                startNode = calculateNodeIndex(boid_position);
                currentNode = startNode;
                goalPos = calculatePositionfromNode(goalNode);
                path = pathfinding.DijkstraAlgorithm(graph, startNode, goalNode);
                /* ------------------- Set the first waypoint for the boid ------------------ */
                if (!path.empty())
                {
                    targetNode = path.back().getToNode();
                    targetPos = calculatePositionfromNode(targetNode);
                    target = Static(targetPos, sf::degrees(0.0f));
                    boid.setTarget(target);
                    path.pop_back();
                }
            }
        }
        else // continue following existing path
        {
            // Calculate currentNode, mouseNode
            currentNode = calculateNodeIndex(boid_position);

            if (currentNode == targetNode && currentNode != goalNode && targetNode != goalNode) // once boid reaches targetNode then set it to the next node
            {
                targetNode = path.back().getToNode();
                targetPos = calculatePositionfromNode(targetNode);
                target = Static(targetPos, sf::degrees(0.0f));
                boid.setTarget(target);
                path.pop_back();
            }
            else if (targetNode == goalNode)
            {
                targetPos = calculatePositionfromNode(targetNode);
                target = Static(targetPos, sf::degrees(0.0f));
                boid.setTarget(target);
            }
        }
        // std::cout << std::endl;
        // std::cout << "Boid: " << boid_position.x << " | " << boid_position.y << " | " << currentNode << std::endl;
        // std::cout << "Mouse: " << mouse.getPosition().x << " | " << mouse.getPosition().y << " | " << mouseNode << std::endl;
        // std::cout << "Target: " << targetPos.x << " | " << targetPos.y << " | " << targetNode << std::endl;

        // update the boid position.
        boid.update(0.01f);
        boid.draw(window);

        // display the new frame.
        window.display();
    }
}
