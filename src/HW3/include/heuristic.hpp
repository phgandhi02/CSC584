#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

#include "graph.hpp"

class Heuristic
{
public:
    Heuristic() = default;
    virtual float estimate(int fromNode);
    virtual float estimate(int fromNode, int goalNode);
    int goalNode;
};

class EuclidianHeuristic : Heuristic
{
public:
    float estimate(int fromNode) override;
    float estimate(int fromNode, int goalNode) override;
};

class ManhattanHeuristic : Heuristic
{
public:
    float estimate(int fromNode) override;
    float estimate(int fromNode, int goalNode) override;
};

class InadmissableHeuristic : Heuristic
{
public:
    float estimate(int fromNode) override;
    float estimate(int fromNode, int goalNode) override;
};
#endif
