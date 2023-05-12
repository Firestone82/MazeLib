<img width="15%" src="assets/icon.png" align="right" alt="Icon">

# Project for C++ (Maze Library API/CLI) 

<p>
    <img alt="Testing" src="https://github.com/Firestone82/MazeLib/actions/workflows/cmake.yml/badge.svg">
    <img alt="License" src="https://img.shields.io/github/license/Firestone82/MazeLib">
    <img alt="GitHub issues" src="https://img.shields.io/github/issues/Firestone82/MazeLib">
</p>

- Author: Pavel Mikula (MIK0486)
- Took approximately 78 hours

## Project Theme
The project will focus on generating and solving mazes. It will be divided into two parts for processing. 
The first part will be more focused on logic, which will be an API/CLI written in C++. 
This API or CLI will accept user input data and create and solve mazes based on the parameters. 
The second part of the project will focus more on graphics in Python. 
The graphical GUI will serve as the interface for the API and will also be used in the URO subject.

## Logical Part of the Project (API/CLI)
This part will operate the following functions:
 - Creating a maze using a specified algorithm
   - Saving to a file or image
 - Solving a maze using a specified algorithm
   - Loading input from a file
   - Saving to a file or image
 - Finding the fastest algorithm for solving a maze
   - Outputting a table of results
 - Listing all available algorithms

## Graphical Part of the Project (GUI)
The graphical part of the project, written in Python, will use the tkinter library and 
libraries from the first part of the project to connect user interfaces with graphics. 
The application will send requests to the API and render their outputs on the screen.

## API Architecture
Important classes for work:
 - Maze (Class for storing a maze)
 - Algorithm (Class for utilizing an algorithm)
   - GeneratingAlgorithm (Subclass for generating algorithms)
   - SolvingAlgorithm (Subclass for solving algorithms)
 - Graph (Class for storing maze content)
   - Node (Subclass for storing maze cell)
 - Image (Class for exporting maze to an image)
 - Interface (Class for storing the interface)
 - Method (Class for saving or loading maze)
 - Bind (Class for binding methods into python)

## Requirements:
- C++17
- CMake 3.22.1+
- Python 3.9.7+ (for GUI)

## Installation
```shell
# Clone the repository
git clone https://github.com/Firestone82/MazeLib.git
cd MazeLib

# Building as C++ CLI
mkdir build && cd build

# Build the project
cmake .. && make -j

# Build the project
pip install -r ../requirements.txt && pip install ..
```

## Images
Example maze output:

<p align="center">
    <img src="assets/maze.png" alt="Not Solved Maze Image"> 
    &nbsp;
    &nbsp;
    &nbsp;
    <img src="assets/mazeSolved.png" alt="Solved Maze Image"> 
</p>

## CLI Usage
<details open>
<summary>Click to show help CLI</summary>

```
 __  __               _      _ _
|  \/  |             | |    (_) |
| \  / | __ _ _______| |     _| |__
| |\/| |/ _` |_  / _ \ |    | | '_ \
| |  | | (_| |/ /  __/ |____| | |_) |
|_|  |_|\__,_/___\___|______|_|_.__/
Author: Pavel Mikula (MIK0486)

Format: mazelib <cmd> [options]

Commands:
  help                           | Show program help message (this)
  version, ver                   | Show programs version number
  generate, gen                  | Generate maze to file or image
  solve                          | Solve maze from file or image
  test                           | Test algorithms
  algorithms, algs, algos        | Show available algorithms

Options:
  -h, --help      | Show this help message and exit          | [boolean]
  -v, --version   | Show programs version number and exit    | [boolean]
```
</details>

<details>
<summary>Click to show generate CLI</summary>

```
Command: mazelib generate [options]

Options:
  -w, --width           | Width of maze                                     REQUIRED | [int]
  -h, --height          | Height of maze                                    REQUIRED | [int]
  -a, --algorithm       | Algorithm to generate maze                        REQUIRED | [string]
  -se, --seed           | Seed of the maze                                           | [double]
  -s, --start           | Start position of maze                                     | [int] [int]
  -e, --end             | End position of maze                                       | [int] [int]
  -pw, --pathWidth      | Width of the path between walls                            | [int]
  -ww, --wallWidth      | Width of wall between paths                                | [int]
  -f, --file            | Path to the file, where maze will be saved                 | [string]
  -i, --image           | Path to the image, where maze will be saved                | [string]
```
</details>

<details>
<summary>Click to show solve CLI</summary>

```
Command: mazelib solve [options]

Options:
  -fi, --fileIn         | Path to the input file of maze                    REQUIRED | [string]
  -a, --algorithm       | Algorithm to solve maze                           REQUIRED | [string]
  -s, --start           | Start position of maze                                     | [int] [int]
  -e, --end             | End position of maze                                       | [int] [int]
  -fo, --fileOut        | Path to the file, where maze will be saved                 | [string]
  -i, --image           | Path to the image, where maze will be saved                | [string]
```
</details>

<details>
<summary>Click to show test CLI</summary>

```
Command: mazelib test [options]

Options:
  -fi, --fileIn         | Path to the file, from which maze will be loaded  REQUIRED | [string]
  -a, --algorithm       | Algorithms to test, separated by commas                    | [string]
  -fo, --fileOut        | Path to the file, where maze will be saved                 | [string]
  -t, --table           | Output results printed in table                            |
```
</details>

<details>
<summary>Click to show algorithms CLI</summary>

```
Command: mazelib algorithms

Options:
  -o, --order           | Order of algorithms                                        | [string]
  -t, --type            | Type of algorithms                                         | [string]
  -d, --description     | Hide description of algorithms                             |
```
</details>

## API Usage
<details open>
<summary>Click to show example </summary>

```cpp
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
```
</details>
