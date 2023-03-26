#pragma once

#include "../headers/Head.h"

class Option {
    private:
        std::string name;
        std::vector<std::string> aliases;
        std::vector<std::string> arguments;
        std::string description;
        bool required;
        std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>> defaultValues;

    public:
        explicit Option(std::string name);
        ~Option() = default;

        std::string getName() const;

        Option& addAlias(std::string alias);
        Option& addAliases(std::vector<std::string> aliases);
        std::vector<std::string> getAliases() const;

        Option& addArgument(std::string argument);
        Option& addArguments(std::vector<std::string> arguments);
        std::vector<std::string> getArguments() const;

        Option& setDescription(std::string description);
        std::string getDescription() const;

        Option& setRequired(bool required);
        bool isRequired() const;

        Option& setDefaults(std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>> defaultValues);
        std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>> getDefaults() const;
    };

class Category {
    private:
        std::string name;
        std::vector<std::string> aliases;
        std::string description;
        std::string usage;
        std::vector<Option> options;
        std::function<int(std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>>)> callable;

    public:
        Category() = default;
        ~Category() = default;

        Category& setName(std::string name);
        std::string getName() const;

        Category& addAlias(std::string alias);
        Category& addAliases(std::vector<std::string> aliases);
        std::vector<std::string> getAliases() const;

        Category& setDescription(std::string description);
        std::string getDescription() const;

        Category& setUsage(std::string usage);
        std::string getUsage() const;

        Category& addOption(const Option& option);

        Category& returns(std::function<int()> callable);
        Category& returns(std::function<int(std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>>)> callable);

        int call(int argc, char** argv) const;
};

class Interface {
    private:
        std::vector<std::shared_ptr<Category>> categories;
        std::function<int()> callable;

    public:
        Interface() = default;
        ~Interface() = default;

        void addCategory(Category category);
        std::vector<std::shared_ptr<Category>> getCategories() const;
        void setDefault(std::function<int()> callable);

        int run(int argc, char** argv);
};