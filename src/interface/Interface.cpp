#include "Interface.h"

/**
 * @brief Construct a new Option:: Option object
 * @param name
 */
Option::Option(std::string name)
        : name(name), required(false) {

    // empty
}

/**
 * @brief Get the name of the option
 * @return
 */
std::string Option::getName() const {
    return this->name;
}

/**
 * @brief Set the required flag of the option
 * @param alias alias to add
 * @return option
 */
Option &Option::addAlias(std::string alias) {
    this->aliases.push_back(alias);
    return *this;
}

/**
 * @brief Set the required flag of the option
 * @param aliases aliases to add
 * @return option
 */
Option &Option::addAliases(std::vector<std::string> aliases) {
    this->aliases.insert(this->aliases.end(), aliases.begin(), aliases.end());
    return *this;
}

/**
 * @brief Get the aliases of the option
 * @return aliases
 */
std::vector<std::string> Option::getAliases() const {
    return this->aliases;
}

/**
 * @brief Add an argument to the option
 * @param argument argument to add
 * @return option
 */
Option &Option::addArgument(std::string argument) {
    this->arguments.push_back(argument);
    return *this;
}

/**
 * @brief Add arguments to the option
 * @param arguments arguments to add
 * @return option
 */
Option &Option::addArguments(std::vector<std::string> arguments) {
    this->arguments.insert(this->arguments.end(), arguments.begin(), arguments.end());
    return *this;
}

/**
 * @brief Get the arguments of the option
 * @return arguments
 */
std::vector<std::string> Option::getArguments() const {
    return this->arguments;
}

/**
 * @brief Set the description of the option
 * @param description description to set
 * @return option
 */
Option &Option::setDescription(std::string description) {
    this->description = description;
    return *this;
}

/**
 * @brief Get the description of the option
 * @return description
 */
std::string Option::getDescription() const {
    return this->description;
}

/**
 * @brief Set the required flag of the option
 * @param required required flag to set
 * @return option
 */
Option &Option::setRequired(bool required) {
    this->required = required;
    return *this;
}

/**
 * @brief Get the required flag of the option
 * @return is required
 */
bool Option::isRequired() const {
    return this->required;
}

/**
 * @brief Set the default value of the option
 * @param defaultValue default value to set
 * @return option
 */
Option &Option::setDefaults(std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>> defaultValues) {
    this->defaultValues = defaultValues;
    return *this;
}

/**
 * @brief Get the default value of the option
 * @return default value
 */
std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>> Option::getDefaults() const {
    return this->defaultValues;
}

/**
 * =================================
 */

/**
 * @brief Construct a new Category:: Category object
 * @param name name of the category
 */
Category::Category(std::string name)
        : name(name) {

    // empty
}

/**
 * @brief Get the name of the category
 * @return name
 */
std::string Category::getName() const {
    return this->name;
}

/**
 * @brief Add an alias to the category
 * @param alias alias to add
 * @return category
 */
Category &Category::addAlias(std::string alias) {
    this->aliases.push_back(alias);
    return *this;
}

/**
 * @brief Add aliases to the category
 * @param aliases aliases to add
 * @return category
 */
Category &Category::addAliases(std::vector<std::string> aliases) {
    this->aliases.insert(this->aliases.end(), aliases.begin(), aliases.end());
    return *this;
}

/**
 * @brief Add an option to the category
 * @param option option to add
 * @return category
 */
Category &Category::addOption(const Option &option) {
    this->options.push_back(option);
    return *this;
}


/**
 * @brief Get the aliases of the category
 * @return aliases
 */
std::vector<std::string> Category::getAliases() const {
    return this->aliases;
}

/**
 * @brief Add description to the category
 * @param description description to add
 * @return category
 */
Category &Category::setDescription(std::string description) {
    this->description = description;
    return *this;
}

/**
 * @brief Get the description of the category
 * @return description
 */
std::string Category::getDescription() const {
    return this->description;
}

/**
 * Set the usage of the category
 * @param usage usage to set
 * @return category
 */
Category &Category::setUsage(std::string usage) {
    this->usage = usage;
    return *this;
}

/**
 * @brief Get the usage of the category
 * @return usage
 */
std::string Category::getUsage() const {
    return this->usage;
}

/**
 * @brief Set the callable of the category
 * @param callable callable to set
 * @return category
 */
Category &Category::returns(std::function<int()> callable) {
    this->callable = [callable](
            std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> args) {
        return callable();
    };

    return *this;
}

/**
 * @brief Set the callable of the category
 * @param callable callable to set
 * @return category
 */
Category &Category::returns(std::function<int(
        std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>>)> callable) {
    this->callable = callable;
    return *this;
}

/**
 * @brief Call the category
 * @param argc argument count
 * @param argv argument values
 * @return int
 */
