#include "../include/graph.hpp"

std::ostream &operator<<(std::ostream &os, Connection const &m)
{
    // since `write` is public, we can call it without any problem.
    return m.write(os);
};

std::ostream &operator<<(std::ostream &os, NodeRecord const &m)
{
    // since `write` is public, we can call it without any problem.
    return m.write(os);
};

std::vector<Connection> Graph::getNodes(int node)
{
    std::vector<Connection> connectedNodes = {Connection(node, node, 0.0f)};
    for (auto &connection : graph)
    {
        if (connection.getFromNode() == node && connection.isConnected())
        {
            connectedNodes.push_back(connection);
        }
    }
    return connectedNodes;
};

void Graph::addNode(int fromNode, int toNode, float cost)
{
    auto newConnection = Connection(fromNode, toNode, cost);

    graph.push_back(newConnection);
};

void Graph::addEdge(Connection connection)
{
    graph.push_back(connection);
};