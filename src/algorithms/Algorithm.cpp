#include "../headers/Head.h"

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
}