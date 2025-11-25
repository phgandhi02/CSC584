#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "../global.hpp"

#include <SFML/Graphics.hpp>

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
    Connection(int fromNode) : m_fromNode(fromNode), m_toNode(fromNode), m_cost(0.0f) {};
    // Create a Connection/Node Edge.
    Connection(int fromNode, int toNode, float cost) : m_fromNode(fromNode), m_toNode(toNode), m_cost(cost) {};
    ~Connection() = default;

    bool operator==(const Connection &rhs) const
    {
        return (m_fromNode == rhs.m_fromNode && m_toNode == rhs.m_toNode && m_cost == rhs.m_cost);
    }
    std::ostream &write(std::ostream &os) const
    {
        // write stuff to stream
        os << "fromNode: " << m_fromNode << " | " << "toNode: " << m_toNode << " | " << "Cost: " << m_cost << std::endl;
        return os;
    }

    int getCost() { return this->m_cost; }
    int getFromNode() { return this->m_fromNode; }
    int getToNode() { return this->m_toNode; }
    // return true if the fromNode is different than the toNode.
    bool isConnectedToDifferentNode() { return (m_fromNode != m_toNode) ? true : false; }

    void setCost(float cost) { this->m_cost = cost; }
    void setToNode(int toNode) { this->m_toNode = toNode; }

private:
    unsigned int m_fromNode;
    unsigned int m_toNode;
    float m_cost = 0.0;
};

std::ostream &operator<<(std::ostream &os, Connection const &m);

class NodeRecord
{
public:
    NodeRecord(int node) : node(node), connection(Connection(node)) {};
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

class AStarNodeRecord : public NodeRecord
{
public:
    AStarNodeRecord(int node) : NodeRecord(node) {};
    AStarNodeRecord(int fromNode, int toNode, float cost) : NodeRecord(fromNode, toNode, cost) {};
    bool operator==(const AStarNodeRecord rhs) const
    {
        return (node == rhs.node && connection == rhs.connection && costSoFar == rhs.costSoFar && estimatedTotalCost == rhs.estimatedTotalCost);
    }
    float getCost() { return connection.getCost(); }
    float estimatedTotalCost = 0.0f;
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

// Function to generate open Grid graph
std::vector<Connection> GenGridGraph(int numRows, int numCols);

std::vector<Connection> GenMapGraph(std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> map);

std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> convert_sketch_to_map(std::array<std::string, MAP_HEIGHT> map_sketch);

unsigned int calculateNodeIndex(sf::Vector2f position);

sf::Vector2f calculatePositionfromNode(unsigned int node);

#endif