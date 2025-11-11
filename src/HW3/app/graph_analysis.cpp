#include "../include/graph.hpp"
#include "../include/pathfinding_algos.hpp"

#include <chrono>

void RunDijkstra(Graph graph, int startNode, int goalNode)
{
    std::cout << "Graph Analysis Running!" << std::endl;
    auto pathfinding = Pathfinding();

    auto start = std::chrono::high_resolution_clock::now();
    auto path = pathfinding.DijkstraAlgorithm(graph, startNode, goalNode);
    // After function call
    auto stop = std::chrono::high_resolution_clock::now();
    for (auto &connection : path)
    {
        std::cout << connection << std::endl;
    }
    std::cout << "Graph Analysis Complete!" << std::endl;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Dijkstra took " << duration.count() << " microseconds" << std::endl;
}

void RunAstar(Graph graph, Heuristic &heuristic, int startNode, int goalNode)
{
    auto pathfinding = Pathfinding();
    auto start = std::chrono::high_resolution_clock::now();
    auto path = pathfinding.Astar(graph, 1, 7, heuristic);
    auto stop = std::chrono::high_resolution_clock::now();
    for (auto &connection : path)
    {
        std::cout << connection << std::endl;
    }
    std::cout << "Graph Analysis Complete!" << std::endl;

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "A* with Heuristic took " << duration.count() << " microseconds" << std::endl;
}

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

    Graph smallGraph = Graph();
    smallGraph.addEdge(Connection(1, 2, 1.3f));
    smallGraph.addEdge(Connection(1, 3, 1.6f));
    smallGraph.addEdge(Connection(1, 4, 3.3f));
    smallGraph.addEdge(Connection(2, 5, 1.5f));
    smallGraph.addEdge(Connection(2, 6, 1.9f));
    smallGraph.addEdge(Connection(3, 4, 1.3f));
    smallGraph.addEdge(Connection(6, 7, 1.4f));
    RunDijkstra(smallGraph, 1, 7);

    RunDijkstra(graph, 1, 7);
    auto euclidianHeuristic = EuclidianHeuristic();
    RunAstar(graph, euclidianHeuristic, 1, 7);

    auto manhattanHeuristic = ManhattanHeuristic();
    RunAstar(graph, manhattanHeuristic, 1, 7);

    return 0;
}