/*
TODO: add kitchen asset sprites to map
TODO: implement seed eating behavior

TODO: implement decision tree for enemy
*/
// Global Include
#include "./include/global.hpp"

// Repo Lib includes
#include "decision-making/decision_trees.hpp"
#include "movement/boid.hpp" // boid object which handles inputs events and steering behavior
#include "pathfinding/graph.hpp" // graph object for graph representation of world for pathfinding
#include "pathfinding/pathfinding_algos.hpp" // algorithms for pathfinding (Dijkstra's and A*)

// SFML libs
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// STL
#include <iostream>
#include <memory>

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

  void draw_map(std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> map,
              sf::RenderWindow &window) {
  auto FLOOR_BROWN = sf::Color(210, 180, 140);
  auto WALL_DARK_BROWN = sf::Color(139, 69, 19);

  auto cell_shape = sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  for (unsigned int i = 0; i < MAP_HEIGHT; i++) {
    for (unsigned int j = 0; j < MAP_WIDTH; j++) {
      // indicies are switched because of SFML x-y direction convention
      cell_shape.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * j),
                                          static_cast<float>(CELL_SIZE * i)));

      // map prints sideways so indices are switched.
      switch (map[i][j]) {
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


void draw_enemy(Boid &enemy, sf::RenderWindow &window) {
  auto enemy_orientation = enemy.getOrientation();
  // if (enemy_orientation.asDegrees() < 0)
  // {
  //     if (enemy.getTextureRect() == RIGHT_CHASING_CAT_TEXTURE_RECT)
  //     {
  //         enemy.setTextureRect(LEFT_CHASING_CAT_TEXTURE_RECT,LEFT_CHASING_CAT_TEXTURE_ORIGIN);
  //     }
  // } else
  // {
  //     if (enemy.getTextureRect() == LEFT_CHASING_CAT_TEXTURE_RECT)
  //     {
  //         enemy.setTextureRect(RIGHT_CHASING_CAT_TEXTURE_RECT,RIGHT_CHASING_CAT_TEXTURE_ORIGIN);
  //     }
  // }
  enemy.draw(window);
  auto circle = sf::CircleShape(5.0f);
  circle.setFillColor(sf::Color::Blue);
  circle.setPosition(enemy.getPosition());
  window.draw(circle);
}

void draw_player(Boid &player, sf::RenderWindow &window) {
  auto player_orientation = player.getOrientation();
  if (player_orientation.asDegrees() < 0) {
    if (player.getTextureRect() == RIGHT_PLAYER_TEXTURE_RECT) {
      player.setTextureRect(LEFT_PLAYER_TEXTURE_RECT,
                            LEFT_PLAYER_TEXTURE_ORIGIN);
    }
  } else {
    if (player.getTextureRect() == LEFT_PLAYER_TEXTURE_RECT) {
      player.setTextureRect(RIGHT_PLAYER_TEXTURE_RECT);
    }
  }
  player.draw(window);
}

std::vector<Connection> pathfind(Graph graph, sf::Vector2f startPos,
                                 sf::Vector2f goalPos) {
  std::vector<Connection> path;
  // stores the node value for start, current, mouse input, and the next target.
  unsigned int startNode, goalNode; // vars to hold nodes
  sf::Vector2f targetPos;           // stores the position of the next target
  Static target;                    // kinematic data struct of target
  auto pathfinding = Pathfinding();

  startNode = calcNodeIndex(startPos);
  goalNode = calcNodeIndex(goalPos);

  // Check if startNode is the same as the goalNode
  if (startNode == goalNode) {
    return path; // return empty path
  }
  // Make sure goal node is within the map
  if (goalNode >= MAP_WIDTH * MAP_WIDTH + MAP_HEIGHT || goalNode < 0)
    return path; // return empty path
  // Check if goal node is in the graph
  if (static_cast<int>(graph.getNodes(goalNode).size()) <= 1) {
    return path; // return empty path
  }

  EuclidianHeuristic heuristic;
  path = pathfinding.Astar(graph, startNode, goalNode, heuristic);
  return path;
}

/*
set Boid to next target from path if path is not empty
*/
void follow_path(std::vector<Connection> &path, Boid &boid) {
  unsigned int targetNode, currentNode, nextNode, goalNode;
  sf::Vector2f targetPos;
  Static target;

  // Calculate currentNode, mouseNode
  currentNode = calcNodeIndex(boid.getPosition());
  nextNode = path.back().getFromNode();
  targetNode = path.back().getToNode();
  goalNode = path.front().getToNode();

  if (currentNode == nextNode && currentNode != goalNode &&
      targetNode !=
          goalNode) // once boid reaches targetNode then set it to the next node
  {

    targetPos = calcPosfromNode(targetNode);
    target = Static(targetPos, sf::degrees(0.0f));
    boid.setTarget(target);
    path.pop_back();
  } else if (targetNode == goalNode) {
    targetPos = calcPosfromNode(targetNode);
    target = Static(targetPos, sf::degrees(0.0f));
    boid.setTarget(target);
    path.pop_back();
  }
}

int main() {
  /* --------------------------------------------------------------------------
   */
  /*                               Game Loop Setup */
  /* --------------------------------------------------------------------------
   */
  auto rng = RandomNumGen(
      40,
      760); // Create random number generator for getting random seed locations
  auto spriteSheetTextures = sf::Texture("sprite_sheet.png");
  /* ------------------------------- Setup graph ------------------------------
   */
  std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> map =
      convert_sketch_to_map(MAP_SKETCH);
  ;
  Graph graph = Graph();
  std::cout << "Generating a graph!" << std::endl;
  auto edges = GenMapGraph(map);
  for (Connection &edge : edges) {
    graph.addEdge(edge);
  }

  // window creates Window obj. Must include event handling loop to ensure the
  // program doesn't end immediately.
  // * use sf::VideoMode to get desktop resolution for dynamic sizing
  sf::RenderWindow window(sf::VideoMode({800, 800}), "CSC584 HW4");
  window.setFramerateLimit(144); // set the framerate limit to 60 fps.

  int i = 0;
  auto seedTexture = sf::Texture("seeds.png");
  sf::Sprite seed(seedTexture);
  seed.scale(sf::Vector2f(.3f, .3f));
  std::vector<Connection> seedPath;
  auto random_position = sf::Vector2f(rng.getRandomInt(), rng.getRandomInt());

  // Create enemy sprite
  auto enemyStartPos = Static(sf::Vector2f(100, 100), sf::degrees(0));
  auto enemyCatPosition = enemyStartPos.getPosition();
  sf::Vector2f targetPos; // stores the position of the next target
  Static target;
  Boid enemyCat(spriteSheetTextures, enemyStartPos, window);
  enemyCat.setTextureRect(IDLE_WONDERING_CAT_TEXTURE_RECT);
  enemyCat.setSpriteScale(.25, .25);
  enemyCat.mouseInputOn = false;
  auto enemySeekBehavior = std::make_unique<KinematicSeek>();
  enemyCat.controller = std::move(enemySeekBehavior);
  enemyCat.breadcrumbs_on = false;
  std::vector<Connection> enemyPath;

  // Create player sprite
  auto playerStartPos = Static(sf::Vector2f(500, 400), sf::degrees(0));
  auto playerPosition = playerStartPos.getPosition();
  Boid player(spriteSheetTextures, playerStartPos, window);
  player.setTextureRect(RIGHT_PLAYER_TEXTURE_RECT);
  player.setSpriteScale(.15, .15);
  player.mouseInputOn = true;
  auto playerSeekBehavior = std::make_unique<KinematicSeek>();
  player.controller = std::move(playerSeekBehavior);
  player.breadcrumbs_on = false;
  player.speed *= 2;

  float distance;
  /* --------------------------------------------------------------------------
   */
  /*                               Main Game Loop */
  /* --------------------------------------------------------------------------
   */
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    while (const std::optional event = window.pollEvent()) {
      // "close requested" event: we close the window
      if (event->is<sf::Event::Closed>()) {
        // Implement any logic needed before closing game ie. save game etc.
        window.close();

        /* ------------------------- Check for Input Events
         * ------------------------- */
      }
    }

    /* ------------------------- Pathfinding for Enemies
     * ------------------------ */
    /*
    * Trying to implement decision tree here.
    Basic pseudo-code:
    if (distance < 150)
    {
        Enemy speed temporarily increases
        Enemy chases player
    } else
    {
        Enemy wanders map
    }
    */

    enemyCatPosition = enemyCat.getPosition();
    playerPosition = player.getPosition();

    distance = (playerPosition - enemyCatPosition).length();
    if (distance < 150) {
      if (enemyCat.getTextureRect() != PLAYER_CAPTURED_CAT_TEXTURE_RECT) {
        enemyCat.setTextureRect(PLAYER_CAPTURED_CAT_TEXTURE_RECT);
      }

      if (calcNodeIndex(enemyCatPosition) != calcNodeIndex(playerPosition)) {
        enemyPath = std::vector<Connection>{};
      }

      // create a path to goal node or follow an existing path.
      // create a path to the goal node
      if (enemyPath.empty() &&
          graph.getNodes(calcNodeIndex(playerPosition)).size() >= 1) {
        enemyPath = pathfind(graph, enemyCatPosition, playerPosition);
        if (!enemyPath.empty()) {
          target = Static(calcPosfromNode(enemyPath.back().getToNode()),
                          sf::degrees(0.0f));
          enemyCat.setTarget(target);
          enemyPath.pop_back();
        }

      } else // continue following existing path
        follow_path(enemyPath, enemyCat);
    } else {
      if (enemyCat.getTextureRect() != IDLE_WONDERING_CAT_TEXTURE_RECT) {
        enemyPath = std::vector<Connection>{};
        enemyCat.setTextureRect(IDLE_WONDERING_CAT_TEXTURE_RECT);
      }

      // create a path to goal node or follow an existing path.
      // create a path to the goal node
      if (enemyPath.empty()) // Initialize Dijkstra's to plan a path to a known
                             // free cell.
      {
        random_position = sf::Vector2f(rng.getRandomInt(), rng.getRandomInt());
        while (graph.getNodes(calcNodeIndex(random_position)).size() <= 1) {
          random_position =
              sf::Vector2f(rng.getRandomInt(), rng.getRandomInt());
        }
        enemyPath = pathfind(graph, enemyCatPosition, random_position);
        if (!enemyPath.empty()) {
          target = Static(calcPosfromNode(enemyPath.back().getToNode()),
                          sf::degrees(0.0f));
          enemyCat.setTarget(target);
          // enemyPath.pop_back();
        }
      } else // continue following existing path
        follow_path(enemyPath, enemyCat);
    }

    // * Must call clear before drawing anything o.w. content from previous
    // frames will show.
    window.clear(sf::Color::White);

    /* ----------------------------- Update Sprites
     * ----------------------------- */
    enemyCat.update(TIME_STEP);
    player.update(TIME_STEP);

    /* ------------------------------- Draw Window
     * ------------------------------ */
    draw_map(map, window); // draw map
    draw_enemy(enemyCat, window);
    draw_player(player, window);

    i++;
    if ((i % 750) == 0) {
      while (graph.getNodes(calcNodeIndex(random_position)).size() <= 1) {
        random_position = sf::Vector2f(rng.getRandomInt(), rng.getRandomInt());
      }

      seed.setPosition(random_position);
      window.draw(seed);
      i = 0;
    } else {
      window.draw(seed);
    }

    // * must call display end the current frame
    window.display();
  }
}