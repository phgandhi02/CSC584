cmake_minimum_required(VERSION 3.28)
project(CSC584_HW4 LANGUAGES CXX)
enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS_INIT "-Werror -Wall -Wextra -Wpedantic")

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

file(GLOB_RECURSE MOVEMENT "src/movement/*.cpp")
file(GLOB_RECURSE PATHFINDING "src/pathfinding/*.cpp")
file(GLOB_RECURSE DECISIONMAKING "src/decision-making/*.cpp")


# --- Create the movement Library ---
add_library(movement ${MOVEMENT})
target_link_libraries(movement PRIVATE SFML::Graphics)
target_link_libraries(movement PRIVATE SFML::Window)

# --- Create the decision-making Library ---
add_library(pathfinding ${PATHFINDING})
target_link_libraries(pathfinding PRIVATE SFML::Graphics)

# --- Create the decision-making Library ---
add_library(decision-making ${DECISIONMAKING})
target_link_libraries(decision-making PRIVATE SFML::Graphics)
target_link_libraries(decision-making PRIVATE SFML::System)


add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_link_libraries(main PRIVATE SFML::System)
target_link_libraries(main PRIVATE SFML::Window)
target_link_libraries(main PRIVATE movement)
target_link_libraries(main PRIVATE pathfinding)
target_link_libraries(main PRIVATE decision-making)

# Make the library's headers in the 'include' folder available
target_include_directories(movement PUBLIC include)
target_include_directories(pathfinding PUBLIC include)
target_include_directories(decision-making PUBLIC include)

file(GLOB_RECURSE TESTS "tests/*.cpp")


# Link decision-making and gtest_main to the runTests program
add_library(TestLib ${TESTS})
target_link_libraries(TestLib PUBLIC SFML::Graphics SFML::Window)

# --- Create The Test Executable ---
add_executable(main_test main_test.cpp)
target_link_libraries(main_test PRIVATE decision-making TestLib gtest_main)


# Automatically find all the tests in your test runner
gtest_discover_tests(main_test)