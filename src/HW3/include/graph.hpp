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
    std::ostream &write(std::ostream &os) const
    {
        // write stuff to stream
        os << "fromNode: " << fromNode << " | " << "toNode: " << toNode << " | " << "Cost: " << cost << std::endl;
        return os;
    }

    float getCost() { return cost; }
    float getFromNode() { return fromNode; }
    float getToNode() { return toNode; }
    // check if node is connected to another different node.
    bool isConnected() { return (fromNode != toNode) ? true : false; }

    void setCost(float cost) { cost = cost; }
    void setToNode(int toNode) { toNode = toNode; }

private:
    int fromNode;
    int toNode;
    float cost = 0.0;
};

std::ostream &operator<<(std::ostream &os, Connection const &m);

class NodeRecord
{
public:
    NodeRecord(int node) : node(node), connection(node) {};
    NodeRecord(int fromNode, int toNode, float cost) : node(fromNode), connection(fromNode, toNode, cost) {};
    bool operator==(const NodeRecord rhs) const
    {
        return (node == rhs.node && connection == rhs.connection && costSoFar == rhs.costSoFar);
    }
    std::ostream &write(std::ostream &os) const
    {
        // write stuff to stream
        os << "Node: " << node << " | " << "Connection: <" << connection << "> " << "costSoFar: " << costSoFar << std::endl;
        return os;
    }

    int node = -1;
    Connection connection;
    float costSoFar = 0.0f;
};

std::ostream &operator<<(std::ostream &os, NodeRecord const &m);

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

// Function to generate random graph
std::vector<Connection> GenRandomGraphs(int numEdges, int numVertices);
// Function to generate random graph
std::vector<Connection> GenRandomGraphs(int numEdges, int numVertices, bool printGraph);

#endif