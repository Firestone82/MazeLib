#pragma once

#include <string>
#include <vector>
#include "../headers/Expected.h"

/**
 * @brief Pixel struct
 */
struct Pixel {
    unsigned char r, g, b;
};

/**
 * @brief Color type
 */
typedef Pixel Color;

/**
 * @brief Color constants
 */
#define WALL_COLOR Color{255, 255, 255}
#define START_COLOR Color{0, 255, 0}
#define END_COLOR Color{255, 0, 0}
#define PATH_COLOR Color{255, 165, 0}
#define ROUTE_COLOR Color{100, 100, 100}

/**
 * @brief Image class
 */
class Image {
private:
    std::vector<Pixel> pixels;
    int width;
    int height;

public:
    Image(int width, int height);

    int getWidth() const;

    int getHeight() const;

    void drawPixel(int x, int y, Color color);

    void drawLine(int x1, int y1, int x2, int y2, Color color);

    void drawLine(int x1, int y1, int x2, int y2, int thickness, Color color);

    void drawFillRect(int x, int y, int width, int height, Color color);

    void drawRect(int x, int y, int width, int height, Color color);

    void drawFillCircle(int x, int y, int radius, Color color);

    void drawCircle(int x, int y, int radius, Color color);

    void drawGrid(int width, Color color);

    int save(std::string filename);
};
