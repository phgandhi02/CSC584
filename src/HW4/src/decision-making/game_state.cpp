#include "../../include/decision-making/game_state.hpp"

#include "../../include/global.hpp"
#include "../../include/pathfinding/pathfinding_algos.hpp"
#include "../../include/pathfinding/heuristic.hpp"

std::vector<Connection> GameState::getPath(sf::Vector2f startPos, sf::Vector2f goalPos)
{
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
  if (static_cast<int>(m_graph.getNodes(goalNode).size()) <= 1) {
    return path; // return empty path
  }

  EuclidianHeuristic heuristic;
  path = pathfinding.Astar(m_graph, startNode, goalNode, heuristic);
  return path;
};

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