#include "../Method.h"
#include "../../headers/libs/json.hpp"

using json = nlohmann::json;

/**
 * Loads maze from text file
 * @param fileName file name
 * @return MazeBuilder object or std::nullopt if the file is not found
 */
Expected<MazeBuilder> TextFileLoadingMethod::load(std::string fileName) {

    json json;

    // Check if file has a valid extension
    if (fileName.substr(fileName.length() - 4) != ".txt" && fileName.substr(fileName.length() - 5) != ".json") {
        return Expected<MazeBuilder>("File name must end with .txt or .json");
    }

    try {
        std::ifstream file(fileName);
        json = json::parse(file);
        file.close();
    } catch (std::exception &e) {
        return Expected<MazeBuilder>("File not found or corrupted");
    }

    int width = json["width"];
    int height = json["height"];
    double generationTime = json["generationTime"];
    std::string generationAlgorithm = json["generationAlgorithm"];
    Coordinate start = {json["coords"]["start"][0], json["coords"]["start"][1]};
    Coordinate end = {json["coords"]["end"][0], json["coords"]["end"][1]};
    int pathWidth = json["pathWidth"];
    int wallWidth = json["wallWidth"];

    // TODO: Fix loading seed as unsigned int from text file
    unsigned int seed = json["seed"].get<nlohmann::json::number_float_t>();

    std::shared_ptr<Graph> graph = std::make_shared<Graph>(width, height);

    for (const auto &node: json["mazeNodes"]) {
        int x = node["x"];
        int y = node["y"];

        for (const auto &neighbor: node["neighbors"]) {
            int neighborX = neighbor["x"];
            int neighborY = neighbor["y"];

            graph->getNode(x, y)->addNeighbour(graph->getNode(neighborX, neighborY));
        }
    }

    MazeBuilder mazeBuilder = MazeBuilder(width, height, generationTime, generationAlgorithm, seed, graph);
    mazeBuilder.setStart(start);
    mazeBuilder.setEnd(end);
    mazeBuilder.setPathWidth(pathWidth);
    mazeBuilder.setWallWidth(wallWidth);

    if (mazeBuilder.buildExpected().hasError()) {
        return Expected<MazeBuilder>(mazeBuilder.buildExpected().error());
    }

    return Expected<MazeBuilder>(mazeBuilder);

}