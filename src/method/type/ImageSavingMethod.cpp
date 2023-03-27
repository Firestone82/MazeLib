#include "../../headers/Head.h"

Expected<int> ImageSavingMethod::save(const Maze& maze, std::string fileName) {
    return save(maze, fileName,std::nullopt);
}

Expected<int> ImageSavingMethod::save(const Maze& maze, std::string fileName, std::optional<MazePath> path) {
    if (maze.isValid() != std::nullopt) return Expected<int>(maze.getError().value());
    if (path != std::nullopt && path.value().getError() != std::nullopt) return Expected<int>(path.value().getError().value());

    int pathWidth = maze.getPathWidth();
    int wallWidth = maze.getWallWidth();

    int pointWidth = pathWidth < 8 ? pathWidth / 4 : pathWidth / 4 - wallWidth / 2;
    if (pointWidth < 1) pointWidth = 1;

    int width = maze.getWidth() * pathWidth + maze.getWidth() * wallWidth + wallWidth;
    int height = maze.getHeight() * pathWidth + maze.getHeight() * wallWidth + wallWidth;

    Image image = Image(width, height);

    // Draw border
    for (int i = 0; i < wallWidth; i++) {
        image.drawRect(i,i,width - i * 2,height - i * 2,WALL_COLOR);
    }

    // Draw the route
    if (path != std::nullopt) {
        auto currentNode = maze.getGraph().getNode(maze.getStart());

        for (const auto& node : path.value().getNodes()) {
            if (currentNode != maze.getGraph().getNode(maze.getStart())) {
                image.drawLine(
                        (currentNode->getX() * pathWidth) + (currentNode->getX() * wallWidth) + (pathWidth / 2) + wallWidth,
                        (currentNode->getY() * pathWidth) + (currentNode->getY() * wallWidth) + (pathWidth / 2) + wallWidth,
                        (node->getX() * pathWidth) + (node->getX() * wallWidth) + (pathWidth / 2) + wallWidth,
                        (node->getY() * pathWidth) + (node->getY() * wallWidth) + (pathWidth / 2) + wallWidth,
                        pointWidth,
                        PATH_COLOR
                );
            }

            currentNode = node;
        }
    }

    for (const auto& node: maze.getGraph().getNodes()) {
//        // Draw node box
//        image.drawRect(
//                node->getX() * pathWidth + node->getX() * wallWidth + wallWidth,
//                node->getY() * pathWidth + node->getY() * wallWidth + wallWidth,
//                pathWidth,
//                pathWidth,
//                {50,50,50}
//        );

        // Draw start node
        if (node->getX() == std::get<0>(maze.getStart()) && node->getY() == std::get<1>(maze.getStart())) {
            if (pathWidth % 2 == 0) {
                for (int x = 0; x < 2; x++) {
                    for (int y = 0; y < 2; y++) {
                        image.drawFillCircle(
                                (node->getX() * pathWidth) + (node->getX() * wallWidth) + (pathWidth / 2) + wallWidth - x,
                                (node->getY() * pathWidth) + (node->getY() * wallWidth) + (pathWidth / 2) + wallWidth - y,
                                pointWidth,
                                START_COLOR
                        );
                    }
                }
            } else {
                image.drawFillCircle(
                        (node->getX() * pathWidth) + (node->getX() * wallWidth) + (pathWidth / 2) + wallWidth,
                        (node->getY() * pathWidth) + (node->getY() * wallWidth) + (pathWidth / 2) + wallWidth,
                        pointWidth,
                        START_COLOR
                );
            }
        }

        // Draw end node
        if (node->getX() == std::get<0>(maze.getEnd()) && node->getY() == std::get<1>(maze.getEnd())) {
            if (pathWidth % 2 == 0) {
                for (int x = 0; x < 2; x++) {
                    for (int y = 0; y < 2; y++) {
                        image.drawFillCircle(
                                (node->getX() * pathWidth) + (node->getX() * wallWidth) + (pathWidth / 2) + wallWidth - x,
                                (node->getY() * pathWidth) + (node->getY() * wallWidth) + (pathWidth / 2) + wallWidth - y,
                                pointWidth,
                                END_COLOR
                        );
                    }
                }
            } else {
                image.drawFillCircle(
                        (node->getX() * pathWidth) + (node->getX() * wallWidth) + (pathWidth / 2) + wallWidth,
                        (node->getY() * pathWidth) + (node->getY() * wallWidth) + (pathWidth / 2) + wallWidth,
                        pointWidth,
                        END_COLOR
                );
            }
        }

        bool leftWall = true;
        bool topWall = true;

        // Check neighbours of node for wall drawing
        for (const auto& neighbour: node->getNeighbours()) {
            if (neighbour->getX() == node->getX() - 1) leftWall = false;
            if (neighbour->getY() == node->getY() - 1) topWall = false;
        }

        // Draw left wall
        if (leftWall) {
            image.drawFillRect(
                    node->getX() * pathWidth + node->getX() * wallWidth,
                    node->getY() * pathWidth + node->getY() * wallWidth,
                    wallWidth,
                    pathWidth + wallWidth * 2,
                    WALL_COLOR
            );
        }

        // Draw top wall
        if (topWall) {
            image.drawFillRect(
                    node->getX() * pathWidth + node->getX() * wallWidth,
                    node->getY() * pathWidth + node->getY() * wallWidth,
                    pathWidth + wallWidth * 2,
                    wallWidth,
                    WALL_COLOR
            );
        }
    }

    if (image.save(fileName) == 1) {
        return Expected(0);
    } else {
        return Expected<int>("While saving the image an error occurred.");
    }
}