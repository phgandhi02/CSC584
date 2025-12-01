#ifndef BEHAVIOR_TREES_HPP
#define BEHAVIOR_TREES_HPP
/*
Behavior Trees lib contains various behavior tree node objs that can be
used to construct a behavior tree.
*/


class BehaviorTreeNode {
public:
    BehaviorTreeNode() = default;
    virtual ~BehaviorTreeNode() = default; 
};

class Action : public BehaviorTreeNode {
public:
    Action() = default;
};


class Conditional : public BehaviorTreeNode {
public:
    Conditional() = default;
private:
};

#endif // BEHAVIOR_TREES_HPP