#include "../../headers/Head.h"

using namespace std;

Expected<MazePath> RecursiveBacktrackerAlgorithm::solve(Maze& maze) {
    if (maze.isValid() != nullopt) return Expected<MazePath>(maze.isValid().value());

    stack<shared_ptr<Node>> stack;
    vector<shared_ptr<Node>> nodes;

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
    stack.push(startNode);

    // Iterate through the stack until path is found
    while (!stack.empty()) {
        shared_ptr<Node> currentNode = stack.top();

        // If end is found, reconstruct path
        if (currentNode->getX() == endNode->getX() && currentNode->getY() == endNode->getY()) {
            nodes.push_back(endNode);

            while (!stack.empty()) {
                nodes.push_back(stack.top());
                stack.pop();
            }

            nodes.push_back(startNode);
            return Expected(MazePath((clock() - startTime),this->getName(), nodes));
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

    return Expected<MazePath>("Maze path was not found!");
}
