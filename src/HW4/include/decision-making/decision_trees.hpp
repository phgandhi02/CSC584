/*
Decision Trees lib contains various recursive decision node objs that can be
used to construct a decision tree.
*/
#ifndef DECISION_TREES_HPP
#define DECISION_TREES_HPP

#include "game_state.hpp"

/**
 * @class DecisionTreeNode
 * @brief Abstract recursive data struct for Decision Trees.
 * 
 */
class DecisionTreeNode {
public:
    /**
     * @brief base c'tor for DecisionTreeNode. Override with subclass c'tor.
     * 
     */
    DecisionTreeNode() = default;
    // base d'tor for DecisionTreeNode. Override with subclass d'tor.
    virtual ~DecisionTreeNode() = default;
    // abstract method for all decision tree node types. 
    virtual DecisionTreeNode& makeDecision(DecisionContext context) = 0; 
};

/**
 * @brief Leaf node for Decision Tree. Action will return itself and terminate
 * decision tree node recursion.
 * 
 */
class Action : public DecisionTreeNode {
public:
    Action() = default;
    ~Action() = default;
    /**
     * @brief Terminates Decision Tree search and returns self.
     * 
     * @return DecisionTreeNode& 
     */
    DecisionTreeNode& makeDecision(DecisionContext context) override { return *this; }
};

/**
 * @brief Decision node for Decision Tree. Will return a branch based on test conditional and then recurse on the selected node.
 * 
 */
class Decision : public DecisionTreeNode {
public:
    /**
     * @brief Selects appropriate branch based on test value and recurses makeDecision func on that node.
     * 
     * @return DecisionTreeNode& 
     */
    Decision(DecisionTreeNode& trueBranch,DecisionTreeNode& falseBranch): 
        trueNode(trueBranch), falseNode(falseBranch) {}; 
    DecisionTreeNode& makeDecision(DecisionContext context) override {
        DecisionTreeNode& branch = getBranch(context);
        return branch.makeDecision(context);

    };
private:
    /**
     * @brief Branch if test value is true
     * 
     */
    DecisionTreeNode& trueNode;
    /**
     * @brief Branch if test value is false.
     * 
     */
    DecisionTreeNode& falseNode;
    /**
     * @brief Checks if the testValue is true
     * 
     * @return true: this will return the trueNode branch.
     * @return false: this will return the falseNode branch.
     */
    virtual bool testValue(DecisionContext context) = 0;
    /**
     * @brief Get the DecisionTreeNode based on the testValue() output
     * 
     * @return DecisionTreeNode& 
     */
    DecisionTreeNode& getBranch(DecisionContext context) {
        if (testValue(context)) {
            return trueNode;
        } else {
            return falseNode;
        }
    }
};

class BinaryDecision: public Decision {
public:
    BinaryDecision(bool conditional, DecisionTreeNode& trueNode, DecisionTreeNode& falseNode): Decision(trueNode,falseNode), m_conditional(conditional) {}
    ~BinaryDecision() = default;
    bool testValue(DecisionContext context) override { return (m_conditional)? true : false; }

private:
        bool m_conditional;
};

class isCloseProximityDecision: public Decision {
public:
    isCloseProximityDecision(float threshold, DecisionTreeNode& trueNode, DecisionTreeNode& falseNode): Decision(trueNode,falseNode), m_threshold(threshold) {}
    ~isCloseProximityDecision() = default;
    bool testValue(DecisionContext context) override { return (context.gameState.getDistance() < m_threshold)? true : false; }
private:
    float m_threshold;
};


class WanderSteeringAction: public Action {
public:
    WanderSteeringAction() = default;
    ~WanderSteeringAction() = default;
    DecisionTreeNode& makeDecision(DecisionContext context) override 
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
    DecisionTreeNode& makeDecision(DecisionContext context) override 
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
     * TODO: need to test whether algo is planning when the player has shifted from the original plan or when the boid has shifted from the path.
     * @param context: DecisionContext obj
     * @return DecisionTreeNode& 
     */
    DecisionTreeNode& makeDecision(DecisionContext context) override 
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
    DecisionTreeNode& makeDecision(DecisionContext context) override 
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
#endif // DECISION_TREES_HPP