int Category::call(int argc, char **argv) const {
    std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> arguments;

    // If there are no options, run the callable
    if (this->options.empty()) {
        return this->callable(
                std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>>());
    }

    // Check if there is any required options
    bool required = false;
    for (const auto &option: this->options) {
        if (option.isRequired()) {
            required = true;
        }
    }


    // If there is no arguments but there is required options, show error
    if (argc == 0 && required) {
        std::cout << std::endl << " mazelib: Missing required arguments, try 'mazelib " << this->getName()
                  << " --help' for more information!" << std::endl;
        return 1;
    }

    // Show help message
    if (argc != 0 && std::strcmp(argv[0], "--help") == 0) {
        std::cout << "" << std::endl;
        std::cout << " Command: " << this->getUsage() << std::endl;
        std::cout << "" << std::endl;
        std::cout << " Options:" << std::endl;

        for (const auto &option: this->options) {
            std::cout << "   ";

            std::string aliases;
            for (const auto &alias: option.getAliases()) {
                aliases += alias + ", ";
            }
            aliases = aliases.substr(0, aliases.size() - 2);

            std::cout << std::setw(15) << std::left << aliases << "\t | ";
            std::cout << std::setw(50) << std::left << option.getDescription();
            std::cout << std::setw(8) << std::right << (option.isRequired() ? "REQUIRED" : "") << " | ";

            for (const auto &argument: option.getArguments()) {
                std::cout << "[" << argument << "] ";
            }

            std::cout << std::endl;
        }

        return 0;
    }

    // Search for all the options
    for (const auto &option: this->options) {
        std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>> values;
        int a = 0; // Argument index

        // Loop through all the arguments
        for (int i = 0; i < argc; i++) {

            // If an argument isn't option, skip
            if (argv[i][0] != '-') {
                continue;
            }

            // Loop through all the aliases
            for (const auto &alias: option.getAliases()) {

                // Alias matches
                if (alias == argv[i]) {

                    // Check if there is enough arguments
                    if (i + static_cast<int>(option.getArguments().size()) >= argc) {
                        std::cout << std::endl << " mazelib: Missing arguments, try 'mazelib " << this->getName()
                                  << " --help' for more information!" << std::endl;
                        return 1;
                    }

                    // If option was set without any arguments, then its true bool
                    if (option.getArguments().empty()) {
                        values.emplace_back(true);
                        break;
                    }

                    // Loop through all the arguments after the alias
                    for (int j = i + 1; j < argc; j++) {

                        // An option was found, stop looking for arguments
                        if (argv[j][0] == '-') {
                            break;
                        }

                        // All required arguments have been found, skip the rest
                        if (a > static_cast<int>(option.getArguments().size()) - 1) {
                            continue;
                        }

                        // Check if the argument is valid
                        std::string type = option.getArguments()[a++];

                        try {
                            if (type == "int") {
                                values.emplace_back(std::stoi(argv[j]));
                            } else if (type == "double") {
                                values.emplace_back(std::stod(argv[j]));
                            } else if (type == "string") {
                                values.emplace_back(argv[j]);
                            } else {
                                std::cout << std::endl << " mazelib: Invalid argument type '" << type
                                          << "'! Try using 'mazelib " << this->getName() << " --help' for help!"
                                          << std::endl;
                                return 2;
                            }
                        } catch (std::invalid_argument &e) {
                            std::cout << std::endl << " mazelib: Invalid values for option '" << option.getName()
                                      << "'. Try using 'mazelib " << this->getName() << " --help' for help!"
                                      << std::endl;
                            return 1;
                        }
                    }
                }
            }
        }

        // If option doesn't accept any, then its false bool
        if (option.getArguments().empty()) {
            if (values.empty()) {
                values.emplace_back(false);
            }
        } else {
            // If there is no arguments and option doesn't require them, then use the default values
            if (values.empty()) {
                if (option.isRequired()) {
                    std::cout << std::endl << " mazelib: Missing required argument '" << option.getName()
                              << "'! Try using 'mazelib " << this->getName() << " --help' for help!" << std::endl;
                    return 0;
                } else {
                    for (const auto &value: option.getDefaults()) {
                        values.emplace_back(value);
                    }
                }
            } else {
                // If there is more arguments than the option has, then it is invalid
                if (values.size() > option.getArguments().size()) {
                    std::cout << std::endl << " mazelib: Too many arguments for '" << option.getName()
                              << "'! Try using 'mazelib " << this->getName() << " --help' for help!" << std::endl;
                    return 0;
                }

                // If there is fewer arguments than the option has, then it is invalid
                if (values.size() < option.getArguments().size()) {
                    std::cout << std::endl << " mazelib: Not enough arguments for '" << option.getName()
                              << "'! Try using 'mazelib " << this->getName() << " --help' for help!" << std::endl;
                    return 0;
                }
            }
        }

        if (!values.empty()) {
            arguments[option.getName()] = std::make_optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>(
                    values);
        } else {
            arguments[option.getName()] = std::nullopt;
        }
    }

    return this->callable(
            std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>>(
                    arguments));
}

/**
 * =================================
 */

/**
 * @brief Construct a new Category:: Category object
 * @param category
 */
void Interface::addCategory(Category category) {
    this->categories.push_back(category);
}

/**
 * @brief Get the Categories object
 * @return categories
 */
std::vector<Category> Interface::getCategories() const {
    return this->categories;
}

/**
 * @brief Set default callable
 * @param callable callable
 */
void Interface::setDefault(std::function<int()> callable) {
    this->callable = callable;
}

/**
 * @brief Set default usage
 * @param usage usage
 */
void Interface::setUsage(std::string usage) {
    this->usage = usage;
}

/**
 * @brief Get the Usage object
 * @return usage
 */
std::string Interface::getUsage() const {
    return this->usage;
}

/**
 * @brief Run the interface
 * @param argc argument count
 * @param argv argument vector
 * @return an exit code
 */
int Interface::run(int argc, char **argv) {
    if (argc == 1) {
        std::cout << std::endl << this->usage << std::endl;
        return 0;
    }

    for (const auto &category: this->categories) {
        if (category.getName() == argv[1]) {
            return category.call(argc - 2, argv + 2);
        }

        for (const auto &alias: category.getAliases()) {
            if (alias == argv[1]) {
                return category.call(argc - 2, argv + 2);
            }
        }
    }

    return this->callable();
}

