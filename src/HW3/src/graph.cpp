#include "../include/graph.hpp"

std::vector<Connection> Graph::getNodes(int node)
{
    std::vector<Connection> connectedNodes = {};
    for (auto &connection : graph)
    {
        if (connection.getFromNode() == node && connection.isConnected())
        {
            connectedNodes.push_back(connection);
        }
    }
    return connectedNodes;
};

void Graph::addNode(int node)
{
    auto newConnection = Connection(node);

    graph.push_back(newConnection);
}

void Graph::addEdge(Connection connection)
{
    graph.push_back(connection);
}