#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>
#include <iostream>

/*
Basic edge that contains a fromNode, toNode, and cost/edge weight. Contains helper functions for getting
*/
class Connection
{
public:
    // Create a Connection/Node Edge that has the same fromNode and toNode with a cost of 0.
    Connection(int fromNode) : fromNode(fromNode), toNode(fromNode) {};
    // Create a Connection/Node Edge.
    Connection(int fromNode, int toNode, float cost) : fromNode(fromNode), toNode(toNode), cost(cost) {};
    ~Connection() = default;

    bool operator==(const Connection &rhs) const
    {
        return (fromNode == rhs.fromNode && toNode == rhs.toNode && cost == rhs.cost);
    }

    const float getCost() { return cost; }
    const float getFromNode() { return fromNode; }
    const float getToNode() { return toNode; }
    // check if node is connected to another different node.
    const bool isConnected() { return (fromNode != toNode) ? true : false; }

    void setCost(float cost) { cost = cost; }
    void setToNode(int toNode) { toNode = toNode; }

private:
    int fromNode;
    int toNode;
    float cost = 0.0;
};

class NodeRecord
{
public:
    NodeRecord(int node) : node(node), connection(node) {};
    bool operator==(const NodeRecord rhs) const
    {
        return (node == rhs.node && connection == rhs.connection && costSoFar == rhs.costSoFar);
    }

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

#endif