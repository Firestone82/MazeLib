#include "../../headers/Head.h"

using json = nlohmann::json;

Expected<int> TextFileSavingMethod::save(const Maze& maze, std::string fileName) {
    return this->save(maze, fileName,std::nullopt);
}

Expected<int> TextFileSavingMethod::save(const Maze& maze, std::string fileName, std::optional<MazePath> path) {
    if (maze.isValid() != std::nullopt) return Expected<int>(maze.isValid().value());
    if (path != std::nullopt && path.value().isValid() != std::nullopt) return Expected<int>(path.value().isValid().value());

    nlohmann::ordered_json mazeObject = {
        {"width", maze.getWidth()},
        {"height", maze.getHeight()},
        {"generationTime", maze.getGenerationTime()},
        {"generationAlgorithm", maze.getGenerationAlgorithm()},
        {"coords", {
            {"start", {std::get<0>(maze.getStart()), std::get<1>(maze.getStart())}},
            {"end", {std::get<0>(maze.getEnd()), std::get<1>(maze.getEnd())}},
        }},
        {"pathWidth", maze.getPathWidth()},
        {"wallWidth", maze.getWallWidth()},
        {"seed", maze.getSeed()},
        {"mazeNodes", json::array()},
        {"pathNodes", json::array()}
    };

    json nodes;

    for (const auto& node : maze.getGraph().getNodes()) {
        json nodeObject = {
                {"x", node->getX()},
                {"y", node->getY()},
                {"neighbors", {}}
        };

        for (const auto& neighbor : node->getNeighbours()) {
            nodeObject["neighbors"].push_back({
                {"x", neighbor->getX()},
                {"y", neighbor->getY()}
            });
        }

        nodes.push_back(nodeObject);
    }

    mazeObject["mazeNodes"] = nodes;

    if (path != std::nullopt) {
        json paths;

        for (const auto &node: path.value().getNodes()) {
           paths.push_back({
                {"x", node->getX()},
                {"y", node->getY()}
            });
        }

        mazeObject["pathNodes"] = paths;
    }

    try {
        std::ofstream file(fileName);
        file << mazeObject.dump(4);
        file.close();
    } catch (const std::exception& e) {
        return Expected<int>(e.what());
    }

    return Expected<int>(0);
}