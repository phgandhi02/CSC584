cmake_minimum_required(VERSION 3.28)
project(CSC584_HW4 LANGUAGES CXX)
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

file(GLOB_RECURSE DECISIONMAKING "src/*.cpp")

# --- Create the DecisionMakingLib Library ---
add_library(DecisionMakingLib ${DECISIONMAKING})
target_link_libraries(DecisionMakingLib PUBLIC SFML::Graphics)
target_link_libraries(DecisionMakingLib PUBLIC SFML::Window)

add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_link_libraries(main PRIVATE SFML::Window)
target_link_libraries(main PRIVATE DecisionMakingLib)

# Make the library's headers in the 'include' folder available
target_include_directories(DecisionMakingLib PUBLIC include)

file(GLOB_RECURSE TESTS "tests/*.cpp")

# --- Create The Test Executable ---
add_executable(test_main test_main.cpp)

# Link DecisionMakingLib and gtest_main to the runTests program
add_library(TestLib ${TESTS})
target_link_libraries(test_main PRIVATE DecisionMakingLib TestLib gtest_main)

# Automatically find all the tests in your test runner
gtest_discover_tests(test_main)