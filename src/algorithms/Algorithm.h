#pragma once

#include "../headers/Head.h"

// --------------------------------

class Maze;

class Algorithm {
    private:
        std::string name;
        std::string type;

    public:
        Algorithm(std::string name, std::string type);
        virtual ~Algorithm() = default;

        std::string getName();
        std::string getType();
};

// --------------------------------

class GeneratingAlgorithm : public Algorithm {
    protected:
        unsigned int seed;

    public:
        GeneratingAlgorithm(std::string name, unsigned int seed);
        virtual ~GeneratingAlgorithm() = default;

        virtual Expected<MazeBuilder> generate(int width, int height) = 0;
};

class KruskalAlgorithm : public GeneratingAlgorithm {
    public:
        /* -- */ KruskalAlgorithm();
        explicit KruskalAlgorithm(unsigned int seed);
        virtual ~KruskalAlgorithm() = default;

        Expected<MazeBuilder> generate(int width, int height) override;
};

// ------------

class SolvingAlgorithm : public Algorithm {
    public:
        explicit SolvingAlgorithm(std::string name) : Algorithm(name,"solving") {};
        virtual ~SolvingAlgorithm() = default;

        virtual Expected<MazePath> solve(Maze& maze) = 0;
};

class RecursiveBacktrackerAlgorithm : public SolvingAlgorithm {
    public:
        RecursiveBacktrackerAlgorithm() : SolvingAlgorithm("RecursiveBacktracker") {};
        virtual ~RecursiveBacktrackerAlgorithm() = default;

        Expected<MazePath> solve(Maze& maze) override;
};

