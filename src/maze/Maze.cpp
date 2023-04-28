#include "../headers/Head.h"

/**
 * @brief Construct a new Maze:: Maze object
 * @param width width of maze
 * @param height height of maze
 * @param generationTime time of generation
 * @param generationAlgorithm algorithm of generation
 * @param start start coordinate
 * @param end end coordinate
 * @param pathWidth width of path
 * @param wallWidth width of wall
 * @param seed seed of maze
 * @param graph graph of maze
 */
Maze::Maze(int width, int height, long long generationTime, std::string generationAlgorithm, Coordinate start, Coordinate end,
           int pathWidth, int wallWidth, unsigned int seed, std::shared_ptr<Graph>& graph)
    : width(width),
      height(height),
      generationTime(generationTime),
      generationAlgorithm(generationAlgorithm),
      start(start),
      end(end),
      pathWidth(pathWidth),
      wallWidth(wallWidth),
      seed(seed),
      graph(graph) {

    // empty
}

/**
 * Get the width of the maze
 * @return width
 */
int Maze::getWidth() const {
    return this->width;
}

/**
 * Get the height of the maze
 * @return height
 */
int Maze::getHeight() const {
    return this->height;
}

/**
 * Get the generation time of the maze
 * @return
 */
long long Maze::getGenerationTime() const {
    return this->generationTime;
}

/**
 * Get the generation algorithm of the maze
 * @return
 */
std::string Maze::getGenerationAlgorithm() const {
    return this->generationAlgorithm;
}

/**
 * Get the start coordinate of the maze
 * @return
 */
Coordinate Maze::getStart() const {
    return this->start;
}

/**
 * Get the end coordinate of the maze
 * @return
 */
Coordinate Maze::getEnd() const {
    return this->end;
}

/**
 * Get the width of the path
 * @return
 */
int Maze::getPathWidth() const {
    return this->pathWidth;
}

/**
 * Get the width of the wall
 * @return
 */
int Maze::getWallWidth() const {
    return this->wallWidth;
}

/**
 * Get the seed of the maze
 * @return
 */
unsigned int Maze::getSeed() const {
    return this->seed;
}

/**
 * Get the graph of the maze
 * @return
 */
std::shared_ptr<Graph> Maze::getGraph() const {
    return this->graph;
}

Expected<int> Maze::isValid() const {
    std::vector<std::string> errors;

    if (this->width <= 0) {
        errors.emplace_back("Width must be greater than 0");
    }

    if (this->height <= 0) {
        errors.emplace_back("Height must be greater than 0");
    }

    if (this->pathWidth <= 0) {
        errors.emplace_back("Path width must be greater than 0");
    }

    if (this->wallWidth <= 0) {
        errors.emplace_back("Wall width must be greater than 0");
    }

    if (std::get<0>(this->start) < 0 || std::get<0>(this->start) >= this->width) {
        errors.emplace_back("Start X coordinate must be between 0 and width");
    }

    if (std::get<1>(this->start) < 0 || std::get<1>(this->start) >= this->height) {
        errors.emplace_back("Start Y coordinate must be between 0 and height");
    }

    if (std::get<0>(this->end) < 0 || std::get<0>(this->end) >= this->width) {
        errors.emplace_back("End X coordinate must be between 0 and width");
    }

    if (std::get<1>(this->end) < 0 || std::get<1>(this->end) >= this->height) {
        errors.emplace_back("End Y coordinate must be between 0 and height");
    }

    if (this->start == this->end) {
        errors.emplace_back("Start and end coordinates must be different");
    }

    if (this->graph->size() < 4) {
        errors.emplace_back("Graph must have at least 4 node");
    }

    if (this->graph->size() != this->width * this->height) {
        errors.emplace_back("Graph must have the same number of nodes as width * height");
    }

    if (!errors.empty()) {
        return Expected<int>(errors);
    }

    return Expected<int>(0);
}

/**
 * ====================================================
 */

MazePath::MazePath(long long solvingTime, std::string solvingAlgorithm, std::vector<std::shared_ptr<Node>> nodes)
    : solvingTime(solvingTime),
      solvingAlgorithm(solvingAlgorithm),
      nodes(nodes) {

    // Nothing
}

/**
 * @brief Get the solving algorithm used to solve the path
 * @return Solving algorithm
 */
std::string MazePath::getSolvingAlgorithm() const {
    return this->solvingAlgorithm;
}

/**
 * @brief Get the time it took to solve the path
 * @return Time it took to solve the path
 */
long long MazePath::getSolvingTime() const {
    return this->solvingTime;
}

/**
 * @brief Get the length of the path
 * @return length of the path
 */
int MazePath::getLength() const {
    return static_cast<int>(this->nodes.size());
}

/**
 * @brief Get the number of junctions in the path
 * @return junction count
 */
int MazePath::getJunctionCount() const {
    int count = 0;

    for (const auto& node : this->nodes) {
        if (node->getNeighbours().size() > 2) {
            count++;
        }
    }

    return count;
}

