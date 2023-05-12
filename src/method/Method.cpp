#include "Method.h"

/**
 * @brief Construct a new Method:: Method object
 * @param name method name
 * @param type method type
 */
Method::Method(std::string name, std::string type)
        : name(name), type(type) {

    // empty
}

/**
 * Returns the name of the method
 * @return name of the method
 */
std::string Method::getName() {
    return this->name;
}

/**
 * Returns the type of the method
 * @return type of the method
 */
std::string Method::getType() {
    return this->type;
}
