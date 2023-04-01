#include "headers/Head.h"

using namespace std;

int main(int argc, char **argv) {
//    example();

    Interface interface = Interface();
    interface.setUsage("mazelib: Unknown command, try 'mazelib --help' for more information!");

    // Unknown command
    interface.setDefault([=]() {
        cout << endl << interface.getUsage() << endl;
        return 0;
    });

    // Version command
    Category version = Category("version")
            .addAliases({"ver", "--version", "-v"})
            .setDescription("Show programs version number")
            .setUsage("mazelib version")
            .returns([=]() {
                cout << endl << " mazelib: Version " << VERSION << endl;
                return 0;
            });
    interface.addCategory(version);

    // Generate command
    Category generate = Category("generate")
            .addAliases({"gen"})
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
                               .setDescription("Seed of the maze")
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
                               .setDescription("Width of the path between walls")
                               .setDefaults({3})
            )
            .addOption(Option("wallWidth")
                               .addAliases({"-ww", "--wallWidth"})
                               .addArguments({"int"})
                               .setDescription("Width of wall between paths")
                               .setDefaults({1})
            )
            .addOption(Option("file")
                               .addAliases({"-f", "--file"})
                               .addArguments({"string"})
                               .setDescription("Path to the file, where maze will be saved")
            )
            .addOption(Option("image")
                               .addAliases({"-i", "--image"})
                               .addArguments({"string"})
                               .setDescription("Path to the image, where maze will be saved")
            )
            .returns(
                    [=](std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> map) {

                        // Required arguments
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

                        std::shared_ptr<GeneratingAlgorithm> generatingAlgorithm = Algorithm::getGenerator(algorithm, seed);

                        // Check if algorithm exists
                        if (generatingAlgorithm == nullptr) {
                            cout << endl;
                            cout << " mazelib: Maze generation failed. " << endl;
                            cout << " mazelib:  - Error: Unknown algorithm '" << algorithm << "'" << endl;
                            return 1;
                        } else {
                            cout << endl;
                            cout << " mazelib: Generating maze..." << endl;
                            cout << " mazelib:  - Algorithm: " << generatingAlgorithm->getName() << endl;
                            cout << " mazelib:  - Width: " << width << endl;
                            cout << " mazelib:  - Height: " << height << endl;
                        }

                        Expected<MazeBuilder> expectedBuilder = generatingAlgorithm->generate(width, height);
                        // TODO-Extra: Add loading bar for process of generating maze

                        // Check if maze generation failed
                        if (expectedBuilder.hasError()) {
                            cout << endl;
                            cout << " mazelib: Maze generation failed. " << endl;
                            cout << " mazelib:  - Errors: " << endl;

                            for (const auto& error: expectedBuilder.errors()) {
                                cout << " mazelib:     - " << error << endl;
                            }

                            return 1;
                        }

                        MazeBuilder builder = expectedBuilder.value();

                        // Set maze start point
                        if (map["start"].has_value()) {
                            int x = std::get<int>(map["start"].value()[0]);
                            int y = std::get<int>(map["start"].value()[1]);

                            builder.setStart({x, y});

                            cout << " mazelib:  - Start: (" << x << ", " << y << ")" << endl;
                        }

                        // Set maze end point
                        if (map["end"].has_value()) {
                            int x = std::get<int>(map["end"].value()[0]);
                            int y = std::get<int>(map["end"].value()[1]);

                            if (x == -1 && y == -1) {
                                x = width - 1;
                                y = height - 1;
                            }

                            builder.setEnd({x,y});

                            cout << " mazelib:  - End: (" << x << ", " << y << ")" << endl;
                        }

                        // Set maze wall width
                        if (map["wallWidth"].has_value()) {
                            int wallWidth = std::get<int>(map["wallWidth"].value()[0]);

                            builder.setWallWidth(wallWidth);

                            cout << " mazelib:  - Wall Width: " << wallWidth << endl;
                        }

                        // Set maze path width
                        if (map["pathWidth"].has_value()) {
                            int pathWidth = std::get<int>(map["pathWidth"].value()[0]);

                            builder.setPathWidth(pathWidth);

                            cout << " mazelib:  - Path Width: " << pathWidth << endl;
                        }

                        Expected<Maze> expectedMaze = builder.buildExpected();

                        // Check if maze is valid
                        if (expectedMaze.hasError()) {
                            cout << endl;
                            cout << " mazelib: Maze building failed. " << endl;
                            cout << " mazelib:  - Errors: " << endl;

                            for (const auto& error: expectedMaze.errors()) {
                                cout << " mazelib:     - " << error << endl;
                            }

                            return 1;
                        }

                        Maze maze = expectedMaze.value();

                        // Saving methods
                        if (map["file"].has_value() || map["image"].has_value()) {

                            if (map["image"].has_value()) {
                                std::string image = std::get<std::string>(map["image"].value()[0]);

                                cout << " mazelib:  - Image Path: " << image << endl;

                                Expected<int> status = ImageSavingMethod().save(maze,image);

                                if (status.hasError()) {
                                    cout << " mazelib:     - Image saving failed. Error: " << status.error() << endl;
                                } else {
                                    cout << " mazelib:     - Image saved successfully!" << endl;
                                }
                            }

                            if (map["file"].has_value()) {
                                std::string file = std::get<std::string>(map["file"].value()[0]);

                                cout << " mazelib:  - File Path: " << file << endl;

                                Expected<int> status = TextFileSavingMethod().save(maze,file);

                                if (status.hasError()) {
                                    cout << " mazelib:     - File saving failed. Error: " << status.error() << endl;
                                } else {
                                    cout << " mazelib:     - File saved successfully!" << endl;
                                }
                            }

                        }

                        cout << " mazelib: Maze generated successfully! Took: " << (maze.getGenerationTime()  / 1000) << "us" << endl;

                        return 0;
                    });
    interface.addCategory(generate);

    // Solving command
    Category solve = Category("solve")
            .setDescription("Solve maze from file or image")
            .setUsage("mazelib solve [options]")
            .addOption(Option("file")
                               .addAliases({"-fi", "--fileIn"})
                               .addArguments({"string"})
                               .setDescription("Path to the input file of maze")
                               .setRequired(true)
            )
            .addOption(Option("algorithm")
                               .addAliases({"-a", "--algorithm"})
                               .addArguments({"string"})
                               .setDescription("Algorithm to solve maze")
                               .setRequired(true)
            )
            .addOption(Option("pathWidth")
                               .addAliases({"-pw", "--pathWidth"})
                               .addArguments({"int"})
                               .setDescription("Width of the path between walls")
                               .setDefaults({3})
            )
            .addOption(Option("wallWidth")
                               .addAliases({"-ww", "--wallWidth"})
                               .addArguments({"int"})
                               .setDescription("Width of wall between paths")
                               .setDefaults({1})
            )
            .addOption(Option("fileOutput")
                               .addAliases({"-fo", "--fileOut"})
                               .addArguments({"string"})
                               .setDescription("Path to the file, where maze will be saved")
            )
            .addOption(Option("image")
                               .addAliases({"-i", "--image"})
                               .addArguments({"string"})
                               .setDescription("Path to the image, where maze will be saved")
            )
            .returns(
                    [=](std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> map) {
                        cout << endl << " Parsed Arguments:" << endl;

                        for (auto const &[key, val]: map) {
                            cout << key << " : ";

                            if (val != std::nullopt) {
                                for (auto const &v: val.value()) {
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

                        // TODO: Implement solving method

                        return 0;
                    });
    interface.addCategory(solve);

    // Testing command
    Category test = Category("test")
            .setDescription("Test algorithms")
            .setUsage("mazelib test [options]")
            .addOption(Option("fileInput")
                               .addAliases({"-fi", "--fileIn"})
                               .addArguments({"string"})
                               .setDescription("Path to the file, from which maze will be loaded")
                               .setRequired(true)
            )
            .addOption(Option("algorithms")
                               .addAliases({"-a", "--algorithm"})
                               .addArguments({"string"})
                               .setDescription("Algorithms to test, separated by commas")
                               .setDefaults({"all"})
            )
            .addOption(Option("fileOutput")
                               .addAliases({"-fo", "--fileOut"})
                               .addArguments({"string"})
                               .setDescription("Path to the file, where maze will be saved")
            )
            .addOption(Option("table")
                               .addAliases({"-t", "--table"})
                               .setDescription("Output results printed in table")
            )
            .returns(
                    [=](std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> map) {

                        auto startTime = std::chrono::high_resolution_clock::now();

                        std::string input = std::get<std::string>(map["fileInput"].value()[0]);
                        Expected<MazeBuilder> loader = TextFileLoadingMethod().load(input);

                        cout << "" << endl;
                        cout << " mazelib: Starting maze testing" << endl;
                        cout << "" << endl;
                        cout << " mazelib:  Gathering input: " << endl;
                        cout << " mazelib:  - Input file: " << input << endl;

                        // Check if loading was successful
                        if (loader.hasError()) {
                            cout << " mazelib:     - Loading failed. Error: " << loader.error() << endl;
                            return 1;
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
                        for (const auto &alg: Algorithm::getSolvers()) {
                            std::string name = alg->getName();
                            std::transform(name.begin(), name.end(), name.begin(), ::tolower);

                            // Check if algorithm name is in target
                            if (target == "all" || target.find(name) != std::string::npos) {
                                algorithms.push_back(alg);
                            }
                        }

                        // Check if any algorithms was found
                        if (algorithms.empty()) {
                            cout << " mazelib:     - No algorithms was found. " << endl;
                            return 1;
                        }

                        Maze loadedMaze = builder.build();

                        cout << endl;
                        cout << " mazelib: Testing algorithms: " << endl;

                        // TODO: Save results to file if fileOutput is set

                        // Show out as table
                        if (std::get<bool>(map["table"].value()[0])) {
                            int nameLength = 0;
                            for (const auto &alg: algorithms) {
                                int len = static_cast<int>(alg->getName().length());

                                if (len > nameLength) {
                                    nameLength = len;
                                }
                            }

                            // Print table header
                            // TODO-Extra: Add centering
                            cout << " mazelib: " << left << string(nameLength,'-') << " | " << "-------" << " | " << "------------" << " | " << "----------" << endl;
                            cout << " mazelib: " << left << setw(nameLength) << "Algorithm Name" << " | " << "Status " << " | " << "Path Length " << " | " << "Time" << endl;
                            cout << " mazelib: " << left << string(nameLength,'-') << " | " << "-------" << " | " << "------------" << " | " << "----------" << endl;

                            // Test all algorithms
                            for (const auto &alg: algorithms) {
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
                                cout << (path.getSolvingTime() / 1000) << "us" << endl;

                                ImageSavingMethod().save(loadedMaze, "path-" + alg->getName() + ".png", path);
                            }
                        } else {
                            // Test all algorithms
                            for (const auto &alg: algorithms) {
                                cout << " mazelib:  - " << alg->getName() << endl;

                                Expected<MazePath> mazePath = alg->solve(loadedMaze);

                                if (mazePath.hasError()) {
                                    cout << " mazelib:    - Solving failed. Error: " << mazePath.error() << endl;
                                    continue;
                                }

                                MazePath path = mazePath.value();

                                cout << " mazelib:    - Path length: " << mazePath.value().getLength() << endl;
                                cout << " mazelib:    - Time taken: " << (path.getSolvingTime() / 1000) << "us" << endl;
                            }
                        }

                        auto endTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

                        cout << endl << " mazelib: Testing finished! Total time taken: " << (duration / 1000) << "us" << endl;

                        return 0;
                    });
    interface.addCategory(test);

    // Add algorithms command
    Category algorithms = Category("algorithms")
            .addAliases({"algs", "algos"})
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
                               .setDescription("Hide description of algorithms")
            )
            .returns(
                    [=](std::map<std::string, std::optional<std::vector<std::variant<int, double, bool, std::string, std::nullopt_t>>>> map) {

                        std::string order = std::get<std::string>(map["order"].value()[0]);
                        std::transform(order.begin(), order.end(), order.begin(), ::tolower);

                        // Check for valid order
                        if (order != "name" && order != "type" && order != "both") {
                            cout << " mazelib: Invalid order of algorithms. Available: 'name', 'type'." << endl;
                            return 1;
                        }

                        std::string type = std::get<std::string>(map["type"].value()[0]);
                        std::transform(type.begin(), type.end(), type.begin(), ::tolower);

                        // Check for valid type
                        if (type != "all" && type != "generating" && type != "solving") {
                            cout << " mazelib: Invalid type of algorithms. Available: 'all', 'generating', 'solving'." << endl;
                            return 1;
                        }

                        std::vector<std::shared_ptr<Algorithm>> algorithms = Algorithm::getAlgorithms();

                        // Sort algorithms
                        if (order == "name") {
                            std::sort(algorithms.begin(), algorithms.end(),[](const std::shared_ptr<Algorithm> &a, const std::shared_ptr<Algorithm> &b) {
                                return a->getName() < b->getName();
                            });
                        } else if (order == "type") {
                            std::sort(algorithms.begin(), algorithms.end(),[](const std::shared_ptr<Algorithm> &a, const std::shared_ptr<Algorithm> &b) {
                                return a->getType() < b->getType();
                            });
                        } else if (order == "both") {
                            std::sort(algorithms.begin(), algorithms.end(),[](const std::shared_ptr<Algorithm> &a, const std::shared_ptr<Algorithm> &b) {
                                return a->getType() + a->getName() < b->getType() + b->getName();
                            });
                        }

                        cout << "" << endl;
                        cout << " mazelib: Available Algorithms: " << endl;

                        int nameLength = 0;
                        for (const auto &alg: algorithms) {
                            int len = static_cast<int>(alg->getName().length());

                            if (len > nameLength) {
                                nameLength = len;
                            }
                        }

                        // Print algorithms
                        for (const auto &algorithm: algorithms) {
                            if (type == "all" ||
                                (type == "generating" && algorithm->getType() == "generating") ||
                                (type == "solving" && algorithm->getType() == "solving")) {

                                if (!std::get<bool>(map["desc"].value()[0])) {
                                    cout << " mazelib:  - " << algorithm->getName() << endl;
                                    cout << " mazelib:     - Type: " << (algorithm->getType() == "generating" ? "Generating" : "Solving") << endl;
                                    cout << " mazelib:     - Complexity: " << algorithm->getComplexity() << endl;
                                    cout << " mazelib:     - Description: " << endl;

                                    std::string description = algorithm->getDescription();

                                    while (description.size() > 100) {
                                        int i = 100;

                                        while (description[i] != ' ') {
                                            i--;
                                        }

                                        cout << " mazelib:         " << description.substr(0, i) << endl;

                                        description = description.substr(i + 1);
                                    }

                                    cout << " mazelib:         " << description << endl;
                                } else {
                                    cout << " mazelib:  - " << std::setw(nameLength) << std::left << algorithm->getName();
                                    cout << " | " << std::setw(10) << std::left << (algorithm->getType() == "generating" ? "Generating" : "Solving");
                                    cout << " | " << std::setw(10) << std::left << algorithm->getComplexity();
                                    cout << endl;
                                }
                            }
                        }

                        return 0;
                    });
    interface.addCategory(algorithms);

    // Add help command
    Category help = Category("help")
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

                for (const auto &category: interface.getCategories()) {
                    std::cout << "    ";

                    std::string aliases;
                    aliases += category.getName() + ", ";
                    for (const auto &alias: category.getAliases()) {
                        if (alias[0] == '-') continue;

                        aliases += alias + ", ";
                    }
                    aliases = aliases.substr(0, aliases.size() - 2);

                    std::cout << std::setw(20) << std::left << aliases << "\t | ";
                    std::cout << std::setw(50) << std::left << category.getDescription() << std::endl;
                }

                cout << "" << endl;
                cout << " Options:" << endl;
                cout << "  -h, --help      | Show this help message and exit          | [boolean]" << endl;
                cout << "  -v, --version   | Show programs version number and exit    | [boolean]" << endl;
                cout << "" << endl;

                return 0;
            });
    interface.addCategory(help);

    return interface.run(argc, argv);
}