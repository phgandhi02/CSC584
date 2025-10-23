#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <tuple>
#include <vector>

using AdjacentNode = std::pair<int, double>;        // type alias for nodes adjacent to the fromNode. type-id is std::pair<int, double>
using AdjacentNodeList = std::vector<AdjacentNode>; // type alias for list of nodes adjacent to the fromNode. type-id is std::pair<int, double>

class Connection
{
public:
    int fromNode;
    int toNode;
    float cost;

    float getCost() { return cost; }
    float getFromNode() { return fromNode; }
    float getToNode() { return toNode; }
};

class Graph
{
public:
    Graph() = default;
    ~Graph() = default;

    AdjacentNodeList getNodes(int fromNode);
    AdjacentNode getSmallestNode(int fromNode);

    void addNodes(int newNode, AdjacentNodeList nodeConnections);
    void addEdge(int fromNode, int newNode, double cost);

private:
    std::unordered_map<int, AdjacentNodeList> nodes;
};

#endif // GRAPH_HPP