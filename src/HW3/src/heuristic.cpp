#include "../include/heuristic.hpp"

float EuclidianHeuristic::estimate(int fromNode)
{
    // return (goalNode - fromNode);
    return sf::Vector2f(calculatePositionfromNode(fromNode) - calculatePositionfromNode(goalNode)).length();
}

float EuclidianHeuristic::estimate(int fromNode, int goalNode)
{
    // return (goalNode - fromNode);
    return sf::Vector2f(calculatePositionfromNode(fromNode) - calculatePositionfromNode(goalNode)).length();
}