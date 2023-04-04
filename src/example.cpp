#include "headers/head.h"

using namespace std;

int example() {
    // Creation of a maze
    MazeBuilder mazeBuilderGenerated = KruskalAlgorithm(time(nullptr)).generate(10,10);
    mazeBuilderGenerated.setStart({0,0});
    mazeBuilderGenerated.setEnd({mazeBuilderGenerated.getWidth() - 1,mazeBuilderGenerated.getHeight() - 1});
    mazeBuilderGenerated.setPathWidth(30);
    mazeBuilderGenerated.setWallWidth(3);

    // Building the maze
    Maze mazeGenerated = mazeBuilderGenerated.build();

    // Exporting the maze to a file
    TextFileSavingMethod().save(mazeGenerated,"maze.txt");

    // Exporting the maze to an image
    ImageSavingMethod().save(mazeGenerated,"maze.png");

    // Loading a maze from a file
    Expected<MazeBuilder> mazeBuilderLoaded = TextFileLoadingMethod().load("maze.txt");

    // Checking for errors
    if (mazeBuilderLoaded.hasError()) {
        cout << "Error: " << mazeBuilderLoaded.error() << endl;
        return 1;
    }

    // Solving the maze
    MazePath generatedPath = DepthFirstSearchAlgorithm().solve(mazeGenerated);

    // Exporting the maze to a file with the path
    TextFileSavingMethod().save(mazeGenerated,"mazePath.txt",generatedPath);

    // Exporting the maze to an image with the path
    ImageSavingMethod().save(mazeGenerated,"mazePath.png",generatedPath);

}