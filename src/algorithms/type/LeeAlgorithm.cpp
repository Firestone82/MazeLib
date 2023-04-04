#include "../../headers/Head.h"

using namespace std;

#define DESCRIPTION "Lee Algorithm, also known as Breadth-First Search Algorithm, finds the shortest path between two points in a maze or a grid. It starts at the starting point, visits neighbors, and marks them with a distance. The algorithm maintains a queue of cells to be visited, adding neighbors that haven't been visited yet. The time and space complexity of Lee Algorithm is O(N), where N is the number of cells in the grid. It only works on grids with cells of the same size and movement in four directions (up, down, left, right)."
#define COMPLEXITY "O(N)"

LeeAlgorithm::LeeAlgorithm() : SolvingAlgorithm("LeeAlgorithm") {
    this->description = DESCRIPTION;
    this->complexity = COMPLEXITY;
}

Expected<MazePath> LeeAlgorithm::solve(Maze &maze) {
    if (maze.isValid().hasError()) return Expected<MazePath>(maze.isValid().errors());

    stack<shared_ptr<Node>> stack;
    vector<shared_ptr<Node>> path;

    Graph graph = maze.getGraph().clone();
    auto startTime = std::chrono::high_resolution_clock::now();

    // Set the IDs of the path
    for (const auto& node : graph.getNodes()) {
        node->setID(0);
    }

    // Get start and end node
    shared_ptr<Node> startNode = graph.getNode(maze.getStart());
    shared_ptr<Node> endNode = graph.getNode(maze.getEnd());

    // Set start as visited
    shared_ptr<Node> currentNode = startNode;
    stack.push(startNode);
    startNode->setID(1);

    int direction = 0; // 0 = right, 1 = down, 2 = left, 3 = up

    // Iterate through the stack until path is found
    while (!stack.empty()) {
        shared_ptr<Node> currentNode = stack.top();

        // If end is found, reconstruct path
        if (currentNode == endNode) {
            break;
        }

        bool found = false;
        for (const auto& neighbor : currentNode->getNeighbours()) {
            if (neighbor->getID() == 0) {
                if (neighbor->getX() == currentNode->getX() + 1) {
                    currentNode = neighbor;
                    found = true;
                    break;
                }

                if (neighbor->getY() == currentNode->getY() - 1) {
                    currentNode = neighbor;
                    found = true;
                    break;
                }

                if (neighbor->getX() == currentNode->getX() - 1) {
                    currentNode = neighbor;
                    found = true;
                    break;
                }

                if (neighbor->getY() == currentNode->getY() + 1) {
                    currentNode = neighbor;
                    found = true;
                    break;
                }
            }
        }

        if (found) {
            currentNode->setID(1);
            stack.push(currentNode);
        } else {
            stack.pop();
        }
    }

    if (stack.empty()) {
        return Expected<MazePath>("No path found");
    }

    while (!stack.empty()) {
        path.push_back(stack.top());
        stack.pop();
    }

    reverse(path.begin(), path.end());

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    return Expected(MazePath(duration, this->getName(), path));
}