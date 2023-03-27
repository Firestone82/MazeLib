#include "headers/Head.h"

using namespace std;

int main(int argc, char** argv) {
//    example();

    Interface interface = Interface();
    interface.setDefault([=]() {
        cout << endl << " mazelib: Unknown command, try 'mazelib --help' for more information!" << endl;
        return 0;
    });

    interface.addCategory(Category()
                        .setName("version")
                        .addAliases({"--version", "-v"})
                        .setDescription("Show programs version number")
                        .setUsage("mazelib version")
                        .returns([=]() {
                            cout << endl << " mazelib: Version " << VERSION << endl;
                            return 0;
                        })
    );

    interface.addCategory(Category()
                        .setName("generate")
                        .setDescription("Generate maze to file or image")
                        .setUsage("mazelib generate [options]")
                        .addOption(Option("width")
                                            .addAliases({"-w", "--width"})
                                            .addArguments({"int"})
                                            .setDescription("Width of maze")
                                            .setRequired(true)
                        )
                        .addOption(Option("height")
                                            .addAliases({"-h", "--height"})
                                            .addArguments({"int"})
                                            .setDescription("Height of maze")
                                            .setRequired(true)
                        )
                        .addOption(Option("algorithm")
                                            .addAliases({"-a", "--algorithm"})
                                            .addArguments({"string"})
                                            .setDescription("Algorithm to generate maze")
                                            .setRequired(true)
                        )
                        .addOption(Option("seed")
                                           .addAliases({"-se", "--seed"})
                                           .addArguments({"double"})
                                           .setDescription("Seed for random number generator")
                        )
                        .addOption(Option("start")
                                            .addAliases({"-s", "--start"})
                                            .addArguments({"int", "int"})
                                            .setDescription("Start position of maze")
                                            .setDefaults({0, 0})
                        )
                        .addOption(Option("end")
                                            .addAliases({"-e", "--end"})
                                            .addArguments({"int", "int"})
                                            .setDescription("End position of maze")
                                            .setDefaults({-1, -1})
                        )
                        .addOption(Option("pathWidth")
                                           .addAliases({"-pw", "--pathWidth"})
                                           .addArguments({"int"})
                                           .setDescription("Path width between walls")
                                           .setDefaults({3})
                        )
                        .addOption(Option("wallWidth")
                                           .addAliases({"-ww", "--wallWidth"})
                                           .addArguments({"int"})
                                           .setDescription("Wall width between paths")
                                           .setDefaults({1})
                        )
                        .addOption(Option("file")
                                            .addAliases({"-f", "--file"})
                                            .addArguments({"string"})
                                            .setDescription("Path to file")
                        )
                        .addOption(Option("image")
                                            .addAliases({"-i", "--image"})
                                            .addArguments({"string"})
                                            .setDescription("Path to image")
                        )
                        .returns([=](std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> map) {

                            std::string algorithm;
                            int width = 0;
                            int height = 0;
                            unsigned int seed = time(nullptr);

                            if (map["algorithm"].has_value()) {
                                // TODO: Get algorithm from map
                                algorithm = std::get<std::string>(map["algorithm"].value()[0]);
                            }

                            if (map["width"].has_value()) {
                                width = std::get<int>(map["width"].value()[0]);
                            }

                            if (map["height"].has_value()) {
                                height = std::get<int>(map["height"].value()[0]);
                            }

                            if (map["seed"].has_value()) {
                                seed = static_cast<unsigned int>(std::get<double>(map["seed"].value()[0]));
                            }

                            cout << endl;
                            cout << " mazelib: Generating maze..." << endl;
                            cout << " mazelib:  - Algorithm: " << algorithm << endl;
                            cout << " mazelib:  - Width: " << width << endl;
                            cout << " mazelib:  - Height: " << height << endl;

                            MazeBuilder builder = KruskalAlgorithm(seed).generate(width, height);

                            if (map["start"].has_value()) {
                                int x = std::get<int>(map["start"].value()[0]);
                                int y = std::get<int>(map["start"].value()[1]);

                                builder.setStart({x, y});

                                if (builder.isValid().has_value()) {
                                    cout << " mazelib:  - Start: " << x << " " << y << " (invalid)" << endl;
                                    return 1;
                                } else {
                                    cout << " mazelib:  - Start: " << x << " " << y << endl;
                                }
                            }

                            if (map["end"].has_value()) {
                                int x = std::get<int>(map["end"].value()[0]);
                                int y = std::get<int>(map["end"].value()[1]);

                                if (x == -1 && y == -1) {
                                    x = width - 1;
                                    y = height - 1;
                                }

                                builder.setEnd({x,y});

                                if (builder.isValid().has_value()) {
                                    cout << " mazelib:  - End: " << x << " " << y << " (invalid)" << endl;
                                    return 1;
                                } else {
                                    cout << " mazelib:  - End: " << x << " " << y << endl;
                                }
                            }

                            if (map["wallWidth"].has_value()) {
                                int wallWidth = std::get<int>(map["wallWidth"].value()[0]);

                                builder.setWallWidth(wallWidth);

                                if (builder.isValid().has_value()) {
                                    cout << " mazelib:  - Wall Width: " << wallWidth << " (invalid)" << endl;
                                    return 1;
                                } else {
                                    cout << " mazelib:  - Wall Width: " << wallWidth << endl;
                                }
                            }

                            if (map["pathWidth"].has_value()) {
                                int pathWidth = std::get<int>(map["pathWidth"].value()[0]);

                                builder.setPathWidth(pathWidth);

                                if (builder.isValid().has_value()) {
                                    cout << " mazelib:  - Path Width: " << pathWidth << " (invalid)" << endl;
                                    return 1;
                                } else {
                                    cout << " mazelib:  - Path Width: " << pathWidth << endl;
                                }
                            }

                            Maze maze = builder.build();

                            if (map["file"].has_value() || map["image"].has_value()) {

                                if (map["image"].has_value()) {
                                    std::string image = std::get<std::string>(map["image"].value()[0]);

                                    cout << " mazelib:  - Image Path: " << image << endl;

                                    int status = ImageSavingMethod().save(maze,image).valueOr(1);

                                    if (status == 0) {
                                        cout << " mazelib:     - Image saved successfully" << endl;
                                    } else {
                                        cout << " mazelib:     - Image saving failed" << endl;
                                    }
                                }

                                if (map["file"].has_value()) {
                                    std::string file = std::get<std::string>(map["file"].value()[0]);

                                    cout << " mazelib:  - File Path: " << file << endl;

                                    int status = TextFileSavingMethod().save(maze, file).valueOr(1);

                                    if (status == 0) {
                                        cout << " mazelib:     - File saved successfully" << endl;
                                    } else {
                                        cout << " mazelib:     - File saving failed" << endl;
                                    }
                                }
                            }

                            cout << endl;
                            return 0;
                        })
    );

    interface.addCategory(Category()
                        .setName("solve")
                        .setDescription("Solve maze from file or image")
                        .setUsage("mazelib solve [options]")
                        .addOption(Option("file")
                                            .addAliases({"-f", "--file"})
                                            .addArguments({"string"})
                                            .setDescription("Path to input file")
                                            .setRequired(true)
                        )
                        .addOption(Option("image")
                                            .addAliases({"-i", "--image"})
                                            .addArguments({"string"})
                                            .setDescription("Path to output image")
                        )
                        .addOption(Option("algorithm")
                                            .addAliases({"-a", "--algorithm"})
                                            .addArguments({"string"})
                                            .setDescription("Algorithm to solve maze")
                                            .setRequired(true)
                        )
                        .addOption(Option("gap")
                                            .addAliases({"-g", "--gap"})
                                            .addArguments({"int"})
                                            .setDescription("Gap between cells")
                                            .setDefaults({"3"})
                        )
                        .addOption(Option("path")
                                            .addAliases({"-p", "--path"})
                                            .setDescription("Show path from start to end")
                        )
                        .returns([=](std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> map) {
                            cout << endl << " Parsed Arguments:" << endl;

                            for (auto const& [key, val] : map) {
                                cout << key << " : ";

                                if (val != std::nullopt) {
                                    for (auto const& v : val.value()) {
                                        if (v.index() == 0) {
                                            cout << std::get<int>(v) << " 0 ";
                                        } else if (v.index() == 1) {
                                            cout << std::get<double>(v) << " 1 ";
                                        } else if (v.index() == 2) {
                                            cout << std::get<bool>(v) << " 2 ";
                                        } else if (v.index() == 3) {
                                            cout << std::get<std::string>(v) << " 3 ";
                                        }
                                    }
                                } else {
                                    cout << "null";
                                }

                                cout << endl;
                            }

                            return 0;
                        })
    );

    interface.addCategory(Category()
                        .setName("algorithms")
                        .setDescription("Show available algorithms")
                        .setUsage("mazelib algorithms")
                        .addOption(Option("order")
                                            .addAliases({"-o", "--order"})
                                            .addArguments({"string"})
                                            .setDescription("Order of algorithms")
                                            .setDefaults({"name"})
                        )
                        .addOption(Option("type")
                                            .addAliases({"-t", "--type"})
                                            .addArguments({"string"})
                                            .setDescription("Type of algorithms")
                                            .setDefaults({"all"})
                        )
                      .returns([=](std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> map) {
                            cout << endl << " Parsed Arguments:" << endl;

//                          for (auto const& [key, val] : map) {
//                              cout << key << " : ";
//
//                              if (val != std::nullopt) {
//                                  for (auto const& v : val.value()) {
//                                      if (v.index() == 0) {
//                                          cout << std::get<int>(v) << " 0 ";
//                                      } else if (v.index() == 1) {
//                                          cout << std::get<double>(v) << " 1 ";
//                                      } else if (v.index() == 2) {
//                                          cout << std::get<bool>(v) << " 2 ";
//                                      } else if (v.index() == 3) {
//                                          cout << std::get<std::string>(v) << " 3 ";
//                                      }
//                                  }
//                              } else {
//                                  cout << "null";
//                              }
//
//                              cout << endl;
//                          }

                            return 0;
                        })
    );

    interface.addCategory(Category()
                          .setName("help")
                          .addAliases({"--help", "-h"})
                          .setDescription("Show help message")
                          .setUsage("mazelib help")
                          .returns([=]() {
                              cout << HEADER;
                              cout << "" << endl;
                              cout << " Format: mazelib <cmd> [options]" << endl;
                              cout << "" << endl;
                              cout << " Commands:" << endl;
                              cout << "    help                         | Show program help message (this)" << endl;

                              for (const auto& category : interface.getCategories()) {
                                  std::cout << "    ";

                                  std::string aliases;
                                  aliases += category->getName() + ", ";
                                  for (const auto& alias : category->getAliases()) {
                                      aliases += alias + ", ";
                                  }
                                  aliases = aliases.substr(0,aliases.size() - 2);

                                  std::cout << std::setw(20) << std::left << aliases << "\t | ";
                                  std::cout << std::setw(50) << std::left << category->getDescription() << std::endl;
                              }

                              cout << "" << endl;
                              cout << " Options:" << endl;
                              cout << "  -h, --help      | Show this help message and exit          | [boolean]" << endl;
                              cout << "  -v, --version   | Show programs version number and exit    | [boolean]" << endl;
                              cout << "" << endl;

                              return 0;
                          })
    );

    return interface.run(argc, argv);
}