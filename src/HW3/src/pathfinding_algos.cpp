#include "../include/pathfinding_algos.hpp"

void PathfindingList::add(NodeRecord nodeRecord)
{
    nodeRecords.push_back(nodeRecord);
};

void PathfindingList::subtract(NodeRecord nodeRecord)
{
    std::remove(nodeRecords.begin(), nodeRecords.end(), nodeRecord);
    nodeRecords.pop_back();
}

NodeRecord PathfindingList::find(int node)
{
    for (auto &record : nodeRecords)
    {
        if (record.node == node)
        {
            return record;
        }
    }
    return NodeRecord(-1);
}

bool PathfindingList::contains(int node)
{
    for (auto &record : nodeRecords)
    {
        if (record.node == node)
        {
            return true;
        }
    }
    return false;
}

NodeRecord PathfindingList::smallestElement()
{
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
    NodeRecord startRecord(start);
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

        auto connections = graph.getNodes(current.node);

        // Loop through each connection in turn
        for (auto &connection : connections)
        {
            int endNode = connection.getToNode();
            float endNodeCost = current.costSoFar + connection.getCost();

            // Skip if the node is closed
            if (closedList.contains(endNode))
            {
                continue;
            }
            else if (openList.contains(endNode))
            {
                NodeRecord endNodeRecord = openList.find(endNode);
                if (endNodeRecord.costSoFar <= endNodeCost)
                {
                    continue;
                }
            }
            else
            {
                auto endNodeRecord = NodeRecord(endNode);
                endNodeRecord.costSoFar = endNodeCost;
                endNodeRecord.connection = connection;

                if (~openList.contains(endNode))
                {
                    openList.add(endNodeRecord);
                }
            }

            openList.subtract(current);
            closedList.add(current);
        }
    }

    if (current.node != end)
    {
        // We’ve run out of nodes without finding the goal, so there’s no solution.
        return std::vector<Connection>{};
    }
    else
    {
        std::vector<Connection> path;
        int currentNode = current.node;
        while (currentNode != start)
        {
            path.push_back(current.connection);
            currentNode = current.connection.getFromNode();
        }

        std::reverse(path.begin(), path.end());

        return path;
    }
}