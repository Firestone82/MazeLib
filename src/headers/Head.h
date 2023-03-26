//
// Created by Pavel on 05.03.2023.
//

#pragma once

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define VERSION "1.0.0"
#define HEADER "\
  __  __               _      _ _        \n\
 |  \\/  |             | |    (_) |      \n\
 | \\  / | __ _ _______| |     _| |__    \n\
 | |\\/| |/ _` |_  / _ \\ |    | | '_ \\ \n\
 | |  | | (_| |/ /  __/ |____| | |_) |   \n\
 |_|  |_|\\__,_/___\\___|______|_|_.__/  \n\
    Author: Pavel Mikula (MIK0486)       \n"

#define WALL_COLOR Color{255, 255, 255}
#define START_COLOR Color{0, 255, 0}
#define END_COLOR Color{255, 0, 0}
#define PATH_COLOR Color{255, 165, 0}
#define ROUTE_COLOR Color{100, 100, 100}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <random>
#include <cmath>
#include <stack>
#include <algorithm>
#include <optional>
#include <variant>

#include "libs/json.hpp"
#include "Expected.h"

#include "../image/Image.h"
#include "../graph/Graph.h"
#include "../maze/Maze.h"
#include "../algorithms/Algorithm.h"
#include "../method/Method.h"
#include "../interface/Interface.h"

int example();