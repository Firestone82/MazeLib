#pragma once

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>

template<typename T>
class Expected {
public:
    std::optional<T> val;
    std::vector<std::string> err;

    explicit Expected(const T &value) {
        this->val = std::make_optional<T>(value);
        this->err = std::vector<std::string>();
    }

    explicit Expected(const std::string &error) {
        this->val = std::nullopt;
        this->err.push_back(error);
    }

    explicit Expected(const std::vector<std::string> &errors) {
        this->val = std::nullopt;
        this->err = errors;
    }

    T value() {
        if (this->hasError()) {
            // TODO-Extra: Add a way to iterate through all errors
            throw std::runtime_error(this->err[0]);
        }

        return this->val.value();
    }

    T valueOr(const T &defaultValue) {
        if (this->hasError()) {
            return defaultValue;
        }

        return this->val.value();
    }

    operator T() {
        return this->value();
    }

    std::string error() {
        if (hasError()) {
            return this->err[0];
        } else {
            return "NaN";
        }
    }

    std::vector<std::string> errors() {
        return this->err;
    }

    bool hasError() {
        return !err.empty();
    }
};