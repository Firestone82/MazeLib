# MazeLib

> **VŠB-TUO** — School project · Programming in C++

![C++](https://img.shields.io/badge/C%2B%2B-17-blue) ![Python](https://img.shields.io/badge/Python-3.9%2B-yellow) ![CMake](https://img.shields.io/badge/CMake-3.22%2B-blue)

## About

A C++ maze generation and solving library with a command-line interface, programmatic API, and Python bindings. Mazes can be exported as PNG images or serialized to disk for later use. The Python bindings power the companion [MazeLib-GUI](https://github.com/Firestone82/MazeLib-GUI) tkinter application.

## Features

**Generation algorithms:** Depth-first search (recursive backtracker), Kruskal's

**Solving algorithms:** BFS, DFS, Dijkstra, Lee, Tremaux, Wall-following

**Output:** PNG image export, binary file serialization

**Interfaces:** CLI, C++ API, Python bindings

## Requirements

- C++17 compiler and CMake 3.22.1+
- Python 3.9+ and pip *(for Python bindings and GUI)*

## Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/Firestone82/MazeLib.git
   cd MazeLib
   ```

2. Build the C++ library and CLI:
   ```bash
   mkdir build && cd build
   cmake ..
   make -j$(nproc)
   cd ..
   ```

3. *(Optional)* Install Python bindings (required for MazeLib-GUI):
   ```bash
   pip install -r requirements.txt
   pip install .
   ```

## Usage

```bash
# Generate a 20×20 maze and save it
./build/mazelib generate --width 20 --height 20 --algorithm dfs --output maze.dat

# Solve a saved maze
./build/mazelib solve --file maze.dat --algorithm dijkstra

# Export a maze as a PNG image
./build/mazelib generate --width 30 --height 30 --algorithm kruskal --image maze.png

# Benchmark all algorithms on a 50×50 maze
./build/mazelib test --width 50 --height 50

# List available algorithms
./build/mazelib list
```

## License

This project was created as a school assignment at VŠB-TUO.
