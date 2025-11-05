#include "../include/pathfinding_algos.hpp"

template <typename NodeRecordType>
std::ostream &operator<<(std::ostream &os, PathfindingList<NodeRecordType> const &m)
{
    return m.write(os);
}

template <typename NodeRecordType>
void PathfindingList<NodeRecordType>::add(NodeRecordType nodeRecord)
{
    nodeRecords.push_back(nodeRecord);
};

template <typename NodeRecordType>
void PathfindingList<NodeRecordType>::subtract(NodeRecordType nodeRecord)
{

    nodeRecords.erase(std::remove(nodeRecords.begin(), nodeRecords.end(), nodeRecord), nodeRecords.end());
    // std::remove(nodeRecords.begin(), nodeRecords.end(), nodeRecord);
    // nodeRecords.pop_back();
}

template <typename NodeRecordType>
NodeRecordType PathfindingList<NodeRecordType>::find(int node)
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
    return NodeRecordType(0, 0, 0.0f);
}

template <typename NodeRecordType>
bool PathfindingList<NodeRecordType>::contains(int node)
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

template <typename NodeRecordType>
NodeRecord PathfindingList<NodeRecordType>::smallestElement(NodeRecord &smallestRecord)
{
    // std::cout << "Looking for smallest node: " << std::endl;
    auto lowestCostSoFar = nodeRecords[0].costSoFar;
    // auto smallestRecord = nodeRecords[0];

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

template <typename NodeRecordType>
AStarNodeRecord PathfindingList<NodeRecordType>::smallestElement(AStarNodeRecord &smallestRecord)
{
    // std::cout << "Looking for smallest node: " << std::endl;
    auto lowestEstimatedTotalCostSoFar = nodeRecords[0].estimatedTotalCost;
    // auto smallestRecord = nodeRecords[0];

    for (auto &record : nodeRecords)
    {
        if (record.estimatedTotalCost <= lowestEstimatedTotalCostSoFar)
        {
            lowestEstimatedTotalCostSoFar = record.estimatedTotalCost;
            smallestRecord = record;
        }
    }
    return smallestRecord;
}

// template <typename NodeRecordType>
std::vector<Connection> Pathfinding::DijkstraAlgorithm(Graph &graph, int start, int end)
{
    // Step 0
    NodeRecord startRecord(start, start, 0.0f);
    startRecord.costSoFar = 0.0f;

    PathfindingList<NodeRecord> openList;
    PathfindingList<NodeRecord> closedList;

    openList.add(startRecord);
    auto current = startRecord;

    while (openList.size() > 0)
    {
        // get the smallest element in the open list
        current = openList.smallestElement(current);

        if (current.node == end)
        {
            break;
        }
        auto connections = graph.getNodes(current.node);

        // Loop through each connection of the smallest element and check if it's on the open list, closed list, or unvisited.
        for (auto &connection : connections)
        {
            if (!connection.isConnectedToDifferentNode())
            {
                continue;
            }
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
                if (!openList.contains(endNode))
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

        // std::reverse(path.begin(), path.end());

        return path;
    }
};

// template <typename NodeRecordType>
std::vector<Connection> Pathfinding::Astar(Graph &graph, int start, int end, Heuristic &heuristic)
{

    // Step 0
    AStarNodeRecord startRecord(start, start, 0.0f);
    startRecord.costSoFar = 0.0f;
    heuristic.goalNode = end;
    startRecord.estimatedTotalCost = heuristic.estimate(start);

    PathfindingList<AStarNodeRecord> openList;
    PathfindingList<AStarNodeRecord> closedList;

    openList.add(startRecord);
    auto current = startRecord;

    while (openList.size() > 0)
    {
        // get the smallest element in the open list
        current = openList.smallestElement(current);

        // If it is the goal node then terminate.
        if (current.node == end)
        {
            break;
        }

        // Otherwise get its outgoing connections
        auto connections = graph.getNodes(current.node);

        // Loop through each connection of the smallest element and check if it's on the open list, closed list, or unvisited.
        for (auto &connection : connections)
        {
            // make sure the current connection is actually connected to a different node.
            if (!current.connection.isConnectedToDifferentNode())
            {
                continue;
            }
            // std::cout << connection << std::endl;

            // Get the cost estimate for the endNode
            int endNode = connection.getToNode();
            float endNodeCost = current.costSoFar + connection.getCost();

            AStarNodeRecord endNodeRecord = AStarNodeRecord(endNode);
            float endNodeHeuristic = 0.0f;

            // Skip if the node is on the closed list.
            // This means that we have explored all the nodes connected to this node.
            if (closedList.contains(endNode))
            {
                // find the record in the closed list corresponding to the endNode
                endNodeRecord = closedList.find(endNode);

                // if we didn't find a shorter route, then skip.
                if (endNodeRecord.costSoFar <= endNodeCost)
                    continue;
                else
                {
                    // otherwise remove endNodeRecord from closed list
                    closedList.subtract(endNodeRecord);
                    // use the node's old cost values to calculate its heuristic without calling the possibly expensive heuristic function.
                    endNodeHeuristic = endNodeRecord.estimatedTotalCost - endNodeRecord.costSoFar;

                    // maybe delete
                    endNodeRecord.estimatedTotalCost = endNodeCost + endNodeHeuristic;
                }
            }
            // check if the node is on the openlist.
            // if it is on the open list then we want to see if this is a worse route.
            else
            {
                // AStarNodeRecord endNodeRecord = AStarNodeRecord(endNode);
                if (openList.contains(endNode))
                {
                    // check if the toNode of the current connection is in the openlist.
                    endNodeRecord = openList.find(endNode);
                    if (endNodeRecord.costSoFar <= endNodeCost)
                    {
                        continue;
                    }
                    else
                    {
                        // otherwise remove endNodeRecord from closed list
                        closedList.subtract(endNodeRecord);
                        // use the node's old cost values to calculate its heuristic without calling the possibly expensive heuristic function.
                        endNodeHeuristic = endNodeRecord.estimatedTotalCost - endNodeRecord.costSoFar;
                    }
                }
                else
                {
                    // Unvisited node so we need to make a new record
                    endNodeRecord = AStarNodeRecord(endNode, connection.getToNode(), connection.getCost());
                    endNodeRecord.estimatedTotalCost = heuristic.estimate(endNode);
                }

                endNodeRecord.costSoFar = endNodeCost; // update costSoFar with connection cost
                endNodeRecord.connection = connection; // update with connection from the fromNode to the toNode.
                endNodeRecord.estimatedTotalCost = endNodeCost + endNodeHeuristic;

                // add it to the openList
                if (!openList.contains(endNode))
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

        // std::reverse(path.begin(), path.end());

        return path;
    }
};