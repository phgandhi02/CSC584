#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <tuple>
#include <vector>

class Graph
{
public:
    Graph() = default;
    ~Graph() = default;
    std::vector<std::pair<int, double>> getNodes(int fromNode);
    void addNodes(int newNode, std::vector<std::pair<int, double>> nodeConnections);
    void addEdge(int fromNode, int newNode, double cost);

private:
    std::unordered_map<int, std::vector<std::pair<int, double>>> nodes;
};

#endif // GRAPH_HPP