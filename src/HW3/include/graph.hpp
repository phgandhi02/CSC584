#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>

class Connection
{
public:
    Connection(int fromNode) : fromNode(fromNode) {};
    Connection(int fromNode, int toNode, float cost) : fromNode(fromNode), toNode(toNode), cost(cost) {};
    ~Connection() = default;

    int fromNode = -1;
    int toNode = -1;
    float cost = 0.0;

    float getCost() { return cost; }
    float getFromNode() { return fromNode; }
    float getToNode() { return toNode; }
};

class NodeRecord
{
public:
    NodeRecord(int node) : node(node), connection(node) {};
    int node = -1;
    Connection connection;
    float costSoFar = 0.0f;
};

class Graph
{
public:
    Graph() = default;
    ~Graph() = default;

    std::vector<Connection> getNodes(int node);

    void addNode(int newNode);
    void addEdge(Connection connection);

private:
    std::vector<Connection> graph;
};

#endif // GRAPH_HPP