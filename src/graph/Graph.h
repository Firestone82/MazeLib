#pragma once

#include <vector>
#include <string>
#include <memory>
#include <tuple>
#include <iostream>

typedef std::tuple<int, int> Coordinate;

class Node {
private:
    int x;
    int y;
    int id;

    std::vector<std::shared_ptr<Node>> neighbours;

public:
    Node(int x, int y);

    ~Node() = default;

    int getX() const;

    int getY() const;

    void setID(int id);

    int getID() const;

    void addNeighbour(std::shared_ptr<Node> node);

    std::vector<std::shared_ptr<Node>> getNeighbours();

    void clearNeighbours();

};

class Graph {
private:
    int width;
    int height;

    std::vector<std::shared_ptr<Node>> nodes;

public:
    Graph(int width, int height);

    ~Graph();

    int getWidth() const;

    int getHeight() const;

    std::vector<std::shared_ptr<Node>> getNodes();

    std::shared_ptr<Node> getNode(Coordinate coordinate);

    std::shared_ptr<Node> getNode(int x, int y);

    int size() const;

    Graph clone();
};
