#include "../include/graph.hpp"

std::vector<Connection> Graph::getNodes(int node)
{
    std::vector<Connection> connectedNodes = {};
    for (auto &connection : graph)
    {
        if (connection.fromNode == node && connection.toNode == -1)
        {
            connectedNodes.push_back(connection);
        }
    }
    return connectedNodes;
};

void Graph::addNode(int node)
{
    auto newNode = Connection(node);
    newNode.cost = 0.0f;

    graph.push_back(newNode);
}

void Graph::addEdge(Connection connection)
{
}