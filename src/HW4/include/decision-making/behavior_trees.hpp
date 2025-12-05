/*
Decision Trees lib contains various recursive decision node objs that can be
used to construct a decision tree.
*/
#ifndef BEHAVIOR_TREES_HPP
#define BEHAVIOR_TREES_HPP

#include <iostream>
#include "game_state.hpp"

enum Status {
    FAIL,
    SUCCESS,
    RUNNING
};

/**
 * @class BehaviorTreeNode
 * @brief Abstract recursive data struct for Behavior Trees.
 * 
 */
class BehaviorTreeNode {
public:
    // base d'tor for BehaviorTreeNode. Override with subclass d'tor.
    virtual ~BehaviorTreeNode() = default;
    // abstract method for all decision tree node types. 
    virtual Status run(DecisionContext context) = 0; 
};

// BTNode that will return SUCCESS if any children return success 
class Selector : public BehaviorTreeNode {
public:
    // Add child to Selector Task.
    void addChild(std::unique_ptr<BehaviorTreeNode> child) {
        if (child)
            m_children.push_back(std::move(child));
        else
            std::cout << "Child NULL" << std::endl;
    }
    Status run(DecisionContext context);
private:
    std::vector<std::unique_ptr<BehaviorTreeNode>> m_children;
};

// BTNode that will return SUCCESS only if all children return success 
class Sequence : public BehaviorTreeNode {
public:
    // Add child to Selector Task.
    void addChild(std::unique_ptr<BehaviorTreeNode> child) {
        if (child)
            m_children.push_back(std::move(child));
        else
            std::cout << "Child NULL" << std::endl;
    }
    Status run(DecisionContext context);
private:
    std::vector<std::unique_ptr<BehaviorTreeNode>> m_children;
};

#endif // BEHAVIOR_TREES_HPP