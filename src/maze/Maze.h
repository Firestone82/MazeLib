#pragma once

#include "../headers/Head.h"

class Maze {
    private:
        int width;
        int height;
        double generationTime;
        std::string generationAlgorithm;
        Coordinate start;
        Coordinate end;
        int pathWidth;
        int wallWidth;
        unsigned int seed;
        Graph graph;

    public:
        Maze(int width, int height, double generationTime, std::string generationAlgorithm,
             Coordinate start, Coordinate end, int pathWidth, int wallWidth, double seed, const Graph& graph);
        ~Maze() = default;

        int getWidth() const;
        int getHeight() const;
        double getGenerationTime() const;
        std::string getGenerationAlgorithm() const;
        Coordinate getStart() const;
        Coordinate getEnd() const;
        int getPathWidth() const;
        int getWallWidth() const;
        unsigned int getSeed() const;
        Graph getGraph() const;

        std::optional<std::string> isValid() const;
};

class MazePath {
    private:
        double solvingTime;
        std::string solvingAlgorithm;
        std::vector<std::shared_ptr<Node>> nodes;

    public:
        MazePath(double solvingTime, std::string solvingAlgorithm, std::vector<std::shared_ptr<Node>> nodes);
        ~MazePath() = default;

        std::string getSolvingAlgorithm() const;
        double getSolvingTime() const;

        int getLength() const;
        int getJunctionCount() const;

        void addNode(std::shared_ptr<Node> node);
        std::vector<std::shared_ptr<Node>> getNodes() const;

        std::optional<std::string> isValid() const;
};

class MazeBuilder {
    private:
        int width;
        int height;
        double generationTime;
        std::string generationAlgorithm;
        Coordinate start;
        Coordinate end;
        int pathWidth;
        int wallWidth;
        unsigned int seed;
        Graph graph;

    public:
        MazeBuilder(int width, int height, double generationTime, std::string generationAlgorithm, double seed);
        MazeBuilder(int width, int height, double generationTime, std::string generationAlgorithm, double seed, const Graph& graph);
        ~MazeBuilder() = default;

        int getWidth() const;
        int getHeight() const;
        double getGenerationTime() const;
        std::string getGenerationAlgorithm() const;

        void setStart(Coordinate start);
        Coordinate getStart() const;

        void setEnd(Coordinate end);
        Coordinate getEnd() const;

        void setPathWidth(int pathWidth);
        int getPathWidth() const;

        void setWallWidth(int wallWidth);
        int getWallWidth() const;

        void setSeed(double seed);
        unsigned int getSeed() const;

        void setGraph(const Graph& graph);
        Graph getGraph();

        std::optional<std::string> isValid() const;

        Maze build();
};