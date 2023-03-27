#pragma once

template <typename T>
class Expected {
    public:
        std::optional<T> val;
        std::string err;

        explicit Expected(const T& value) {
            this->val = std::make_optional<T>(value);
            this->err = "";
        }

        explicit Expected(const std::string& error) {
            this->val = std::nullopt;
            this->err = error;
        }

        T value() {
            if (this->hasError()) {
                throw std::runtime_error(this->err);
            }

            return this->val.value();
        }

        T valueOr(const T& defaultValue) {
            if (this->hasError()) {
                return defaultValue;
            }

            return this->val.value();
        }

        operator T() {
            return this->value();
        }

        bool hasError() {
            return !err.empty();
        }

        std::string error() {
            return this->err;
        }
};