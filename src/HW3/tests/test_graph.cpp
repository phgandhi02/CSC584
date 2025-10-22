#include <gtest/gtest.h>
/*
- Anything can be asserted as long as it can be streamed to an ostream object, in particular C-strings and string objects.

- Assertions are fatal and expects are non-fatal.

- Test() args go from general to specific. The first arg is the test suite name and the second arg is the test name.
*/

/*
Test Fixtures allow us to reuse the same configuration of objects for several different tests.

To create a fixture you must: derive a class from the testing::Test class and start the body of the class with the protected access specifier to enable the testing framework to create all the necessary member variables used for running a Test Fixture. The fixture should be the object name followed by Test (ie. GraphTest). The test fixture can be constructed and then member variables can hold the data that is to be tested and evaluated.

The rule of thumb is to use EXPECT_* when you want the test to continue to reveal more errors after the assertion failure, and use ASSERT_* when continuing after failure doesn’t make sense. For example, the second assertion in the Dequeue test is ASSERT_NE(n, nullptr), as we need to dereference the pointer n later, which would lead to a segfault when n is NULL.

*/
class GraphTest : public testing::Test
{
protected:
    int var1 = 0;
};

TEST_F(GraphTest, GraphFixtureTest){

};

/*
Graph Initization Test.


*/
TEST(Graph, GraphInitialization)
{
    EXPECT_EQ(0, 0);
}