#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "graph.hpp"
#include "heuristic.hpp"

class NodeRecord
{
};

class Pathfinding
{
    Pathfinding() = default;
    ~Pathfinding() = default;
    std::vector<int> DijkstraAlgorithm(Graph graph, int start, int end);
    std::vector<int> Astar(Graph graph, int start, int end, Heuristic heuristic);
};

#endif