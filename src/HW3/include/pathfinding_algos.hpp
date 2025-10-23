#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "graph.hpp"
#include "heuristic.hpp"

#include <algorithm>

class NodeRecord
{
public:
    NodeRecord() = default;
    ~NodeRecord() = default;
    int node;
    AdjacentNode adjacentNode;
};

class PathfindingList
{
public:
    NodeRecord smallestElement();
    bool contains(NodeRecord record);
    NodeRecord find(NodeRecord record);
    std::vector<NodeRecord> reverse()
    {
        std::vector<NodeRecord> nodeRecordsCopy(nodeRecords.size());
        std::reverse_copy(nodeRecords.begin(), nodeRecords.end(), nodeRecordsCopy.begin());
        return nodeRecordsCopy;
    }
    void append(NodeRecord newRecord) { nodeRecords.push_back(newRecord); }
    void pop() { nodeRecords.pop_back(); }
    int size() { return nodeRecords.size(); }

private:
    std::vector<NodeRecord> nodeRecords;
};

class Pathfinding
{
    Pathfinding() = default;
    ~Pathfinding() = default;
    std::vector<int> DijkstraAlgorithm(Graph graph, int start, int end);
    std::vector<int> Astar(Graph graph, int start, int end, Heuristic heuristic);
};

#endif