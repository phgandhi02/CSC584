#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "graph.hpp"
#include "heuristic.hpp"

#include <algorithm>

class PathfindingList
{
public:
    NodeRecord smallestElement();
    bool contains(int node);
    NodeRecord find(int node);
    void add(NodeRecord newRecord);
    void subtract(NodeRecord newRecord);
    int size() { return nodeRecords.size(); }

private:
    std::vector<NodeRecord> nodeRecords;
};

class Pathfinding
{
    Pathfinding() = default;
    ~Pathfinding() = default;
    std::vector<Connection> DijkstraAlgorithm(Graph graph, int start, int end);
    std::vector<Connection> Astar(Graph graph, int start, int end, Heuristic heuristic);
};

#endif