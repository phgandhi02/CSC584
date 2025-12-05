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

/**
 * @brief Decision node for Decision Tree. Will return a branch based on test conditional and then recurse on the selected node.
 * 
 */
class Decision : public BehaviorTreeNode {
public:
    /**
     * @brief Selects appropriate branch based on test value and recurses makeDecision func on that node.
     * 
     * @return BehaviorTreeNode& 
     */
    Decision(BehaviorTreeNode& trueBranch,BehaviorTreeNode& falseBranch): 
        trueNode(trueBranch), falseNode(falseBranch) {}; 
    BehaviorTreeNode& makeDecision(DecisionContext context) override {
        BehaviorTreeNode& branch = getBranch(context);
        return branch.makeDecision(context);

    };
private:
    /**
     * @brief Branch if test value is true
     * 
     */
    BehaviorTreeNode& trueNode;
    /**
     * @brief Branch if test value is false.
     * 
     */
    BehaviorTreeNode& falseNode;
    /**
     * @brief Checks if the testValue is true
     * 
     * @return true: this will return the trueNode branch.
     * @return false: this will return the falseNode branch.
     */
    virtual bool testValue(DecisionContext context) = 0;
    /**
     * @brief Get the BehaviorTreeNode based on the testValue() output
     * 
     * @return BehaviorTreeNode& 
     */
    BehaviorTreeNode& getBranch(DecisionContext context) {
        if (testValue(context)) {
            return trueNode;
        } else {
            return falseNode;
        }
    }
};

class BinaryDecision: public Decision {
public:
    BinaryDecision(bool conditional, BehaviorTreeNode& trueNode, BehaviorTreeNode& falseNode): Decision(trueNode,falseNode), m_conditional(conditional) {}
    ~BinaryDecision() = default;
    bool testValue(DecisionContext context) override { return (m_conditional)? true : false; }

private:
        bool m_conditional;
};

class isCloseProximityDecision: public Decision {
public:
    isCloseProximityDecision(float threshold, BehaviorTreeNode& trueNode, BehaviorTreeNode& falseNode): Decision(trueNode,falseNode), m_threshold(threshold) {}
    ~isCloseProximityDecision() = default;
    bool testValue(DecisionContext context) override { return (context.gameState.getDistance() < m_threshold)? true : false; }
private:
    float m_threshold;
};


class WanderSteeringAction: public Action {
public:
    WanderSteeringAction() = default;
    ~WanderSteeringAction() = default;
    BehaviorTreeNode& makeDecision(DecisionContext context) override 
    {
        auto enemySeekBehavior = std::make_unique<KinematicWander>();
        if (!(context.boid.controller == enemySeekBehavior))
        {
            context.boid.controller = std::move(enemySeekBehavior);
        }
        return *this;
    }
};

class SeekSteeringAction: public Action {
public:
    SeekSteeringAction() = default;
    ~SeekSteeringAction() = default;
    BehaviorTreeNode& makeDecision(DecisionContext context) override 
    {
        auto enemySeekBehavior = std::make_unique<KinematicSeek>();
        if (!(context.boid.controller == enemySeekBehavior))
        {
            context.boid.controller = std::move(enemySeekBehavior);
        }
        
        context.boid.setTarget(context.gameState.getPlayer()); 
        return *this;
    }
};


class PathfindPlayerAction: public Action {
public:
    PathfindPlayerAction() = default;
    ~PathfindPlayerAction() = default;
    /**
     * @brief Action to Pathfind to player
     * ! need to handle cases to make sure the enemy is on a valid node.
     * @param context: DecisionContext obj
     * @return BehaviorTreeNode& 
     */
    BehaviorTreeNode& makeDecision(DecisionContext context) override 
    {
        auto enemyPos = context.gameState.getEnemyCatPos();
        auto playerPos = context.gameState.getPlayerPos();

        if (!m_path.empty())
        {
            if (m_path.front().getToNode() != calcNodeIndex(playerPos))
                { m_path = std::vector<Connection>{}; }
            else if (m_path.back().getFromNode() != calcNodeIndex(enemyPos))
                m_path = std::vector<Connection>{};
        }

        if (m_path.empty() && context.gameState.getGraph().getNodes(calcNodeIndex(playerPos)).size() >= 1) 
        {
            m_path = context.gameState.getPath(enemyPos,playerPos);
            if (!m_path.empty())
                context.gameState.followPath(m_path, context.boid);
        } else // continue following existing path
            context.gameState.followPath(m_path, context.boid);
        return *this;
    }
    std::vector<Connection> m_path;
};

class RandomPathfindAction: public Action {
public:
    RandomPathfindAction() = default;
    ~RandomPathfindAction() = default;
    BehaviorTreeNode& makeDecision(DecisionContext context) override 
    {
        auto enemyPos = context.gameState.getEnemyCatPos();
        auto random_position = sf::Vector2f(m_rng.getRandomInt(), m_rng.getRandomInt());
        if (m_path.empty()) 
        {
            while (context.gameState.getGraph().getNodes(calcNodeIndex(random_position)).size() >= 1)
            {
                random_position = sf::Vector2f(m_rng.getRandomInt(), m_rng.getRandomInt());
            }

            m_path = context.gameState.getPath(enemyPos,random_position);
        } else // continue following existing path
            context.gameState.followPath(m_path, context.boid);

        return *this;
    }
    std::vector<Connection> m_path;
    RandomNumGen m_rng = RandomNumGen(40, 760);
};
#endif // BEHAVIOR_TREES_HPP