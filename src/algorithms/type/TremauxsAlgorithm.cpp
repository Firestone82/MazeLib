#include "../../headers/Head.h"

using namespace std;

#define DESCRIPTION ""
#define COMPLEXITY ""

TremauxsAlgorithm::TremauxsAlgorithm() : SolvingAlgorithm("TremauxsAlgorithm") {
    this->description = DESCRIPTION;
    this->complexity = COMPLEXITY;
}

Expected<MazePath> TremauxsAlgorithm::solve(Maze &maze) {
    if (maze.isValid().hasError()) return Expected<MazePath>(maze.isValid().errors());

    vector<std::shared_ptr<Node>> path;

    Graph graph = maze.getGraph().clone();
    auto startTime = std::chrono::high_resolution_clock::now();

    // Set the IDs of the nodes
    for (const auto& node : graph.getNodes()) {
        node->setID(0);
    }

    // Initialize the startNode and endNode nodes
    shared_ptr<Node> startNode = maze.getGraph().getNode(maze.getStart());
    shared_ptr<Node> endNode = maze.getGraph().getNode(maze.getEnd());

    // Set startNode as visited
    shared_ptr<Node> currentNode = startNode;
    path.push_back(startNode);
    currentNode->setID(1);

    // Iterate through the maze until we reach the endNode
    while (currentNode != endNode) {
        vector<std::shared_ptr<Node>> neighbours;

        for (auto& neighbour : currentNode->getNeighbours()) {
            if (neighbour->getID() == 0) {
                neighbours.push_back(neighbour);
            }
        }

        if (!neighbours.empty()) {
            auto next = neighbours[rand() % neighbours.size()];

            // Mark the chosen neighbour and move to it
            next->setID(1);
            path.push_back(next);

            currentNode = next;
        } else { // If all neighbours have been visited, backtrack to the last unvisited node
            path.pop_back();
            currentNode->setID(2);
            currentNode = path.back();
        }
    }

    if (path.empty()) {
        return Expected<MazePath>("No path found");
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    return Expected(MazePath(duration,this->getName(),path));
}