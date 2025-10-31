#include "../include/graph.hpp"
#include "../include/pathfinding_algos.hpp"

#include <chrono>

int main()
{
    std::cout << "Program Running!" << std::endl;
    Graph graph = Graph();
    auto numVertices = 3000;         // 7 + rand() % 6;
    auto numEdges = numVertices * 3; // rand() % ((numVertices * (numVertices - 1)) / 2);
    std::cout << "Generating a graph!" << std::endl;
    auto edges = GenRandomGraphs(numEdges, numVertices, false);

    for (Connection &edge : edges)
    {
        graph.addEdge(edge);
    }

    std::cout << "Graph Analysis Running!" << std::endl;
    auto pathfinding = Pathfinding();

    auto start = std::chrono::high_resolution_clock::now();
    auto path = pathfinding.DijkstraAlgorithm(graph, 1, 7);
    // After function call
    auto stop = std::chrono::high_resolution_clock::now();
    for (auto &connection : path)
    {
        std::cout << connection << std::endl;
    }
    std::cout << "Graph Analysis Complete!" << std::endl;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Dijkstra took " << duration.count() << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto heuristic = EuclidianHeuristic();
    path = pathfinding.Astar(graph, 1, 7, heuristic);
    stop = std::chrono::high_resolution_clock::now();
    for (auto &connection : path)
    {
        std::cout << connection << std::endl;
    }
    std::cout << "Graph Analysis Complete!" << std::endl;

    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Dijkstra took " << duration.count() << " microseconds" << std::endl;
    return 0;
}