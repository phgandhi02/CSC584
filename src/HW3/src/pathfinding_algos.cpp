#include "../include/pathfinding_algos.hpp"

std::ostream &operator<<(std::ostream &os, PathfindingList const &m)
{
    return m.write(os);
}

void PathfindingList::add(NodeRecord nodeRecord)
{
    nodeRecords.push_back(nodeRecord);
};

void PathfindingList::subtract(NodeRecord nodeRecord)
{

    nodeRecords.erase(std::remove(nodeRecords.begin(), nodeRecords.end(), nodeRecord), nodeRecords.end());
    // std::remove(nodeRecords.begin(), nodeRecords.end(), nodeRecord);
    // nodeRecords.pop_back();
}

NodeRecord PathfindingList::find(int node)
{
    // std::cout << "Searching for node: " << node << std::endl;
    for (auto &record : nodeRecords)
    {
        if (record.node == node)
        {
            // std::cout << "Found node: " << node << std::endl;
            return record;
        }
    }
    // std::cout << "Didn't find node" << std::endl;
    return NodeRecord(0, 0, 0.0f);
}

bool PathfindingList::contains(int node)
{
    // std::cout << "Searching for node: " << node << std::endl;
    for (auto &record : nodeRecords)
    {
        if (record.node == node)
        {
            // std::cout << "Found node: " << node << std::endl;
            return true;
        }
    }
    // std::cout << "Didn't find node" << std::endl;
    return false;
}

NodeRecord PathfindingList::smallestElement()
{
    // std::cout << "Looking for smallest node: " << std::endl;
    auto lowestCostSoFar = nodeRecords[0].costSoFar;
    auto smallestRecord = nodeRecords[0];

    for (auto &record : nodeRecords)
    {
        if (record.costSoFar <= lowestCostSoFar)
        {
            lowestCostSoFar = record.costSoFar;
            smallestRecord = record;
        }
    }
    return smallestRecord;
}

std::vector<Connection> Pathfinding::DijkstraAlgorithm(Graph graph, int start, int end)
{
    // Step 0
    NodeRecord startRecord(start, start, 0.0f);
    startRecord.costSoFar = 0.0f;

    PathfindingList openList;
    PathfindingList closedList;
    int endNode;

    openList.add(startRecord);
    auto current = startRecord;

    while (openList.size() > 0)
    {
        // get the smallest element in the open list
        current = openList.smallestElement();

        if (current.node == end)
        {
            break;
        }
        // if (!current.connection.isConnected())
        // {
        //     continue;
        // }
        auto connections = graph.getNodes(current.node);

        // Loop through each connection of the smallest element and check if it's on the open list, closed list, or unvisited.
        for (auto &connection : connections)
        {
            // std::cout << connection << std::endl;

            // ToNode of the current connection
            int endNode = connection.getToNode();
            float endNodeCost = current.costSoFar + connection.getCost();

            // Skip if the node is on the closed list.
            // This means that we have explored all the nodes connected to this node.
            if (closedList.contains(endNode))
            {
                continue;
            }
            // check if the node is on the openlist.
            // if it is on the open list then we want to see if this is a worse route.
            else
            {
                NodeRecord endNodeRecord = NodeRecord(endNode);
                if (openList.contains(endNode))
                {
                    // check if the toNode of the current connection is in the openlist.
                    endNodeRecord = openList.find(endNode);
                    if (endNodeRecord.costSoFar <= endNodeCost)
                    {
                        continue;
                    }
                }
                else
                {
                    // Unvisited node so we need to make a new record
                    endNodeRecord = NodeRecord(endNode, connection.getToNode(), connection.getCost());
                }

                endNodeRecord.costSoFar = endNodeCost; // update costSoFar with connection cost
                endNodeRecord.connection = connection; // update with connection from the fromNode to the toNode.

                // add it to the openList
                if (~openList.contains(endNode))
                {
                    openList.add(endNodeRecord);
                }
            }
        }
        openList.subtract(current);
        closedList.add(current);
        // std::cout << "Open List" << std::endl;
        // std::cout << openList << std::endl;
        // std::cout << "Closed List" << std::endl;
        // std::cout << closedList << std::endl;
    }

    if (current.node != end)
    {
        // We’ve run out of nodes without finding the goal, so there’s no solution.
        return std::vector<Connection>{};
    }
    else
    {
        std::vector<Connection> path;
        // int currentNode = current.node;
        while (current.node != start)
        {
            path.push_back(current.connection);
            current = closedList.find(current.connection.getFromNode());
        }

        std::reverse(path.begin(), path.end());

        return path;
    }
};

std::vector<Connection> Pathfinding::Astar(Graph graph, int start, int end, Heuristic heuristic)
{
    // Step 0
    NodeRecord startRecord(start, start, 0.0f);
    startRecord.costSoFar = 0.0f;

    PathfindingList openList;
    PathfindingList closedList;
    int endNode;

    openList.add(startRecord);
    auto current = startRecord;

    while (openList.size() > 0)
    {
        // get the smallest element in the open list
        current = openList.smallestElement();

        if (current.node == end)
        {
            break;
        }
        // if (!current.connection.isConnected())
        // {
        //     continue;
        // }
        auto connections = graph.getNodes(current.node);

        // Loop through each connection of the smallest element and check if it's on the open list, closed list, or unvisited.
        for (auto &connection : connections)
        {
            // std::cout << connection << std::endl;

            // ToNode of the current connection
            int endNode = connection.getToNode();
            float endNodeCost = current.costSoFar + connection.getCost();

            // Skip if the node is on the closed list.
            // This means that we have explored all the nodes connected to this node.
            if (closedList.contains(endNode))
            {
                continue;
            }
            // check if the node is on the openlist.
            // if it is on the open list then we want to see if this is a worse route.
            else
            {
                NodeRecord endNodeRecord = NodeRecord(endNode);
                if (openList.contains(endNode))
                {
                    // check if the toNode of the current connection is in the openlist.
                    endNodeRecord = openList.find(endNode);
                    if (endNodeRecord.costSoFar <= endNodeCost)
                    {
                        continue;
                    }
                }
                else
                {
                    // Unvisited node so we need to make a new record
                    endNodeRecord = NodeRecord(endNode, connection.getToNode(), connection.getCost());
                }

                endNodeRecord.costSoFar = endNodeCost; // update costSoFar with connection cost
                endNodeRecord.connection = connection; // update with connection from the fromNode to the toNode.

                // add it to the openList
                if (~openList.contains(endNode))
                {
                    openList.add(endNodeRecord);
                }
            }
        }
        openList.subtract(current);
        closedList.add(current);
        // std::cout << "Open List" << std::endl;
        // std::cout << openList << std::endl;
        // std::cout << "Closed List" << std::endl;
        // std::cout << closedList << std::endl;
    }

    if (current.node != end)
    {
        // We’ve run out of nodes without finding the goal, so there’s no solution.
        return std::vector<Connection>{};
    }
    else
    {
        std::vector<Connection> path;
        // int currentNode = current.node;
        while (current.node != start)
        {
            path.push_back(current.connection);
            current = closedList.find(current.connection.getFromNode());
        }

        std::reverse(path.begin(), path.end());

        return path;
    }
};