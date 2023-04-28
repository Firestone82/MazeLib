cmake_minimum_required(VERSION 3.22.1)
project(mazelib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../target)

option(DISABLE_ASAN "Do not use Address sanitizer" OFF)

#if(DISABLE_ASAN)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#endif()

include_directories(C:/Users/Pavel/AppData/Local/Msys2/mingw64/include/python3.10)
link_directories(C:/Users/Pavel/AppData/Local/Msys2/mingw64/lib/python3.10)

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
        src/example.cpp
        src/image/Image.cpp
        src/graph/Graph.cpp
        src/maze/Maze.cpp
        src/interface/Interface.cpp
        src/algorithms/Algorithm.cpp
        src/algorithms/type/KruskalAlgorithm.cpp
        src/algorithms/type/DepthFirstSearchAlgorithm.cpp
        src/method/Method.cpp
        src/method/type/ImageSavingMethod.cpp
        src/method/type/TextFileLoadingMethod.cpp
        src/method/type/TextFileSavingMethod.cpp
        src/method/type/ImageMemoryMethod.cpp
        src/algorithms/type/BreadthFirstSearchAlgorithm.cpp
        src/algorithms/type/TremauxsAlgorithm.cpp
        src/algorithms/type/WallFollowingAlgorithm.cpp
        src/algorithms/type/DijkstraAlgorithm.cpp
        src/algorithms/type/LeeAlgorithm.cpp
        src/test.cpp)

#find_package(Python 3.6 COMPONENTS Interpreter Development REQUIRED)
#find_package(pybind11 CONFIG REQUIRED)
#
#pybind11_add_module(mazeLibAPI
#        src/pybind/test.cpp,
#        src/pybind/bind.cpp
#)



