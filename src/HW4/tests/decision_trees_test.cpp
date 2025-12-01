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

/**
 * @brief Test class of DecisionTreeNode
 * @brief Abstract recursive data struct for Decision Trees.
 */
class TestDecision: public Decision
{
public:
    /**
     * @brief Construct a new Test Decision object
     * 
     * @param trueBranch DT node selected if testValue is true
     * @param falseBranch DT node selected if testValue is false
     * @param selectTrue `TESTING_ONLY` if true then true node is selected.
     */
    TestDecision(DecisionTreeNode& trueBranch,DecisionTreeNode& falseBranch, bool selectTrue): 
        Decision(trueBranch,falseBranch), selectedBranch(selectTrue) {}; 
    /**
     * @brief Destroy the Test Decision Tree Node object
     */
    ~TestDecision() = default;
    bool testValue() override {return selectedBranch;}
    bool selectedBranch;
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

TEST(DecisionNodeTest,MakeTrueDecision)
{
    // Arrange
    auto trueNode = Action();
    auto falseNode = Action();
    auto node = TestDecision(trueNode,falseNode, true);
    // Act
    auto nodeAddress = &node.makeDecision();

    // Assert
    EXPECT_EQ(&trueNode,nodeAddress);
}

TEST(DecisionNodeTest,MakeFalseDecision)
{
    // Arrange
    auto trueNode = Action();
    auto falseNode = Action();
    auto node = TestDecision(trueNode,falseNode, false);
    // Act
    auto nodeAddress = &node.makeDecision();

    // Assert
    EXPECT_EQ(&falseNode,nodeAddress);
}

TEST(FloatAboveDecisionTest,MakeTrueDecision)
{
    // Arrange
    auto trueNode = Action();
    auto falseNode = Action();
    float gameState = 0.5;
    float *p_gameState = &gameState;
    auto node = FloatAboveDecision(p_gameState,.2,trueNode,falseNode);
    // Act
    auto nodeAddress = &node.makeDecision();

    // Assert
    EXPECT_EQ(&trueNode,nodeAddress);
}

TEST(FloatAboveDecisionTest,MakeFalseDecision)
{
    // Arrange
    auto trueNode = Action();
    auto falseNode = Action();
    float gameState = 0.1;
    float *p_gameState = &gameState;
    auto node = FloatAboveDecision(p_gameState,.2,trueNode,falseNode);
    // Act
    auto nodeAddress = &node.makeDecision();

    // Assert
    EXPECT_EQ(&falseNode,nodeAddress);
};

TEST(ComplexDecisionTree, MakeCorrectDecision)
{
    /**
     * @brief Testing a complex decision tree. This decision tree will have more than one decision node and it will need to evaluate to the correct node.
     * root -> decision_1 -> leafNodeA
     *                    -> leafNodeB
     *      -> decision_2 -> leafNodeC
     *                    -> leafNodeD
     * select True -> false, therefore leafNodeB          
     */ 
    // leaf nodes of the decision tree

    // Arrange
    // create leaf nodes for DT
    auto leafNodeA = Action(); 
    auto leafNodeB = Action();
    auto leafNodeC = Action();
    auto leafNodeD = Action();
    // create logic for DT
    bool root_bool_val = (1 > 0);  // true
    bool second_bool_val = (0 > 1); // false
    // create nodes for DT
    auto decision_1 = BinaryDecision(second_bool_val, leafNodeA,leafNodeB);
    auto decision_2 = BinaryDecision(!second_bool_val, leafNodeC,leafNodeD);
    auto root = BinaryDecision(root_bool_val, decision_1, decision_2);

    // Act
    auto nodeAddress = &root.makeDecision();

    // Assert
    EXPECT_EQ(&leafNodeB,nodeAddress);
}