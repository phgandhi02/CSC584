#include "../../include/pathfinding/graph.hpp"
#include <bits/stdc++.h>

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

std::vector<Connection> GenMapGraph(std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> map)
{
    std::vector<Connection> edges;
    // std::cout << std::endl;
    for (unsigned int i = 0; i < MAP_HEIGHT; i++)
    {
        for (unsigned int j = 0; j < MAP_WIDTH; j++)
        {
            int fromNode = static_cast<int>(i * MAP_WIDTH + j);
            float cost = 1.0f;

            if ((i == 0) | (i == MAP_HEIGHT) | (j == 0) | (j == MAP_WIDTH))
            {
                continue;
            }
            // select each element
            auto cell = map[i][j];
            if (cell == Cell::Empty)
            {
                if (map[i + 1][j] == Cell::Empty)
                {
                    int toNode = fromNode + static_cast<int>(MAP_WIDTH); // cell above
                    edges.emplace_back(fromNode, toNode, cost);
                }
                if (map[i][j + 1] == Cell::Empty)
                {
                    int toNode = fromNode + 1; // cell to the right
                    edges.emplace_back(fromNode, toNode, cost);
                }
                if (map[i - 1][j] == Cell::Empty)
                {
                    int toNode = fromNode - static_cast<int>(MAP_WIDTH); // cell below
                    edges.emplace_back(fromNode, toNode, cost);
                }
                if (map[i][j - 1] == Cell::Empty)
                {
                    int toNode = fromNode - 1; // cell to the left
                    edges.emplace_back(fromNode, toNode, cost);
                }
            }
            // switch (map[i][j])
            // {
            // case Cell::Wall:
            // {
            //     std::cout << "#" << std::flush;
            //     break;
            // }
            // default:
            //     std::cout << "_" << std::flush;
            //     break;
            // }
        }
        // std::cout << std::endl;
    }
    return edges;
}

/**
 * @brief Convert a sketch into a map to be drawn with draw_map().
 *
 * @param map_sketch array of strings where the string represents a row and the char index for each string is the column number. To index for row i, column j -> `map_sketch[i][j]`
 * @return `std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> output_map`: collection of MAP_HEIGHT number of rows.
 */
std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> convert_sketch_to_map(std::array<std::string, MAP_HEIGHT> map_sketch)
{
    // std::cout << std::endl;
    // The inner array contains each row. The outer array contains all the rows that make the map.
    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> output_map;
    for (unsigned int i = 0; i < MAP_HEIGHT; i++) // loop for each row i in the map.
    {
        for (unsigned int j = 0; j < MAP_WIDTH; j++) // loop for elem j in the i row of the map
        {
            // ? why is this flipped?
            output_map[i][j] = Cell::Empty;

            switch (map_sketch[i][j])
            {
            case '#':
            {
                output_map[i][j] = Cell::Wall;
                // std::cout << "#";
                break;
            }
            default:
                output_map[i][j] = Cell::Empty;
                // std::cout << " ";
                break;
            }
        }
        // std::cout << std::endl;
    }
    return output_map;
};

unsigned int calculateNodeIndex(sf::Vector2f position)
{
    return (static_cast<unsigned int>(position.y) / CELL_SIZE) * MAP_WIDTH + static_cast<unsigned int>(position.x) / CELL_SIZE;
}

sf::Vector2f calculatePositionfromNode(unsigned int node)
{
    // calculate the row and column index from the node index
    int row_index = node / MAP_WIDTH;
    int col_index = node % MAP_WIDTH;
    float x_pos = static_cast<float>(row_index * CELL_SIZE + CELL_SIZE / 2);
    float y_pos = static_cast<float>(col_index * CELL_SIZE + CELL_SIZE / 2);
    auto position = sf::Vector2f(y_pos, x_pos);
    return position;
}