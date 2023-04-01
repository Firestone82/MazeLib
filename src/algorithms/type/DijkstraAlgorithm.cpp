#include "../../headers/Head.h"

using namespace std;

#define DESCRIPTION ""
#define COMPLEXITY ""

DijkstraAlgorithm::DijkstraAlgorithm() : SolvingAlgorithm("DijkstraAlgorithm") {
    this->description = DESCRIPTION;
    this->complexity = COMPLEXITY;
}

Expected<MazePath> DijkstraAlgorithm::solve(Maze& maze) {
    if (maze.isValid().hasError()) return Expected<MazePath>(maze.isValid().errors());

    std::map<std::shared_ptr<Node>, std::pair<int, std::shared_ptr<Node>>> nodes;
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

    // Initialize all distances to infinity, except for the start node which is 0
    for (const auto& node : graph.getNodes()) {
        nodes[node] = std::make_pair(std::numeric_limits<int>::max(),nullptr);
    }
    nodes[startNode] = std::make_pair(0,nullptr);

    // Set start as visited
    std::shared_ptr<Node> currentNode = startNode;
    startNode->setID(0);

    while (currentNode != endNode) {
        // Find the node with the smallest distance
        int distance = std::numeric_limits<int>::max();

        for (const auto& node : nodes) {
            if (node.first->getID() == 0 && node.second.first < distance) {
                distance = node.second.first;
                currentNode = node.first;
            }
        }

        // Mark the current node as visited
        currentNode->setID(1);

        // Update the distances and parent nodes of the current node's neighbours
        for (const auto& neighbour : currentNode->getNeighbours()) {
            int new_distance = nodes[currentNode].first + 1;

            if (new_distance < nodes[neighbour].first) {
                nodes[neighbour] = std::make_pair(new_distance,currentNode);
            }
        }
    }

    // Reconstruct the path
    while (currentNode != nullptr) {
        path.push_back(currentNode);
        currentNode = nodes[currentNode].second;
    }

    // Reverse the path
    std::reverse(path.begin(),path.end());

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    return Expected(MazePath(duration,this->getName(),path));
}
