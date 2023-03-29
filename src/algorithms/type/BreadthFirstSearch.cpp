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

    Graph graph = maze.getGraph().clone();
    double startTime = clock();

    // Set the IDs of the nodes
    for (const auto& node : graph.getNodes()) {
        node->setID(0);
    }

    // Get start and end node
    shared_ptr<Node> startNode = graph.getNode(maze.getStart());
    shared_ptr<Node> endNode = graph.getNode(maze.getEnd());

    // Set start as visited
    startNode->setID(1);
    queue.push(startNode);

    // Iterate through the queue until path is found
    while (!queue.empty()) {
        shared_ptr<Node> currentNode = queue.front();
        queue.pop();

        // Increase ID
        currentNode->setID(currentNode->getID() + 1);

        // If end is found, reconstruct path
        if (currentNode->getX() == endNode->getX() && currentNode->getY() == endNode->getY()) {
            int id = currentNode->getID();
            vector<shared_ptr<Node>> nodes;

            while (id > 0) {
                nodes.push_back(currentNode);

                for (const auto& neighbor : currentNode->getNeighbours()) {
                    if (neighbor->getID() == id - 1) {
                        currentNode = neighbor;
                        break;
                    }
                }

                id--;
            }

            return Expected(MazePath((clock() - startTime),this->getName(), nodes));
        }

        // Try to find a neighbour that is not visited
        for (const auto& neighbor : currentNode->getNeighbours()) {
            if (neighbor->getID() == 0) {
                neighbor->setID(currentNode->getID());
                queue.push(neighbor);
            }
        }
    }

    return Expected<MazePath>("Maze path was not found!");
}
