#pragma once

#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include "../graph/Graph.h"
#include "../headers/Expected.h"

class Maze {
    private:
        int width;
        int height;
        long long generationTime;
        std::string generationAlgorithm;
        Coordinate start;
        Coordinate end;
        int pathWidth;
        int wallWidth;
        unsigned int seed;
        std::shared_ptr<Graph> graph;

    public:
        Maze(int width, int height, long long generationTime, std::string generationAlgorithm,
             Coordinate start, Coordinate end, int pathWidth, int wallWidth, unsigned int seed, std::shared_ptr<Graph>& graph);
        ~Maze() = default;

        int getWidth() const;
        int getHeight() const;
        long long getGenerationTime() const;
        std::string getGenerationAlgorithm() const;
        Coordinate getStart() const;
        Coordinate getEnd() const;
        int getPathWidth() const;
        int getWallWidth() const;
        unsigned int getSeed() const;
        std::shared_ptr<Graph> getGraph() const;

        Expected<int> isValid() const;
};

class MazePath {
    private:
        long long solvingTime;
        std::string solvingAlgorithm;
        std::vector<std::shared_ptr<Node>> nodes;

    public:
        MazePath(long long solvingTime, std::string solvingAlgorithm, std::vector<std::shared_ptr<Node>> nodes);
        ~MazePath() = default;

        std::string getSolvingAlgorithm() const;
        long long getSolvingTime() const;

        int getLength() const;
        int getJunctionCount() const;

        void addNode(std::shared_ptr<Node> node);
        std::vector<std::shared_ptr<Node>> getNodes() const;

        Expected<int> isValid() const;
};

class MazeBuilder {
    private:
        int width;
        int height;
        long long generationTime;
        std::string generationAlgorithm;
        Coordinate start;
        Coordinate end;
        int pathWidth;
        int wallWidth;
        unsigned int seed;
        std::shared_ptr<Graph> graph;

    public:
//        MazeBuilder(int width, int height, long long generationTime, std::string generationAlgorithm, unsigned int seed);
        MazeBuilder(int width, int height, long long generationTime, std::string generationAlgorithm, unsigned int seed, std::shared_ptr<Graph>& graph);
        ~MazeBuilder() = default;

        int getWidth() const;
        int getHeight() const;
        long long getGenerationTime() const;
        std::string getGenerationAlgorithm() const;

        void setStart(Coordinate start);
        Coordinate getStart() const;

        void setEnd(Coordinate end);
        Coordinate getEnd() const;

        void setPathWidth(int pathWidth);
        int getPathWidth() const;

        void setWallWidth(int wallWidth);
        int getWallWidth() const;

        void setSeed(unsigned int seed);
        unsigned int getSeed() const;

        void setGraph(std::shared_ptr<Graph>& graph);
        std::shared_ptr<Graph> getGraph();

        // TODO-Extra: Switch this methods output
        Maze build();
        Expected<Maze> buildExpected();
};