#include "../include/graph.hpp"
#include "../include/pathfinding_algos.hpp"

int main()
{
    std::cout << "Program Running!" << std::endl;
    Graph graph = Graph();
    auto numVertices = 30000;        // 7 + rand() % 6;
    auto numEdges = numVertices * 3; // rand() % ((numVertices * (numVertices - 1)) / 2);
    std::cout << "Generating a graph!" << std::endl;
    auto edges = GenRandomGraphs(numEdges, numVertices, false);

    for (Connection &edge : edges)
    {
        graph.addEdge(edge);
    }

    std::cout << "Graph Analysis Running!" << std::endl;
    auto pathfinding = Pathfinding();
    auto path = pathfinding.DijkstraAlgorithm(graph, 1, 7);
    for (auto &connection : path)
    {
        std::cout << connection << std::endl;
    }
    std::cout << "Graph Analysis Complete!" << std::endl;
    return 0;
}