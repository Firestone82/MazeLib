#include "Algorithm.h"

/**
 * @brief Construct a new Algorithm:: Algorithm object
 * @param name algorithm name
 * @param type algorithm type
 */
Algorithm::Algorithm(std::string name, std::string type)
        : name(name), type(type) {

    // empty
}

/**
 * @brief Construct a new Algorithm:: Algorithm object
 * @param name algorithm name
 * @param type algorithm type
 * @param complexity algorithm complexity
 */
Algorithm::Algorithm(std::string name, std::string type, std::string complexity)
        : name(name), type(type), complexity(complexity) {

    // empty
}

/**
 * @brief Construct a new Algorithm:: Algorithm object
 * @param name algorithm name
 * @param type algorithm type
 * @param complexity algorithm complexity
 * @param description algorithm description
 */
Algorithm::Algorithm(std::string name, std::string type, std::string complexity, std::string description)
        : name(name), type(type), complexity(complexity), description(description) {

    // empty
}

/**
 * Returns the name of the algorithm
 * @return name of the algorithm
 */
std::string Algorithm::getName() {
    return this->name;
}

/**
 * Returns the type of the algorithm
 * @return type of the algorithm
 */
std::string Algorithm::getType() {
    return this->type;
}

/**
 * Returns the complexity of the algorithm
 * @return complexity of the algorithm
 */
std::string Algorithm::getComplexity() {
    return this->complexity;
}

/**
 * Returns the description of the algorithm
 * @return description of the algorithm
 */
std::string Algorithm::getDescription() {
    return this->description;
}

/**
 * Returns all algorithms
 * @return list of algorithms
 */
std::vector<std::shared_ptr<Algorithm>> Algorithm::getAlgorithms() {
    std::vector<std::shared_ptr<Algorithm>> algorithms;

    for (auto &generator: Algorithm::getGenerators()) {
        algorithms.push_back(generator);
    }

    for (auto &solver: Algorithm::getSolvers()) {
        algorithms.push_back(solver);
    }

    return algorithms;
}

/**
 * Returns all generators
 * @return list of generators
 */
std::vector<std::shared_ptr<GeneratingAlgorithm>> Algorithm::getGenerators() {
    std::vector<std::shared_ptr<GeneratingAlgorithm>> generators;

    generators.push_back(std::make_shared<KruskalAlgorithm>());

    return generators;
}

/**
 * Get a generator by name
 * @param name generator name
 * @return Generator
 */
std::shared_ptr<GeneratingAlgorithm> Algorithm::getGenerator(std::string name) {
    return Algorithm::getGenerator(name, time(nullptr));
}

/**
 * Get a generator by name and seed
 * @param name generator name
 * @param seed seed of the generator
 * @return Generator
 */
std::shared_ptr<GeneratingAlgorithm> Algorithm::getGenerator(std::string name, unsigned int seed) {
    std::transform(name.begin(), name.end(), name.begin(), tolower);

    for (const auto &generator: Algorithm::getGenerators()) {
        std::string target = generator->getName();
        std::transform(target.begin(), target.end(), target.begin(), tolower);

        if (target == name || target == name + "algorithm") {
            generator->setSeed(seed);
            return generator;
        }
    }

    return nullptr;
}

std::vector<std::shared_ptr<SolvingAlgorithm>> Algorithm::getSolvers() {
    std::vector<std::shared_ptr<SolvingAlgorithm>> generators;

    generators.push_back(std::make_shared<BreadthFirstSearchAlgorithm>());
    generators.push_back(std::make_shared<DepthFirstSearchAlgorithm>());
    generators.push_back(std::make_shared<DijkstraAlgorithm>());
    generators.push_back(std::make_shared<LeeAlgorithm>());
    generators.push_back(std::make_shared<TremauxsAlgorithm>());
    generators.push_back(std::make_shared<WallFollowingAlgorithm>());

    return generators;
}

/**
 * Get a solver by name
 * @param name solver name
 * @return Solver
 */
std::shared_ptr<SolvingAlgorithm> Algorithm::getSolver(std::string name) {
    std::transform(name.begin(), name.end(), name.begin(), tolower);

    for (auto &solver: Algorithm::getSolvers()) {
        std::string target = solver->getName();
        std::transform(target.begin(), target.end(), target.begin(), tolower);

        if (target == name || target == name + "algorithm") {
            return solver;
        }
    }

    return nullptr;
}

/**
* =================================================================================================
*/

/**
 * @brief Construct a new Generating Algorithm:: Generating Algorithm object
 * @param name algorithm name
 * @param seed seed of the algorithm
 */
GeneratingAlgorithm::GeneratingAlgorithm(std::string name, unsigned int seed)
        : Algorithm(name, "generating"), seed(seed) {

    // empty
}

/**
 * Sets the seed of the algorithm
 * @param seed seed of the algorithm
 */
void GeneratingAlgorithm::setSeed(unsigned int seed) {
    this->seed = seed;
}

/**
* =================================================================================================
*/

/**
 * @brief Construct a new Solving Algorithm:: Solving Algorithm object
 * @param name algorithm name
 */
SolvingAlgorithm::SolvingAlgorithm(std::string name)
        : Algorithm(name, "solving") {

    // empty
}