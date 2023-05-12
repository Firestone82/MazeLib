#include "../Algorithm.h"

using namespace std;

#define DESCRIPTION "Wall Following Algorithm is a maze-solving algorithm that follows either the left or right wall of the maze, keeping it always on one side. It moves forward until it reaches a junction, and then turns in the direction of the wall it is following. If it reaches a dead end, it turns around and follows the wall on the other side. The algorithm terminates when it reaches the destination or returns to the starting point. The time complexity of Wall Following Algorithm is O(N), where N is the number of cells in the maze. It works for mazes with or without loops, but may not find the shortest path."
#define COMPLEXITY "O(N)"

WallFollowingAlgorithm::WallFollowingAlgorithm() : SolvingAlgorithm("WallFollowingAlgorithm") {
    this->description = DESCRIPTION;
    this->complexity = COMPLEXITY;
}

Expected<MazePath> WallFollowingAlgorithm::solve(Maze &maze) {
    if (maze.isValid().hasError()) return Expected<MazePath>(maze.isValid().errors());

    stack<shared_ptr<Node>> stack;
    vector<shared_ptr<Node>> path;

    Graph graph = maze.getGraph()->clone();
    auto startTime = std::chrono::high_resolution_clock::now();

    // Set the IDs of the path
    for (const auto &node: graph.getNodes()) {
        node->setID(0);
    }

    // Get start and end node
    shared_ptr<Node> startNode = graph.getNode(maze.getStart());
    shared_ptr<Node> endNode = graph.getNode(maze.getEnd());

    // Set start as visited
    shared_ptr<Node> currentNode = startNode;
    stack.push(startNode);
    startNode->setID(1);

    // Iterate through the stack until path is found
    while (!stack.empty()) {
        shared_ptr<Node> currentNode = stack.top();

        // If end is found, reconstruct path
        if (currentNode == endNode) {
            break;
        }

        bool found = false;
        for (const auto &neighbor: currentNode->getNeighbours()) {
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