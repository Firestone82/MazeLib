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
                        .addOption(Option("gap")
                                            .addAliases({"-g", "--gap"})
                                            .addArguments({"int"})
                                            .setDescription("Gap between cells")
                                            .setDefaults({3})
                        )
                        .addOption(Option("path")
                                            .addAliases({"-p", "--path"})
                                            .setDescription("Show path from start to end")
                        )
                        .returns([=](std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> map) {

                            for (auto const& [key, val] : map) {
                                cout << key << " : ";

                                if (val != std::nullopt) {
                                    for (auto const& v : val.value()) {
                                        if (v.index() == 0) {
                                            cout << std::get<int>(v) << " ";
                                        } else if (v.index() == 1) {
                                            cout << std::get<double>(v) << " ";
                                        } else if (v.index() == 2) {
                                            cout << std::get<bool>(v) << " ";
                                        } else if (v.index() == 3) {
                                            cout << std::get<std::string>(v) << " ";
                                        } else {
                                            cout << "nullopt ";
                                        }
                                    }
                                } else {
                                    cout << "null";
                                }

                                cout << endl;
                            }

                            std::string algorithm;

                            if (map["algorithm"].has_value()) {
                                algorithm = std::get<std::string>(map["algorithm"].value()[0]);
                            }

                            int width = 0;
                            int height = 0;

                            if (map["width"].has_value()) {
                                width = std::get<int>(map["width"].value()[0]);
                            }

                            if (map["height"].has_value()) {
                                height = std::get<int>(map["height"].value()[0]);
                            }

                            unsigned int seed = time(nullptr);

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

                                if (!builder.isValid()) {
                                    cout << " mazelib:  - Start: " << x << " " << y << " (invalid)" << endl;
                                    return 1;
                                } else {
                                    cout << " mazelib:  - Start: " << x << " " << y << endl;
                                }
                            }

                            if (map["end"].has_value()) {
                                int x = std::get<int>(map["end"].value()[0]);
                                int y = std::get<int>(map["end"].value()[1]);

                                builder.setEnd({x, y});

                                if (!builder.isValid()) {
                                    cout << " mazelib:  - End: " << x << " " << y << " (invalid)" << endl;
                                    return 1;
                                } else {
                                    cout << " mazelib:  - End: " << x << " " << y << endl;
                                }
                            }

                            if (map["path"].has_value()) {
//                                builder.setPath(true);

                                cout << " mazelib:  - Path: true" << endl;
                            }

                            if (map["gap"].has_value()) {
                                int gap = std::get<int>(map["gap"].value()[0]);

//                                builder.setGap(gap);

                                cout << " mazelib:  - Gap: " << gap << endl;
                            }


//                            if (map["file"].index)) {
//                                cout << " mazelib:  - File: " << get<string>(map["file"][0]) << endl;
//                            }
//
//                            if (!map["image"].empty()) {
//                                cout << " mazelib:  - Image: " << get<string>(map["image"][0]) << endl;
//                            }

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