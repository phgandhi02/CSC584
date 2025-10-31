#include "../include/heuristic.hpp"

float EuclidianHeuristic::estimate(int fromNode)
{
    return (goalNode - fromNode);
}

float EuclidianHeuristic::estimate(int fromNode, int goalNode)
{
    return (goalNode - fromNode);
}