#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "graph.hpp"
#include "heuristic.hpp"

#include <algorithm>
#include <iostream>

template <class NodeRecordType>
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
    NodeRecord smallestElement(NodeRecord &smallestRecord);
    AStarNodeRecord smallestElement(AStarNodeRecord &smallestRecord);
    bool contains(int node);
    NodeRecordType find(int node);
    void add(NodeRecordType newRecord);
    void subtract(NodeRecordType newRecord);
    int size() { return nodeRecords.size(); }
    std::vector<NodeRecordType> nodeRecords;

private:
};

template <typename NodeRecordType>
std::ostream &operator<<(std::ostream &os, PathfindingList<NodeRecordType> const &m);

// template <class NodeRecordType>
class Pathfinding
{
public:
    Pathfinding() = default;
    ~Pathfinding() = default;
    std::vector<Connection> DijkstraAlgorithm(Graph graph, int start, int end);
    std::vector<Connection> Astar(Graph graph, int start, int end, Heuristic heuristic);
};

#endif