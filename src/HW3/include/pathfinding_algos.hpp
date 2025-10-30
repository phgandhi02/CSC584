#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "graph.hpp"
#include "heuristic.hpp"

#include <algorithm>
#include <iostream>

class PathfindingList
{
public:
    std::ostream &write(std::ostream &os) const
    {
        for (auto &record : nodeRecords)
        {
            // write stuff to stream
            os << "Record: " << record << std::endl;
        }
        return os;
    }
    NodeRecord smallestElement();
    bool contains(int node);
    NodeRecord find(int node);
    void add(NodeRecord newRecord);
    void subtract(NodeRecord newRecord);
    int size() { return nodeRecords.size(); }
    std::vector<NodeRecord> nodeRecords;

private:
};

std::ostream &operator<<(std::ostream &os, PathfindingList const &m);

class Pathfinding
{
public:
    Pathfinding() = default;
    ~Pathfinding() = default;
    std::vector<Connection> DijkstraAlgorithm(Graph graph, int start, int end);
    std::vector<Connection> Astar(Graph graph, int start, int end, Heuristic heuristic);
};

#endif