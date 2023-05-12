#include "maze/Maze.h"
#include "algorithms/Algorithm.h"
#include "method/Method.h"

using namespace std;

void example() {

    // Creation of a maze
    MazeBuilder builder = KruskalAlgorithm(time(nullptr)).generate(10, 10);
    builder.setPathWidth(30);
    builder.setWallWidth(3);

    // Building the maze
    Maze maze = builder.build();

    // Exporting the maze to a file
    TextFileSavingMethod().save(maze, "maze.txt");

    // Exporting the maze to an image
    ImageSavingMethod().save(maze, "maze.png");

    // --------------------------------

    // Loading a maze from a file
    Expected<MazeBuilder> loaded = TextFileLoadingMethod().load("maze.txt");

    // Checking for errors
    if (loaded.hasError()) {
        cout << "Error: " << loaded.error() << endl;
        return;
    } else {
        builder = loaded.value();
        maze = builder.build();
    }

    // Solving the maze
    MazePath path = DepthFirstSearchAlgorithm().solve(maze);

    // Exporting the maze to a file with the path
    TextFileSavingMethod().save(maze, "mazePath.txt", path);

    // Exporting the maze to an image with the path
    ImageSavingMethod().save(maze, "mazePath.png", path);
}