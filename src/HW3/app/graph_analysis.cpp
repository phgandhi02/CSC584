#include "../include/graph.hpp"
#include "../include/pathfinding_algos.hpp"

int main()
{
    std::cout << "Graph Analysis Running!" << std::endl;
    Graph graph = Graph();
    graph.addEdge(Connection(1, 2, 1.3f));
    graph.addEdge(Connection(1, 3, 1.6f));
    graph.addEdge(Connection(1, 4, 3.3f));
    graph.addEdge(Connection(2, 5, 1.5f));
    graph.addEdge(Connection(2, 6, 1.9f));
    graph.addEdge(Connection(3, 4, 1.3f));
    graph.addEdge(Connection(6, 7, 1.4f));
    auto pathfinding = Pathfinding();
    auto path = pathfinding.DijkstraAlgorithm(graph, 1, 7);
    for (auto &connection : path)
    {
        std::cout << connection << std::endl;
    }
    std::cout << "Graph Analysis Complete!" << std::endl;
    return 0;
}