#include <queue>
#include "../../headers/Head.h"

using namespace std;

#define DESCRIPTION ""
#define COMPLEXITY ""

BreadthFirstSearchAlgorithm::BreadthFirstSearchAlgorithm() : SolvingAlgorithm("BreadthFirstSearch") {
    this->description = DESCRIPTION;
    this->complexity = COMPLEXITY;
}

Expected<MazePath> BreadthFirstSearchAlgorithm::solve(Maze& maze) {
    if (maze.isValid().hasError()) return Expected<MazePath>(maze.isValid().errors());

    queue<shared_ptr<Node>> queue;
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
    startNode->setID(0);
    queue.push(startNode);

    // Iterate through the queue until path is found
    while (!queue.empty()) {
        currentNode = queue.front();
        queue.pop();

        // Increase ID
        currentNode->setID(currentNode->getID() + 1);

        // If end is found, reconstruct path
        if (currentNode->getX() == endNode->getX() && currentNode->getY() == endNode->getY()) {
            break;
        }

        // Try to find a neighbour that is not visited
        for (const auto& neighbor : currentNode->getNeighbours()) {
            if (neighbor->getID() == 0) {
                neighbor->setID(currentNode->getID());
                queue.push(neighbor);
            }
        }
    }

    if (currentNode == startNode) {
        return Expected<MazePath>("No path found");
    }

    while (currentNode->getID() > 1) {
        path.push_back(currentNode);

        for (const auto& neighbor : currentNode->getNeighbours()) {
            if (neighbor->getID() == currentNode->getID() - 1) {
                currentNode = neighbor;
                break;
            }
        }
    }

    path.push_back(startNode);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    return Expected(MazePath(duration,this->getName(),path));
}
