#include "../headers/Head.h"

/**
 * @brief Construct a new Algorithm:: Algorithm object
 * @param name algorithm name
 * @param type algorithm type
 */
Algorithm::Algorithm(std::string name, std::string type)
    : name(name), type(type) {

    // empty
};

/**
 * @brief Construct a new Algorithm:: Algorithm object
 * @param name algorithm name
 * @param type algorithm type
 * @param complexity algorithm complexity
 */
Algorithm::Algorithm(std::string name, std::string type, std::string complexity)
    : name(name), type(type), complexity(complexity) {

    // empty
};

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
};

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

    for (auto& generator : GeneratingAlgorithm::getGenerators()) {
        algorithms.push_back(generator);
    }

    for (auto& solver : SolvingAlgorithm::getSolvers()) {
        algorithms.push_back(solver);
    }

    return algorithms;
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
    : Algorithm(name,"generating"), seed(seed) {

    // empty
};

/**
 * Returns all generators
 * @return list of generators
 */
std::vector<std::shared_ptr<GeneratingAlgorithm>> GeneratingAlgorithm::getGenerators() {
    std::vector<std::shared_ptr<GeneratingAlgorithm>> generators;

    generators.push_back(std::make_unique<KruskalAlgorithm>());

    return generators;
}

/**
 * Get a generator by name
 * @param name generator name
 * @return Generator
 */
std::shared_ptr<GeneratingAlgorithm> GeneratingAlgorithm::getGenerator(std::string name) {
    return GeneratingAlgorithm::getGenerator(name,time(nullptr));
}

/**
 * Get a generator by name and seed
 * @param name generator name
 * @param seed seed of the generator
 * @return Generator
 */
std::shared_ptr<GeneratingAlgorithm> GeneratingAlgorithm::getGenerator(std::string name, unsigned int seed) {
    std::transform(name.begin(),name.end(),name.begin(),::tolower);

    for (auto& generator : GeneratingAlgorithm::getGenerators()) {
        if (generator->getName() == name) {
            return std::make_shared<KruskalAlgorithm>(seed);
        }
    }

    return nullptr;
}

/**
* =================================================================================================
*/

/**
 * @brief Construct a new Solving Algorithm:: Solving Algorithm object
 * @param name algorithm name
 */
SolvingAlgorithm::SolvingAlgorithm(std::string name)
    : Algorithm(name,"solving") {

    // empty
};

std::vector<std::shared_ptr<SolvingAlgorithm>> SolvingAlgorithm::getSolvers() {
    std::vector<std::shared_ptr<SolvingAlgorithm>> generators;

    generators.push_back(std::make_unique<RecursiveBacktrackerAlgorithm>());

    return generators;
}

/**
 * Get a solver by name
 * @param name solver name
 * @return Solver
 */
std::shared_ptr<SolvingAlgorithm> SolvingAlgorithm::getSolvers(std::string name) {
    std::transform(name.begin(),name.end(),name.begin(),::tolower);

    for (auto& solver : SolvingAlgorithm::getSolvers()) {
        if (solver->getName() == name) {
            return std::move(solver);
        }
    }

    return nullptr;
}