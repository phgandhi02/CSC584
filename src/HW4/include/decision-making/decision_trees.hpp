#ifndef DECISION_TREES_HPP
#define DECISION_TREES_HPP
/*
Decision Trees lib contains various recursive decision node objs that can be
used to construct a decision tree.
*/

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
    virtual DecisionTreeNode& makeDecision() = 0; 
};

/**
 * @brief Leaf node for Decision Tree. Action will return itself and terminate
 * decision tree node recursion.
 * 
 */
class Action : public DecisionTreeNode {
public:
    /**
     * @brief Terminates Decision Tree search and returns self.
     * 
     * @return DecisionTreeNode& 
     */
    DecisionTreeNode& makeDecision() override { return *this; }
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
    DecisionTreeNode& makeDecision() override {
        DecisionTreeNode& branch = getBranch();
        return branch.makeDecision();

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
    virtual bool testValue() = 0;
    /**
     * @brief Get the DecisionTreeNode based on the testValue() output
     * 
     * @return DecisionTreeNode& 
     */
    DecisionTreeNode& getBranch() {
        if (testValue()) {
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
    bool testValue() override { return (m_conditional)? true : false; }

private:
        bool m_conditional;
};

class FloatAboveDecision: public Decision {
public:
    FloatAboveDecision(float *checkVal, float threshold, DecisionTreeNode& trueNode, DecisionTreeNode& falseNode): Decision(trueNode,falseNode), m_gameState(*checkVal), m_threshold(threshold) {}
    ~FloatAboveDecision() = default;
    bool testValue() override { return (m_gameState > m_threshold)? true : false; }
private:
    float m_gameState;
    float m_threshold;
};
#endif // DECISION_TREES_HPP