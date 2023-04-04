cmake_minimum_required(VERSION 3.22.1)
project(mazelib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../target)

add_compile_options(
        -Wall
        -Wextra
        -pedantic
        -Wno-unused-parameter
        -Wno-unused-variable
        -Wno-unused-function
        -Wno-missing-field-initializers
)

add_executable(mazelib
        src/main.cpp
        src/image/Image.cpp
        src/graph/Graph.cpp
        src/maze/Maze.cpp
        src/algorithms/Algorithm.cpp
        src/algorithms/type/KruskalAlgorithm.cpp
        src/algorithms/type/DepthFirstSearchAlgorithm.cpp
        src/method/Method.cpp
        src/method/type/ImageSavingMethod.cpp
        src/method/type/TextFileLoadingMethod.cpp
        src/method/type/TextFileSavingMethod.cpp
        src/headers/Expected.h src/example.cpp src/interface/Interface.cpp src/interface/Interface.h src/algorithms/type/BreadthFirstSearchAlgorithm.cpp src/algorithms/type/TremauxsAlgorithm.cpp src/algorithms/type/WallFollowingAlgorithm.cpp src/algorithms/type/DijkstraAlgorithm.cpp src/algorithms/type/LeeAlgorithm.cpp)
