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

file(GLOB_RECURSE PATHFINDING "src/*.cpp")

# --- Create the PathfindingLib Library ---
add_library(PathfindingLib ${PATHFINDING})
target_link_libraries(PathfindingLib PUBLIC SFML::Graphics)
target_link_libraries(PathfindingLib PUBLIC SFML::Window)

add_executable(sfml_demo ./app/sfml_demo.cpp)
target_compile_features(sfml_demo PRIVATE cxx_std_11)
target_link_libraries(sfml_demo PRIVATE SFML::Graphics)
target_link_libraries(sfml_demo PRIVATE SFML::Window)
target_link_libraries(sfml_demo PRIVATE PathfindingLib)

add_executable(graph_analysis ./app/graph_analysis.cpp)
target_compile_features(graph_analysis PRIVATE cxx_std_11)
target_link_libraries(graph_analysis PRIVATE PathfindingLib)



# Make the library's headers in the 'include' folder available
target_include_directories(PathfindingLib PUBLIC include)

# --- Create The Test Executable ---
add_executable(test_graph tests/test_graph.cpp)


# Link PathfindingLib and gtest_main to the runTests program
target_link_libraries(test_graph PRIVATE PathfindingLib gtest_main)

# Automatically find all the tests in your test runner
gtest_discover_tests(test_graph)