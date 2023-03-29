#pragma once

#include "../headers/Head.h"

// --------------------------------

class Maze;
class GeneratingAlgorithm;
class SolvingAlgorithm;

class Algorithm {
    protected:
        std::string name;
        std::string type;
        std::string complexity = "O(1)";
        std::string description = "No description";

    public:
        Algorithm(std::string name, std::string type);
        Algorithm(std::string name, std::string type, std::string complexity);
        Algorithm(std::string name, std::string type, std::string complexity, std::string description);
        virtual ~Algorithm() = default;

        std::string getName();
        std::string getType();
        std::string getComplexity();
        std::string getDescription();

        static std::vector<std::shared_ptr<Algorithm>> getAlgorithms();

        static std::vector<std::shared_ptr<GeneratingAlgorithm>> getGenerators();
        static std::shared_ptr<GeneratingAlgorithm> getGenerator(std::string name);
        static std::shared_ptr<GeneratingAlgorithm> getGenerator(std::string name, unsigned int seed);

        static std::vector<std::shared_ptr<SolvingAlgorithm>> getSolvers();
        static std::shared_ptr<SolvingAlgorithm> getSolver(std::string name);
};

// --------------------------------

class GeneratingAlgorithm : public Algorithm {
    protected:
        unsigned int seed;

    public:
        /* -- */ GeneratingAlgorithm(std::string name, unsigned int seed);
        virtual ~GeneratingAlgorithm() = default;

        void setSeed(unsigned int seed);

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
        explicit SolvingAlgorithm(std::string name);
        virtual ~SolvingAlgorithm() = default;

        virtual Expected<MazePath> solve(Maze& maze) = 0;

};

class RecursiveBacktrackerAlgorithm : public SolvingAlgorithm {
    public:
        /* -- */ RecursiveBacktrackerAlgorithm();
        virtual ~RecursiveBacktrackerAlgorithm() = default;

        Expected<MazePath> solve(Maze& maze) override;
};

class BreadthFirstSearchAlgorithm : public SolvingAlgorithm {
    public:
        /* -- */ BreadthFirstSearchAlgorithm();
        virtual ~BreadthFirstSearchAlgorithm() = default;

        Expected<MazePath> solve(Maze& maze) override;
};