/**
 * @brief Add a node to the path
 * @param node node to add
 */
void MazePath::addNode(std::shared_ptr<Node> node) {
    this->nodes.push_back(node);
}

/**
 * @brief Get the nodes of the path
 * @return Vector of nodes
 */
std::vector<std::shared_ptr<Node>> MazePath::getNodes() const {
    return this->nodes;
}

Expected<int> MazePath::isValid() const {
    std::vector<std::string> errors;

    if (this->nodes.size() < 2) {
        errors.emplace_back("Path must have at least 2 nodes");
    }

    if (!errors.empty()) {
        return Expected<int>(errors);
    }

    return Expected<int>(0);
}

/**
* =================================
*/

///**
// * @brief Construct a new Maze Builder:: Maze Builder object
// * @param width width of maze
// * @param height height of maze
// */
//MazeBuilder::MazeBuilder(int width, int height, long long generationTime, std::string generationAlgorithm, unsigned int seed)
//    : width(width),
//      height(height),
//      generationTime(generationTime),
//      generationAlgorithm(generationAlgorithm),
//      pathWidth(6),
//      wallWidth(2),
//      seed(seed),
//      graph(Graph(width, height)) {
//
//    // empty
//}

/**
 * @brief Construct a new Maze Builder:: Maze Builder object
 * @param width width of maze
 * @param height height of maze
 * @param graph graph of maze
 */
MazeBuilder::MazeBuilder(int width, int height, long long generationTime, std::string generationAlgorithm, unsigned int seed, std::shared_ptr<Graph>& graph)
    : width(width),
      height(height),
      generationTime(generationTime),
      generationAlgorithm(generationAlgorithm),
      pathWidth(6),
      wallWidth(2),
      seed(seed),
      graph(graph) {

    // empty
}

/**
 * Get the width of the maze
 * @return width
 */
int MazeBuilder::getWidth() const {
    return this->width;
}

/**
 * Get the height of the maze
 * @return height
 */
int MazeBuilder::getHeight() const {
    return this->height;
}

/**
 * Get generation time of the maze
 * @return generation time
 */
long long MazeBuilder::getGenerationTime() const {
    return this->generationTime;
}

/**
 * Get generation algorithm of the maze
 * @return generation algorithm
 */
std::string MazeBuilder::getGenerationAlgorithm() const {
    return this->generationAlgorithm;
}

/**
 * Set the start coordinate of the maze
 * @param start start coordinate
 */
void MazeBuilder::setStart(Coordinate start) {
    this->start = start;
}

/**
 * Get the start coordinate of the maze
 * @return start coordinate
 */
Coordinate MazeBuilder::getStart() const {
    return this->start;
}

/**
 * Set the end coordinate of the maze
 * @param end end coordinate
 */
void MazeBuilder::setEnd(Coordinate end) {
    this->end = end;
}

/**
 * Get the end coordinate of the maze
 * @return end coordinate
 */
Coordinate MazeBuilder::getEnd() const {
    return this->end;
}

/**
 * Set the width of the path
 * @param pathWidth
 */
void MazeBuilder::setPathWidth(int pathWidth) {
    this->pathWidth = pathWidth;
}

/**
 * Get the width of the path
 * @return path width
 */
int MazeBuilder::getPathWidth() const {
    return this->pathWidth;
}

/**
 * Set the width of the wall
 * @param wallWidth
 */
void MazeBuilder::setWallWidth(int wallWidth) {
    this->wallWidth = wallWidth;
}

/**
 * Get the width of the wall
 * @return wall width
 */
int MazeBuilder::getWallWidth() const {
    return this->wallWidth;
}

/**
 * Set the seed of the maze
 * @param seed seed
 */
void MazeBuilder::setSeed( unsigned int seed) {
    this->seed = seed;
}

/**
 * Get the seed of the maze
 * @return seed
 */
unsigned int MazeBuilder::getSeed() const {
    return this->seed;
}

/**
 * Set the graph of the maze
 * @param graph graph of maze
 */
void MazeBuilder::setGraph(std::shared_ptr<Graph>& graph) {
    this->graph = graph;
}

/**
 * Get the graph of the maze
 * @return graph of maze
 */
std::shared_ptr<Graph> MazeBuilder::getGraph() {
    return this->graph;
}

/**
 * Build the maze
 * @return maze
 */
Maze MazeBuilder::build() {
    return Maze(
            this->width,
            this->height,
            this->generationTime,
            this->generationAlgorithm,
            this->start,
            this->end,
            this->pathWidth,
            this->wallWidth,
            this->seed,
            this->graph
    );
}

/**
 * Build the maze
 * @return maze
 */
Expected<Maze> MazeBuilder::buildExpected() {
    Maze maze = this->build();

    if (maze.isValid().hasError()) {
        return Expected<Maze>(maze.isValid().errors());
    }

    return Expected<Maze>(maze);
}