#include "../headers/Head.h"
#include "../headers/libs/stb_image_write.h"

/**
 * @brief Returns the height of the image
 * @return height of the image
 */
int Image::getHeight() const {
    return height;
}

/**
 * @brief Returns the width of the image
 * @return width of the image
 */
int Image::getWidth() const {
    return width;
}

/**
 * @brief Construct a new Image:: Image object
 * @param width Width of the image
 * @param height Height of the image
 */
Image::Image(int width, int height) {
    this->width = width;
    this->height = height;

    for (int i = 0; i < width * height; i++) {
        pixels.push_back({16,16,16});
    }
}

void Image::drawPixel(int x, int y, Color color) {
    pixels[x + y * width] = {color.r, color.g, color.b};
}

/**
 * @brief Draw a line on the image
 * @param x1 X coordinate of the first point
 * @param y1 Y coordinate of the first point
 * @param x2 X coordinate of the second point
 * @param y2 Y coordinate of the second point
 * @param color Color of the line
 */
void Image::drawLine(int x1, int y1, int x2, int y2, Color color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        drawPixel(x1,y1, color);

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

/**
 * @brief Draw a line on the image
 * @param x1 X coordinate of the first point
 * @param y1 Y coordinate of the first point
 * @param x2 X coordinate of the second point
 * @param y2 Y coordinate of the second point
 * @param thickness Thickness of the line
 * @param color Color of the line
 */
void Image::drawLine(int x1, int y1, int x2, int y2, int thickness, Color color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        int x = x1 - thickness / 2;
        int y = y1 - thickness / 2;

        drawRect(x, y,thickness,thickness, color);
        //drawCircle(x1 - thickness / 2,y1 - thickness / 2,thickness,color);

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

/**
 * @brief Draw a rectangle on the image
 * @param x X coordinate of the top left corner
 * @param y Y coordinate of the top left corner
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 * @param color Color of the rectangle
 */
void Image::drawRect(int x, int y, int width, int height, Color color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (j == 0 || j == height - 1 || i == 0 || i == width - 1) {
                drawPixel(x + i, y + j, color);
            }
        }
    }
}

/**
 * @brief Draw a filled rectangle on the image
 * @param x X coordinate of the top left corner
 * @param y Y coordinate of the top left corner
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 * @param color Color of the rectangle
 */
void Image::drawFillRect(int x, int y, int width, int height, Color color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            drawPixel(x + i, y + j, color);
        }
    }
}

/**
 * @brief Draw a circle on the image
 * @param x X coordinate of the center
 * @param y Y coordinate of the center
 * @param radius Radius of the circle
 * @param color Color of the circle
 */
void Image::drawCircle(int x, int y, int radius, Color color) {
    for (int32_t dy = y - radius; dy < y + radius; dy++)
        for (int32_t dx = x - radius; dx < x + radius; dx++)
            if ((dx - x) * (dx - x) + (dy - y) * (dy - y) == radius * radius)
                drawPixel(dx, dy, color);
}

/**
 * @brief Draw a filled circle on the image
 * @param x X coordinate of the center
 * @param y Y coordinate of the center
 * @param radius Radius of the circle
 * @param color Color of the circle
 */
void Image::drawFillCircle(int x, int y, int radius, Color color) {
    for (int32_t dy = y - radius; dy < y + radius; dy++)
        for (int32_t dx = x - radius; dx < x + radius; dx++)
            if ((dx - x) * (dx - x) + (dy - y) * (dy - y) < radius * radius)
                drawPixel(dx, dy, color);
}

/**
 * @brief Draw a grid on the image
 * @param width Width of the grid
 * @param color Color of the grid
 */
void Image::drawGrid(int width, Color color) {
    for (int i = 0; i < this->width; i += width) {
        for (int j = 0; j < this->height; j++) {
            drawPixel(i, j, color);
        }
    }

    for (int i = 0; i < this->height; i += width) {
        for (int j = 0; j < this->width; j++) {
            drawPixel(j, i, color);
        }
    }
}

/**
 * @brief Save the image to a file
 * @param filename
 */
int Image::save(std::string filename) {
    return stbi_write_png(filename.c_str(),width,height,3,pixels.data(),width * 3);
}