#include "headers/head.h"

using namespace std;

int test() {
    // Creation of a maze
    MazeBuilder mazeBuilderGenerated = KruskalAlgorithm().generate(10,10);

    std::shared_ptr<Graph> graph = mazeBuilderGenerated.getGraph();
    std::cout << "end " << &graph << std::endl;

    return 0;
}