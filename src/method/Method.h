#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "../headers/Expected.h"
#include "../maze/Maze.h"
#include "../image/Image.h"

// --------------------------------

class Maze;

class Method {
private:
    std::string name;
    std::string type;

public:
    /* -- */ Method(std::string name, std::string type);

    virtual ~Method() = default;

    std::string getName();

    std::string getType();
};

// --------------------------------

class SavingMethod : public Method {
public:
    explicit SavingMethod(std::string name) : Method(name, "saving") {};

    virtual ~SavingMethod() = default;

    virtual Expected<int> save(const Maze &maze, std::string fileName) = 0;

    virtual Expected<int> save(const Maze &maze, std::string fileName, std::optional<MazePath> path) = 0;
};

class TextFileSavingMethod : public SavingMethod {
public:
    /* -- */ TextFileSavingMethod() : SavingMethod("Text File") {};

    virtual ~TextFileSavingMethod() = default;

    Expected<int> save(const Maze &maze, std::string fileName) override;

    Expected<int> save(const Maze &maze, std::string fileName, std::optional<MazePath> path) override;
};

class ImageSavingMethod : public SavingMethod {
public:
    /* -- */ ImageSavingMethod() : SavingMethod("Image File") {};

    virtual ~ImageSavingMethod() = default;

    Expected<int> save(const Maze &maze, std::string fileName) override;

    Expected<int> save(const Maze &maze, std::string fileName, std::optional<MazePath> path) override;
};

// ------------

class MemoryMethod : public Method {
public:
    explicit MemoryMethod(std::string name) : Method(name, "memory") {};

    virtual ~MemoryMethod() = default;

    virtual Expected<std::vector<unsigned char>> save(const Maze &maze) = 0;

    virtual Expected<std::vector<unsigned char>> save(const Maze &maze, std::optional<MazePath> path) = 0;
};

// ------------

class LoadingMethod : public Method {
public:
    explicit LoadingMethod(std::string name) : Method(name, "loading") {};

    virtual ~LoadingMethod() = default;

    virtual Expected<MazeBuilder> load(std::string fileName) = 0;
};

class TextFileLoadingMethod : public LoadingMethod {
public:
    /* -- */ TextFileLoadingMethod() : LoadingMethod("Text File") {};

    virtual ~TextFileLoadingMethod() = default;

    Expected<MazeBuilder> load(std::string fileName) override;
};

