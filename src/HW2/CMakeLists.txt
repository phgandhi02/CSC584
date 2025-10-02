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

file(GLOB_RECURSE STEERING_SOURCES "src/*.cpp")

# --- Create the SteeringLib Library ---
add_library(SteeringLib ${STEERING_SOURCES})
target_link_libraries(SteeringLib PRIVATE SFML::Graphics)
target_link_libraries(SteeringLib PRIVATE SFML::Window)

add_executable(main ./main.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_link_libraries(main PRIVATE SteeringLib)



# Make the library's headers in the 'include' folder available
target_include_directories(SteeringLib PUBLIC include)

# --- Create The Test Executable ---
add_executable(runTests tests/test_main.cpp)


# Link SteeringLib and gtest_main to the runTests program
target_link_libraries(runTests PRIVATE SteeringLib gtest_main SFML::Graphics SFML::Window)

# Automatically find all the tests in your test runner
gtest_discover_tests(runTests)