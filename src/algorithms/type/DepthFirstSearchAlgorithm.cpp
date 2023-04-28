#include "../Algorithm.h"

using namespace std;

#define DESCRIPTION "Depth-First Search (DFS) is an algorithm that traverses a graph or a tree by exploring as far as possible along each branch before backtracking. The algorithm starts at the root node (or any arbitrary node) and explores as far as possible along each branch before backtracking."
#define COMPLEXITY "O(V+E)"

DepthFirstSearchAlgorithm::DepthFirstSearchAlgorithm() : SolvingAlgorithm("DepthFirstSearchAlgorithm") {
    this->description = DESCRIPTION;
    this->complexity = COMPLEXITY;
}

Expected<MazePath> DepthFirstSearchAlgorithm::solve(Maze& maze) {
    if (maze.isValid().hasError()) return Expected<MazePath>(maze.isValid().errors());

    stack<shared_ptr<Node>> stack;
    vector<shared_ptr<Node>> path;

    Graph graph = maze.getGraph()->clone();
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

    // Iterate through the stack until path is found
    while (!stack.empty()) {
        shared_ptr<Node> currentNode = stack.top();

        // If end is found, reconstruct path
        if (currentNode->getX() == endNode->getX() && currentNode->getY() == endNode->getY()) {
            break;
        }

        // Try to find a neighbour that is not visited
        bool found = false;
        for (const auto& neighbor : currentNode->getNeighbours()) {
            if (neighbor->getID() == 0) {
                neighbor->setID(1);
                stack.push(neighbor);
                found = true;
                break;
            }
        }

        // If no neighbour is found, iterate backwards
        if (!found) {
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
