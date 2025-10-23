#include "../include/graph.hpp"

#include <algorithm>

std::vector<std::pair<int, double>> Graph::getNodes(int fromNode)
{
    return nodes[fromNode];
}

AdjacentNode Graph::getSmallestNode(int fromNode)
{
    AdjacentNodeList adjacentNodes = getNodes(fromNode);

    // Code from https://stackoverflow.com/questions/53619536/how-to-find-the-minimum-element-in-vector-of-pairs-in-c
    AdjacentNode result = *std::min_element(begin(adjacentNodes), end(adjacentNodes), [](auto lhs, auto rhs)
                                            { return std::get<1>(lhs) < std::get<1>(rhs); });
    return result;
}

void Graph::addEdge(int fromNode, int toNode, double cost)
{
    // Check if newNodes is already in the adjacency list.
    if (nodes.find(fromNode) == nodes.end())
    {
        auto nodeConnections = std::vector<std::pair<int, double>>{
            {toNode, cost}};
        nodes[fromNode] = nodeConnections; // if the newNode is not in the list then assign the newNode's connnections to other nodes.
    }
    else
    {
        auto nodeConnections = std::pair<int, double>{toNode, cost};
        nodes[fromNode].push_back(nodeConnections); // if the newNode is already in the list then append the edge to the pre-existing vector of adjacent nodes and costs.
    }
}

void Graph::addNodes(int newNode, std::vector<std::pair<int, double>> nodeConnections)
{
    // Check if newNodes is already in the adjacency list.
    if (nodes.find(newNode) == nodes.end())
    {
        nodes[newNode] = nodeConnections; // if the newNode is not in the list then assign the newNode's connnections to other nodes.
    }
    else
    {
        nodes[newNode].insert(nodes[newNode].end(), nodeConnections.begin(), nodeConnections.end()); // if the newNode is already in the list then append the new nodeConnections to the pre-existing vector of adjacent nodes and costs.
    }
}