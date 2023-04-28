#include "../headers/Head.h"

/**
 * @brief Construct a new Node:: Node object
 * @param x X coordinate
 * @param y Y coordinate
 */
Node::Node(int x, int y) {
    this->x = x;
    this->y = y;
    this->id = 0;
}

/**
 * @brief Get the X coordinate of the node
 * @return X coordinate
 */
int Node::getX() const {
    return this->x;
}

/**
 * @brief Get the Y coordinate of the node
 * @return Y coordinate
 */
int Node::getY() const {
    return this->y;
}

/**
 * @brief Set the ID of the node
 * @param id ID to set
 * @return ID of the node
 */
void Node::setID(int id) {
    this->id = id;
}

/**
 * @brief Get the ID of the node
 * @return ID of the node
 */
int Node::getID() const {
    return this->id;
}

/**
 * @brief Add a neighbour to the node
 * @param node Node to add as neighbour
 */
void Node::addNeighbour(std::shared_ptr<Node> node) {
    this->neighbours.push_back(node);
}

/**
 * @brief Get the neighbours of the node
 * @return Vector of neighbours
 */
std::vector<std::shared_ptr<Node>> Node::getNeighbours() {
    return this->neighbours;
}

/**
 * @brief Clear the neighbours of the node
 * @return
 */
void Node::clearNeighbours() {
    this->neighbours.clear();
}

/**
 * ====================================================
 */

/**
 * @brief Construct a new Graph:: Graph object
 * @param width Width of the graph
 * @param height Height of the graph
 */
Graph::Graph(int width, int height) {
    this->width = width;
    this->height = height;

    // Initialize nodes
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            this->nodes.push_back(std::make_shared<Node>(x, y));
        }
    }
}

/**
 * @brief Destroy the Graph:: Graph object
 */
Graph::~Graph() {
    for (const auto& node : this->nodes) {
        node->clearNeighbours();
    }
}

/**
 * @brief Construct a new Graph:: Graph object
 * @param graph Graph to copy
 */
Graph Graph::clone() {
    Graph newGraph(this->width, this->height);

    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            std::shared_ptr<Node> node = this->getNode(x, y);
            std::shared_ptr<Node> newNode = newGraph.getNode(x, y);

            newNode->setID(node->getID());

            for (const auto& neighbour : node->getNeighbours()) {
                newNode->addNeighbour(newGraph.getNode(neighbour->getX(), neighbour->getY()));
            }
        }
    }

    return newGraph;
}

/**
 * @brief Get the width of the graph
 * @return Width of the graph
 */
int Graph::getWidth() const {
    return this->width;
}

/**
 * @brief Get the height of the graph
 * @return Height of the graph
 */
int Graph::getHeight() const {
    return this->height;
}

/**
 * @brief Get the nodes of the graph
 * @return Vector of nodes
 */
std::vector<std::shared_ptr<Node>> Graph::getNodes() {
    return this->nodes;
}

/**
 * @brief Get the node at the specified coordinates
 * @param coordinate coordinate to get the node at
 * @return Node at the specified coordinates
 */
std::shared_ptr<Node> Graph::getNode(Coordinate coordinate) {
    return this->getNode(std::get<0>(coordinate),std::get<1>(coordinate));
}

/**
 * @brief Get the node at the specified coordinates
 * @param x X coordinate
 * @param y Y coordinate
 * @return Node at the specified coordinates
 */
std::shared_ptr<Node> Graph::getNode(int x, int y) {
//    for (auto node : this->nodes) {
//        if (node->getX() == x && node->getY() == y) {
//            return node;
//        }
//    }

    return this->nodes.at(x + y * width);
}

/**
 * @brief Get the size of the graph
 * @return Size of the graph
 */
int Graph::size() const {
    return static_cast<int>(this->nodes.size());
}