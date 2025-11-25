#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

#include "graph.hpp"

class Heuristic
{
public:
    Heuristic() = default;
    ~Heuristic() = default;
    virtual float estimate(int fromNode) = 0;
    virtual float estimate(int fromNode, int goalNode) = 0;
    int goalNode;
};

class EuclidianHeuristic : public Heuristic
{
public:
    EuclidianHeuristic() = default;
    ~EuclidianHeuristic() = default;
    float estimate(int fromNode) override;
    float estimate(int fromNode, int goalNode) override;
};

class ManhattanHeuristic : public Heuristic
{
public:
    ManhattanHeuristic() = default;
    ~ManhattanHeuristic() = default;
    float estimate(int fromNode) override;
    float estimate(int fromNode, int goalNode) override;
};

class InadmissableHeuristic : public Heuristic
{
public:
    InadmissableHeuristic() = default;
    ~InadmissableHeuristic() = default;
    float estimate(int fromNode) override;
    float estimate(int fromNode, int goalNode) override;
};
#endif
