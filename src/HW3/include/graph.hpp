#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>

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

class NodeRecord
{
public:
    NodeRecord() = default;
    ~NodeRecord() = default;
    int node;
    Connection connection;
    float costSoFar;
};

class Graph
{
public:
    Graph() = default;
    ~Graph() = default;

    std::vector<Connection> getNodes(NodeRecord node);

    void addNodes(int newNode);
    void addEdge(Connection connection);
};

#endif // GRAPH_HPP