#include "../headers/Head.h"
#include "Algorithm.h"


/**
 * @brief Construct a new Algorithm:: Algorithm object
 * @param name algorithm name
 * @param type algorithm type
 */
Algorithm::Algorithm(std::string name, std::string type) : name(name), type(type) {
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
std::vector<std::unique_ptr<GeneratingAlgorithm>> GeneratingAlgorithm::getGenerators() {
    std::vector<std::unique_ptr<GeneratingAlgorithm>> generators;

    generators.push_back(std::make_unique<KruskalAlgorithm>());

    return generators;
}

/**
 * Get a generator by name
 * @param name generator name
 * @return Generator
 */
std::unique_ptr<GeneratingAlgorithm> GeneratingAlgorithm::getGenerator(std::string name) {
    return GeneratingAlgorithm::getGenerator(name,time(nullptr));
}

/**
 * Get a generator by name and seed
 * @param name generator name
 * @param seed seed of the generator
 * @return Generator
 */
std::unique_ptr<GeneratingAlgorithm> GeneratingAlgorithm::getGenerator(std::string name, unsigned int seed) {
    std::transform(name.begin(),name.end(),name.begin(),::tolower);

    for (auto& generator : GeneratingAlgorithm::getGenerators()) {
        if (generator->getName() == name) {
            return std::make_unique<KruskalAlgorithm>(seed);
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

std::vector<std::unique_ptr<SolvingAlgorithm>> SolvingAlgorithm::getGenerators() {
    std::vector<std::unique_ptr<SolvingAlgorithm>> generators;

    generators.push_back(std::make_unique<RecursiveBacktrackerAlgorithm>());

    return generators;
}

/**
 * Get a solver by name
 * @param name solver name
 * @return Solver
 */
std::unique_ptr<SolvingAlgorithm> SolvingAlgorithm::getGenerator(std::string name) {
    std::transform(name.begin(),name.end(),name.begin(),::tolower);

    for (auto& solver : SolvingAlgorithm::getGenerators()) {
        if (solver->getName() == name) {
            return std::move(solver);
        }
    }

    return nullptr;
}