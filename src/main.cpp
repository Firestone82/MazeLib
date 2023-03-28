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
                        .setAliases({"--version", "-v"})
                        .setDescription("Show programs version number")
                        .setUsage("mazelib version")
                        .returns([=]() {
                            cout << endl << " mazelib: Version " << VERSION << endl;
                            return 0;
                        })
    );

    interface.addCategory(Category()
                        .setName("generate")
                        .setAliases({"gen"})
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

                            std::shared_ptr<GeneratingAlgorithm> generatingAlgorithm = GeneratingAlgorithm::getGenerator(algorithm, seed);

                            if (generatingAlgorithm == nullptr) {
                                cout << endl;
                                cout << " mazelib: Maze generation failed. " << endl;
                                cout << " mazelib:  - Error: Unknown algorithm '" << algorithm << "'" << endl;
                                return 1;
                            } else {
                                cout << endl;
                                cout << " mazelib: Generating maze..." << endl;
                                cout << " mazelib:  - Algorithm: " << algorithm << endl;
                                cout << " mazelib:  - Width: " << width << endl;
                                cout << " mazelib:  - Height: " << height << endl;
                            }

                            Expected<MazeBuilder> expectedBuilder = generatingAlgorithm->generate(width, height);

                            if (expectedBuilder.hasError()) {
                                cout << endl;
                                cout << " mazelib: Maze generation failed. " << endl;
                                cout << " mazelib:  - Error: " << expectedBuilder.error() << endl;
                                return 2;
                            }

                            MazeBuilder builder = expectedBuilder.value();

                            if (map["start"].has_value()) {
                                int x = std::get<int>(map["start"].value()[0]);
                                int y = std::get<int>(map["start"].value()[1]);

                                builder.setStart({x, y});

                                cout << " mazelib:  - Start: " << x << " " << y << endl;
                            }

                            if (map["end"].has_value()) {
                                int x = std::get<int>(map["end"].value()[0]);
                                int y = std::get<int>(map["end"].value()[1]);

                                if (x == -1 && y == -1) {
                                    x = width - 1;
                                    y = height - 1;
                                }

                                builder.setEnd({x,y});

                                cout << " mazelib:  - End: " << x << " " << y << endl;
                            }

                            if (map["wallWidth"].has_value()) {
                                int wallWidth = std::get<int>(map["wallWidth"].value()[0]);

                                builder.setWallWidth(wallWidth);

                                cout << " mazelib:  - Wall Width: " << wallWidth << endl;
                            }

                            if (map["pathWidth"].has_value()) {
                                int pathWidth = std::get<int>(map["pathWidth"].value()[0]);

                                builder.setPathWidth(pathWidth);

                                cout << " mazelib:  - Path Width: " << pathWidth << endl;
                            }

                            Maze maze = builder.build();
                            auto errors = maze.isValid();

                            if (errors.has_value()) {
                                cout << endl;
                                cout << " mazelib: Maze generation failed. " << endl;
                                cout << " mazelib:  - Errors: " << endl;

                                for (const auto& error : errors.value()) {
                                    cout << " mazelib:     - " << error << endl;
                                }

                                return 3;
                            }

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
                        .setName("test")
                        .setDescription("Test algorithms")
                        .setUsage("mazelib test [options]")
                        .addOption(Option("input")
                                            .addAliases({"-i", "--input"})
                                            .addArguments({"string"})
                                            .setDescription("Path to input file")
                                            .setRequired(true)
                        )
                        .addOption(Option("output")
                                            .addAliases({"-o", "--output"})
                                            .addArguments({"string"})
                                            .setDescription("Path to output file")
                        )
                        .addOption(Option("algorithms")
                                            .addAliases({"-a", "--algorithms"})
                                            .addArguments({"string"})
                                            .setDescription("Algorithms to test, separated by commas")
                                            .setDefaults({"all"})
                        )
                        .addOption(Option("table")
                                            .addAliases({"-t", "--table"})
                                            .setDescription("Output results in table")
                        )
                        .returns([=](std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> map) {

                            unsigned int start = std::clock();

                            std::string input = std::get<std::string>(map["input"].value()[0]);
                            Expected<MazeBuilder> loader = TextFileLoadingMethod().load(input);

                            cout << "" << endl;
                            cout << " mazelib: Starting maze testing: " << endl;
                            cout << " mazelib:  - Input file: " << input << endl;

                            // Check if loading was successful
                            if (loader.hasError()) {
                                cout << " mazelib:     - Loading failed. Error: " << loader.error() << endl;
                                return 1;
                            } else {
                                cout << " mazelib:     - Loading successful" << endl;
                            }

                            MazeBuilder builder = loader.value();

                            // Print maze info
                            cout << " mazelib:  - Maze info:" << endl;
                            cout << " mazelib:    - Generated by: " << builder.getGenerationAlgorithm() << endl;
                            cout << " mazelib:    - Width: " << builder.getWidth() << endl;
                            cout << " mazelib:    - Height: " << builder.getHeight() << endl;

                            std::vector<std::shared_ptr<SolvingAlgorithm>> algorithms;
                            std::string target = std::get<std::string>(map["algorithms"].value()[0]);
                            std::transform(target.begin(),target.end(),target.begin(),::tolower);

                            cout << " mazelib:  - Algorithms: " << target << endl;

                            // Get all solving algorithms by user input
                            for (const auto& alg : Algorithm::getAlgorithms()) {
                                if (alg->getType() == "generating") continue;

                                std::string name = alg->getName();
                                std::transform(name.begin(),name.end(),name.begin(),::tolower);

                                // Check if algorithm name is in target
                                if (target == "all" || target.find(name) != std::string::npos) {
                                    algorithms.push_back(std::dynamic_pointer_cast<SolvingAlgorithm>(alg));
                                }
                            }

                            // Check if any algorithms was found
                            if (algorithms.empty()) {
                                cout << " mazelib:     - No algorithms was found. " << endl;
                                return 1;
                            } else {
                                cout << " mazelib:     - " << algorithms.size() << " algorithms was found. " << endl;
                            }

                            Maze loadedMaze = builder.build();
                            cout << endl;

                            // Show out as table
                            if (std::get<bool>(map["table"].value()[0])) {
                                int nameLength = 0;
                                for (const auto& alg : algorithms) {
                                    if (alg->getName().length() > nameLength) {
                                        nameLength = alg->getName().length();
                                    }
                                }

                                // Print table header
                                cout << " mazelib: ";
                                cout << setw(nameLength) << left << "Algorithm" << " | ";
                                cout << setw(7)          << left << "STATUS" << " | " ;
                                cout << setw(12)         << left << "Path Length" << " | ";
                                cout << "Time" << endl;

                                // Print table line
                                cout << " mazelib: ";
                                cout << string(nameLength,'-') << " | ";
                                cout << string(7, '-') << " | ";
                                cout << string(12, '-') << " | ";
                                cout << string(10, '-') << endl;

                                // Test all algorithms
                                for (const auto& alg : algorithms) {
                                    cout << " mazelib: ";
                                    cout << setw(nameLength) << left << alg->getName() << " | ";

                                    Expected<MazePath> mazePath = alg->solve(loadedMaze);

                                    if (mazePath.hasError()) {
                                        cout << setw(7) << left << "FAILED" << " | ";
                                        cout << setw(12) << left << "N/A" << " | ";
                                        cout << "N/A" << endl;
                                        continue;
                                    }

                                    MazePath path = mazePath.value();

                                    cout << setw(7) << left << "SUCCESS" << " | ";
                                    cout << setw(12) << left << path.getLength() << " | ";
                                    cout << path.getSolvingTime() << "ms" << endl;
                                }

                                cout << endl;
                            } else {
                                cout << " mazelib: Testing algorithms: " << endl;

                                // Test all algorithms
                                for (const auto& alg : algorithms) {
                                    cout << " mazelib:  - " << alg->getName() << endl;

                                    Expected<MazePath> mazePath = alg->solve(loadedMaze);

                                    if (mazePath.hasError()) {
                                        cout << " mazelib:    - Solving failed. Error: " << mazePath.error() << endl;
                                        continue;
                                    }

                                    MazePath path = mazePath.value();

                                    cout << " mazelib:    - Path length: " << mazePath.value().getLength() << endl;
                                    cout << " mazelib:    - Time taken: " << path.getSolvingTime() << "ms" << endl;
                                }

                                cout << endl;
                            }

                            cout << " mazelib: Total time taken: " << (std::clock() - start) / (double) CLOCKS_PER_SEC << "s" << endl;

                            return 0;
                        })
    );

    interface.addCategory(Category()
                        .setName("algorithms")
                        .setAliases({"algs", "algos"})
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
                        .addOption(Option("desc")
                                            .addAliases({"-d", "--description"})
                                            .setDescription("Show description of algorithms")
                        )
                        .returns([=](std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> map) {

                            std::string order = std::get<std::string>(map["order"].value()[0]);
                            std::transform(order.begin(),order.end(),order.begin(),::tolower);

                            // Check for valid order
                            if (order != "name" && order != "type" && order != "both") {
                                cout << " mazelib: Invalid order of algorithms. Available: 'name', 'type'." << endl;
                                return 1;
                            }

                            std::string type = std::get<std::string>(map["type"].value()[0]);
                            std::transform(type.begin(),type.end(),type.begin(),::tolower);

                            // Check for valid type
                            if (type != "all" && type != "generating" && type != "solving") {
                                cout << " mazelib: Invalid type of algorithms. Available: 'all', 'generating', 'solving'." << endl;
                                return 1;
                            }

                            std::vector<std::shared_ptr<Algorithm>> algorithms = Algorithm::getAlgorithms();

                            // Sort algorithms
                            if (order == "name") {
                                std::sort(algorithms.begin(),algorithms.end(),[](const std::shared_ptr<Algorithm>& a, const std::shared_ptr<Algorithm>& b) {
                                    return a->getName() < b->getName();
                                });
                            } else if (order == "type") {
                                std::sort(algorithms.begin(),algorithms.end(),[](const std::shared_ptr<Algorithm>& a, const std::shared_ptr<Algorithm>& b) {
                                    return a->getType() < b->getType();
                                });
                            } else if (order == "both") {
                                std::sort(algorithms.begin(),algorithms.end(),[](const std::shared_ptr<Algorithm>& a, const std::shared_ptr<Algorithm>& b) {
                                    return a->getType() + a->getName() < b->getType() + b->getName();
                                });
                            }

                            cout << "" << endl;
                            cout << " Available Algorithms: " << endl;

                            // Print algorithms
                            for (const auto& algorithm : algorithms) {
                                if (type == "all" || (type == "generating" && algorithm->getType() == "generating") || (type == "solving" && algorithm->getType() == "solving")) {
                                    if (std::get<bool>(map["desc"].value()[0])) {
                                        cout << "  - " << algorithm->getName() << endl;
                                        cout << "      - Type: " << (algorithm->getType() == "generating" ? "Generating" : "Solving") << endl;
                                        cout << "      - Complexity: " << algorithm->getComplexity() << endl;

                                        cout << "      - Description: " << endl;

                                        std::string description = algorithm->getDescription();

                                        while (description.size() > 100) {
                                            int i = 100;

                                            while (description[i] != ' ') {
                                                i--;
                                            }

                                            cout << "          " << description.substr(0,i) << endl;

                                            description = description.substr(i + 1);
                                        }

                                        cout << "          " << description << endl;
                                    } else {
                                        cout << "  - " << std::setw(20) << std::left << algorithm->getName();
                                        cout << " | " << std::setw(10) << std::left << (algorithm->getType() == "generating" ? "Generating" : "Solving");
                                        cout << " | " << std::setw(10) << std::left << algorithm->getComplexity();
                                        cout << endl;
                                    }
                                }
                            }

                            return 0;
                        })
    );

    interface.addCategory(Category()
                        .setName("help")
                        .setAliases({"--help", "-h"})
                        .setDescription("Show help message")
                        .setUsage("mazelib help")
                        .returns([=]() {
                            cout << HEADER;
                            cout << "" << endl;
                            cout << " Format: mazelib <cmd> [options]" << endl;
                            cout << "" << endl;
                            cout << " Commands:" << endl;
                            cout << "    help, --help, -h             | Show program help message (this)" << endl;

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