#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <memory>
#include <vector>

template <typename T>
class Node
{
public:
    Node() = default;
    std::vector<char[]> edges;
};

template <typename T>
class Connection
{
public:
    Node<std::string> fromNode;
    Node<std::string> toNode;
    float getConst();
};

template <typename T>
class Graph
{
public:
    std::vector<Connection<std::string>> getConnections(Node<std::string> fromNode);
};

std::vector<Connection<std::string>> pathfindDijkstra();

#endif // GRAPH_HPP