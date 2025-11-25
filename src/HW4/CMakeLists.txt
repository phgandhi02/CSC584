cmake_minimum_required(VERSION 3.28)
project(CSC584_HW2 LANGUAGES CXX)
enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(GoogleTest)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.x
    GIT_SHALLOW ON
    )
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE DECISION_MAKING "src/*.cpp")

# --- Create the DecisionMakingLib Library ---
add_library(DecisionMakingLib ${DECISION_MAKING})
target_link_libraries(DecisionMakingLib PUBLIC SFML::Graphics)
target_link_libraries(DecisionMakingLib PUBLIC SFML::Window)

add_executable(<new-exe-name> <replace-with-new-exe>)
target_compile_features(<new-exe-name> PRIVATE cxx_std_11)
target_link_libraries(<new-exe-name> PRIVATE SFML::Graphics)
target_link_libraries(<new-exe-name> PRIVATE SFML::Window)
target_link_libraries(<new-exe-name> PRIVATE DecisionMakingLib)

# Make the library's headers in the 'include' folder available
target_include_directories(DecisionMakingLib PUBLIC include)

# --- Create The Test Executable ---
add_executable(test_graph tests/test_graph.cpp)


# Link DecisionMakingLib and gtest_main to the runTests program
target_link_libraries(test_graph PRIVATE DecisionMakingLib gtest_main)

# Automatically find all the tests in your test runner
gtest_discover_tests(test_graph)