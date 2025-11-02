#include "../include/graph.hpp"

std::ostream &operator<<(std::ostream &os, Connection const &m)
{
    // since `write` is public, we can call it without any problem.
    return m.write(os);
};

std::vector<Connection> Graph::getNodes(int node)
{
    std::vector<Connection> connectedNodes = {Connection(node, node, 0.0f)};
    for (auto &connection : graph)
    {
        if (connection.getFromNode() == node && connection.isConnectedToDifferentNode())
        {
            connectedNodes.push_back(connection);
        }
    }
    return connectedNodes;
};

void Graph::addNode(int newNode)
{
    auto newConnection = Connection(newNode);

    graph.push_back(newConnection);
};

void Graph::addEdge(Connection connection)
{
    graph.push_back(connection);
};

#include <bits/stdc++.h>

/*
src: https://www.geeksforgeeks.org/dsa/how-to-create-a-random-graph-in-c/
*/
// Function to generate random graph
std::vector<Connection> GenRandomGraphs(int numEdges, int numVertices)
{
    int i, j;
    std::vector<Connection> edges;
    // int i, j, edge[numEdges][2], count;
    i = 0;
    int fromNode, toNode;
    float cost;
    srand(time(0));

    // Print the attributes of graph
    std::cout << "Random graph generation: " << std::endl;
    std::cout << "The graph has " << numVertices << " vertices" << std::endl;
    std::cout << "and has " << numEdges << " edges." << std::endl;

    // Assign random values to the number
    // of vertex and edges of the graph,
    // Using rand().
    while (i < numEdges)
    {
        fromNode = rand() % numVertices + 1;
        toNode = rand() % numVertices + 1;
        cost = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f;

        edges.emplace_back(Connection(fromNode, toNode, cost));

        // Print the connections of each
        // vertex, irrespective of the
        // direction.

        // Check if the edge has the same fromNode and toNode. If so, skip and replace the node in next loop.
        if (edges[i].isConnectedToDifferentNode() == false)
        {
            // std::cout << "Node not connected" << edges[i].isConnected() << std::endl;
            edges.pop_back();
            continue;
        }
        else
        {
            for (j = 0; j < i; j++)
            {
                // check if edge already exists. If so, skip and replace the node in next loop.
                if ((edges[i].getFromNode() == edges[j].getFromNode() && edges[i].getToNode() == edges[j].getToNode()) || (edges[i].getFromNode() == edges[j].getToNode() && edges[i].getToNode() == edges[j].getFromNode()))
                {
                    // std::cout << edges[i] << " is duplicate of " << edges[j] << std::endl;
                    edges.pop_back();
                    i--;
                }
            }
        }
        i++;
    }

    return edges;
}

std::vector<Connection> GenRandomGraphs(int numEdges, int numVertices, bool printGraph)
{
    int i, j, count;
    std::vector<Connection> edges = GenRandomGraphs(numEdges, numVertices);

    if (printGraph)
    {
        std::cout << "The generated random graph is: " << std::endl;
        for (i = 0; i < numVertices; i++)
        {
            count = 0;
            std::cout << "\t" << i + 1 << "-> { ";
            for (j = 0; j < numEdges; j++)
            {
                if (edges[j].getFromNode() == i + 1)
                {
                    std::cout << edges[j].getToNode() << " ";
                    count++;
                }
                else if (edges[j].getToNode() == i + 1)
                {
                    std::cout << edges[j].getToNode() << " ";
                    count++;
                }
                else if (j == numEdges - 1 && count == 0)

                    // Print “Isolated vertex”
                    // for the vertex having
                    // no degree.
                    std::cout << "Isolated Vertex!";
            }
            std::cout << " }" << std::endl;
        }
    }
    return edges;
}