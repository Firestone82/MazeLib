#include "headers/head.h"

using namespace std;

int example() {
    int status = 0;

    MazeBuilder mazeBuilderGenerated = KruskalAlgorithm(time(nullptr)).generate(10,10);
    mazeBuilderGenerated.setStart({0,0});
    mazeBuilderGenerated.setEnd({mazeBuilderGenerated.getWidth() - 1,mazeBuilderGenerated.getHeight() - 1});
    mazeBuilderGenerated.setPathWidth(30);
    mazeBuilderGenerated.setWallWidth(3);

    Maze mazeGenerated = mazeBuilderGenerated.build();
    status = TextFileSavingMethod().save(mazeGenerated,"maze.txt").valueOr(1);

    cout << " Saved maze to file: " << "maze.txt" << endl;
    cout << "  - Status:          " << (status == 0 ? "Saved" : "Error") << endl;                                                 // Returns "Saved", "Error"
    cout << "  - Created with:    " << mazeGenerated.getGenerationAlgorithm() << endl;                                            // Returns "Kruskal"
    cout << "  - Creation time    " << mazeGenerated.getGenerationTime() << "ms" << endl;                                         // Returns time in milliseconds
    cout << "  - Seed:            " << mazeGenerated.getSeed() << endl;                                                           // Returns "0
    cout << "  - Maze dimensions: " << mazeGenerated.getWidth() << "x" << mazeGenerated.getHeight() << endl;                      // Returns "10x10"
    cout << "  - Path width:      " << mazeGenerated.getPathWidth() << endl;                                                      // Returns "10"
    cout << "  - Wall width:      " << mazeGenerated.getWallWidth() << endl;                                                      // Returns "10"
    cout << "  - Start coords:    " << get<0>(mazeGenerated.getStart()) << "," << get<1>(mazeGenerated.getStart()) << endl; // Returns "0,0"
    cout << "  - End coords:      " << get<0>(mazeGenerated.getEnd()) << "," << get<1>(mazeGenerated.getEnd()) << endl;     // Returns "0,0"
    cout << "" << endl;

    status = ImageSavingMethod().save(mazeGenerated,"maze.png").valueOr(1);

    cout << " Saved image to file: " << "maze.png" << endl;
    cout << "  - Status:           " << (status == 0 ? "Saved" : "Error") << endl; // Returns "Solved", "Error"
    cout << "" << endl;

    MazePath generatedPath = RecursiveBacktrackerAlgorithm().solve(mazeGenerated);
    status = TextFileSavingMethod().save(mazeGenerated,"mazePath.txt",generatedPath).valueOr(1);

    cout << " Saved path to file:     " << "mazePath.txt" << endl;
    cout << "  - Status:              " << (status == 0 ? "Saved" : "Error") << endl;      // Returns "Saved", "Error"
    cout << "  - Solved with:         " << generatedPath.getSolvingAlgorithm() << endl;    // Returns "RecursiveBacktracker"
    cout << "  - Solving time         " << generatedPath.getSolvingTime() << "ms" << endl; // Returns time in milliseconds
    cout << "  - Path length:         " << generatedPath.getLength() << endl;              // Returns length of path
    cout << "  - Amount of junctions: " << generatedPath.getJunctionCount() << endl;       // Returns amount of junctions
    cout << "" << endl;

    status = ImageSavingMethod().save(mazeGenerated,"mazePath.png",generatedPath).valueOr(1);

    cout << " Saved image to file: " << "mazePath.png" << endl;
    cout << "  - Status:           " << (status == 0 ? "Saved" : "Error") << endl; // Returns "Saved", "Error"
    cout << "" << endl;

    // --------------------------------

    MazeBuilder mazeBuilderLoaded = TextFileLoadingMethod().load("maze.txt");
    Maze mazeLoaded = mazeBuilderGenerated.build();

    cout << " Loaded maze from file: " << "maze.txt" << endl;
    cout << "  - Status:          " << (status == 0 ? "Loaded" : "Error") << endl;                                             // Returns "Loaded", "Error"
    cout << "  - Created with:    " << mazeLoaded.getGenerationAlgorithm() << endl;                                            // Returns "Kruskal"
    cout << "  - Creation time    " << mazeLoaded.getGenerationTime() << "ms" << endl;                                         // Returns time in milliseconds
    cout << "  - Seed:            " << mazeLoaded.getSeed() << endl;                                                           // Returns "0
    cout << "  - Maze dimensions: " << mazeLoaded.getWidth() << "x" << mazeLoaded.getHeight() << endl;                         // Returns "10x10"
    cout << "  - Path width:      " << mazeLoaded.getPathWidth() << endl;                                                      // Returns "10"
    cout << "  - Wall width:      " << mazeLoaded.getWallWidth() << endl;                                                      // Returns "10"
    cout << "  - Start coords:    " << get<0>(mazeLoaded.getStart()) << "," << get<1>(mazeLoaded.getStart()) << endl;    // Returns "0,0"
    cout << "  - End coords:      " << get<0>(mazeLoaded.getEnd()) << "," << get<1>(mazeLoaded.getEnd()) << endl;        // Returns "0,0"
    cout << "" << endl;

    Expected<MazeBuilder> loader = TextFileLoadingMethod().load("mazeFailed.txt");

    if (loader.hasError()) {
        cout << " Failed to load maze from file: " << "mazeFailed.txt" << endl;
        cout << "  - Error: " << loader.error() << endl;
        cout << "" << endl;
    }

    return 0;
}