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

        static std::vector<std::shared_ptr<Algorithm>> getAlgorithms();
};

// --------------------------------

class GeneratingAlgorithm : public Algorithm {
    protected:
        unsigned int seed;

    public:
        GeneratingAlgorithm(std::string name, unsigned int seed);
        virtual ~GeneratingAlgorithm() = default;

        virtual Expected<MazeBuilder> generate(int width, int height) = 0;

        static std::vector<std::shared_ptr<GeneratingAlgorithm>> getGenerators();
        static std::shared_ptr<GeneratingAlgorithm> getGenerator(std::string name);
        static std::shared_ptr<GeneratingAlgorithm> getGenerator(std::string name, unsigned int seed);
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
        explicit SolvingAlgorithm(std::string name);
        virtual ~SolvingAlgorithm() = default;

        virtual Expected<MazePath> solve(Maze& maze) = 0;

        static std::vector<std::shared_ptr<SolvingAlgorithm>> getSolvers();
        static std::shared_ptr<SolvingAlgorithm> getSolvers(std::string name);
};

class RecursiveBacktrackerAlgorithm : public SolvingAlgorithm {
    public:
        RecursiveBacktrackerAlgorithm() : SolvingAlgorithm("RecursiveBacktracker") {};
        virtual ~RecursiveBacktrackerAlgorithm() = default;

        Expected<MazePath> solve(Maze& maze) override;
};
