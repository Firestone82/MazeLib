#include "../../headers/Head.h"

using namespace std;

/**
 * @brief Construct a new Kruskal Algorithm:: Kruskal Algorithm object
 */
KruskalAlgorithm::KruskalAlgorithm() : GeneratingAlgorithm("Kruskal",time(nullptr)) {
    // Nothing
}

/**
 * @brief Construct a new Kruskal Algorithm:: Kruskal Algorithm object
 * @param seed seed of the algorithm
 */
KruskalAlgorithm::KruskalAlgorithm(unsigned int seed) : GeneratingAlgorithm("Kruskal", seed) {
    // Nothing
}

/**
 * Generate a maze using the Kruskal algorithm
 * @param width width of the maze
 * @param height height of the maze
 * @return MazeBuilder object
 */
Expected<MazeBuilder> KruskalAlgorithm::generate(int width, int height) {
    if (this->seed <= 0)            return Expected<MazeBuilder>("Seed must be greater than 0");
    if (width < 2 || height < 2)    return Expected<MazeBuilder>("Width and height must be greater than 2");

    // Seed the random number generator
    srand(this->seed);

    Graph graph = Graph(width, height);
    double startTime = clock();

    // Set the IDs of the nodes
    for (const auto& node : graph.getNodes()) {
        node->setID(node->getX() * width + node->getY());
    }

    int iters = width * height - 1;
    while (iters > 0) {
        int targetX = rand() % width;
        int targetY = rand() % height;

        // Randomly choose a direction
        tuple<int, int> direction = make_tuple(0,0);
        switch (rand() % 4) {
            case 1: { direction = {-1, 0}; break; } // LEFT
            case 2: { direction = { 0,-1}; break; } // UP
            case 3: { direction = { 1, 0}; break; } // RIGHT
            case 4: { direction = { 0, 1}; break; } // DOWN
        }

        // Calculate the neighbour coordinates
        int neighbourX = targetX + get<0>(direction);
        int neighbourY = targetY + get<1>(direction);

        // Check if the neighbour is out of bounds
        if (neighbourX < 0 || neighbourX >= width || neighbourY < 0 || neighbourY >= height) {
            continue;
        }

        // Randomly chosen node from the graph
        shared_ptr<Node> node = graph.getNode(targetX,targetY);

        // Randomly chosen neighbour of the node
        shared_ptr<Node> neighbour = graph.getNode(neighbourX,neighbourY);

        // Check if the neighbour is already connected to the node
        if (node->getID() == neighbour->getID()) {
            continue;
        } else { // If not, connect them
            int oldId = neighbour->getID();
            int newId = node->getID();

            // Update the neighbour id
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    if (graph.getNode(x, y)->getID() == oldId) {
                        graph.getNode(x, y)->setID(newId);
                    }
                }
            }

            node->addNeighbour(neighbour);
            neighbour->addNeighbour(node);
        }

        iters--;
    }

    return Expected(MazeBuilder(width, height,(clock() - startTime),this->getName(), seed, graph));
}
