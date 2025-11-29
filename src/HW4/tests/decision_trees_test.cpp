#include "../include/decision-making/decision_trees.hpp"
#include <gtest/gtest.h>

/**
 * @brief Test class of DecisionTreeNode
 * @brief Abstract recursive data struct for Decision Trees.
 */
class TestDecisionTreeNode: public DecisionTreeNode
{
public:
    /**
     * @brief Construct a new Test Decision Tree Node object
     */
    TestDecisionTreeNode() = default;
    /**
     * @brief Destroy the Test Decision Tree Node object
     */
    ~TestDecisionTreeNode() = default;
    /**
     * @brief Wrapper around DecisionTreeNode for unittesting.
     * 
     * @return DecisionTreeNode& 
     */
    DecisionTreeNode& makeDecision() override {return *this;} // return pointer to this object to return an address. This is how we pass a reference back. 
};

// test the DecisionTreeNode constructor
TEST(DecisionTreeNodeTest,ConstructNode)
{
    // Arrange
    auto node = TestDecisionTreeNode();
    // Act
    auto nodeAddress = &node.makeDecision();
    // Assert
    EXPECT_EQ(&node, nodeAddress);
}

// test the DecisionTreeNode constructor
TEST(ActionNodeTest,ConstructNode)
{
    // Arrange
    auto node = Action();
    // Act
    auto nodeAddress = &node.makeDecision();
    
    // Assert
    EXPECT_EQ(&node, nodeAddress);
}

