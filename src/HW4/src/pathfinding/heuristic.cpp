#include "../../include/pathfinding/heuristic.hpp"

float EuclidianHeuristic::estimate(int fromNode)
{
    // return (goalNode - fromNode);
    return sf::Vector2f(calcPosfromNode(fromNode) - calcPosfromNode(goalNode)).length();
}

float EuclidianHeuristic::estimate(int fromNode, int goalNode)
{
    // return (goalNode - fromNode);
    return sf::Vector2f(calcPosfromNode(fromNode) - calcPosfromNode(goalNode)).length();
}

float ManhattanHeuristic::estimate(int fromNode)
{
    const float D = 1.0f;
    const auto distance = sf::Vector2f(calcPosfromNode(fromNode) - calcPosfromNode(goalNode));
    return D * (distance.x + distance.y);
}

float ManhattanHeuristic::estimate(int fromNode, int goalNode)
{
    return sf::Vector2f(calcPosfromNode(fromNode) - calcPosfromNode(goalNode)).length();
}