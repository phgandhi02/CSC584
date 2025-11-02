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

// // Function to generate random graph
// std::vector<Connection> GenGridGraph(int numRows, int numCols)
// {
//     std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols));
//     // TODO: handle path to the outer rim of the map.
//     // // cut the outer rows and columns of the map.
//     // numRows = numRows - 2;
//     // numCols = numCols - 2;
//     int totalNodes = numRows * numCols;
//     // int totalNumEdges = 9 * numRows * numCols;
//     int totalNumEdges = 9 * (numRows - 2) * (numCols - 2) + 2 * numRows * 6 + 2 * numCols * 6 + 16;
//     std::vector<Connection> edges;

//     // float cost;
//     srand(time(0));

//     // Print the attributes of graph
//     std::cout << "Grid graph generation: " << std::endl;
//     std::cout << "The graph has " << totalNodes << " Nodes" << std::endl;
//     std::cout << "and has " << totalNumEdges << " edges." << std::endl;

//     int arr_index = 0;
//     for (int i = 0; i <= numRows; i++)
//     {
//         for (int j = 0; j <= numCols; j++)
//         {
//             arr_index = i * numRows + j;
//             if ((arr_index % numRows) == 0 || (arr_index % numRows) == numCols || arr_index <= numCols || arr_index >= numRows * numRows)
//             {
//                 continue;
//             }
//             else
//             {
//                 edges.emplace_back(Connection(arr_index, arr_index + 1, 1.0f));             // right
//                 edges.emplace_back(Connection(arr_index, arr_index + numCols, 1.0f));       // down
//                 edges.emplace_back(Connection(arr_index, arr_index - numCols, 1.0f));       // up
//                 edges.emplace_back(Connection(arr_index, arr_index - 1, 1.0f));             // left
//                 edges.emplace_back(Connection(arr_index, arr_index - numCols - 1, 1.414f)); // top left
//                 edges.emplace_back(Connection(arr_index, arr_index - numCols + 1, 1.414f)); // top right
//                 edges.emplace_back(Connection(arr_index, arr_index + numCols + 1, 1.414f)); // bottom right
//                 edges.emplace_back(Connection(arr_index, arr_index + numCols - 1, 1.414f)); // bottom left
//             }
//         }
//     }

//     return edges;
// }

std::vector<Connection> GenGridGraph(int numRows, int numCols)
{
    // numRows = numRows - 2;
    // numCols = numCols - 2;
    std::vector<Connection> edges;
    int totalNodes = numRows * numCols;
    srand(time(0));

    std::cout << "Grid graph generation: " << std::endl;
    std::cout << "The graph has " << totalNodes << " Nodes" << std::endl;

    for (int i = 0; i < numRows; i++) // Loop from 0 to numRows-1
    {
        for (int j = 0; j < numCols; j++) // Loop from 0 to numCols-1
        {
            int fromNode = i * numCols + j; // Correct index calculation

            // 8 directions (row, col offsets)
            int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
            float costs[] = {1.414f, 1.0f, 1.414f, 1.0f, 1.0f, 1.414f, 1.0f, 1.414f};

            for (int k = 0; k < 8; k++)
            {
                int ni = i + dr[k]; // Neighbor's row
                int nj = j + dc[k]; // Neighbor's col

                // Check if neighbor is *inside* the grid
                if (ni >= 0 && ni < numRows && nj >= 0 && nj < numCols)
                {
                    int toNode = ni * numCols + nj;
                    edges.emplace_back(Connection(fromNode, toNode, costs[k]));
                }
            }
        }
    }
    std::cout << "and has " << edges.size() << " edges." << std::endl;
    return edges;
}
