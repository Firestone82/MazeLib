#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

#include "../headers/Head.h"

namespace py = pybind11;
using namespace pybind11::literals;

// Define the conversion functions for the Expected<T> class
template <typename T>
void register_expected(py::module& m, const std::string& name) {
    py::class_<Expected<T>>(m, name.c_str())
            .def(py::init<T>())
            .def(py::init<std::string>())
            .def(py::init<std::vector<std::string>>())
            .def("value", &Expected<T>::value)
            .def("valueOr", &Expected<T>::valueOr)
            .def("__bool__", [](Expected<Maze> e) { return !e.hasError(); })
            .def("__repr__", [](Expected<T>& e) {
                if (e.hasError()) {
                    return py::str("Error: {}"_s.format(e.error()));
                } else {
                    return py::str("Value: {}"_s.format(e.value()));
                }
            })
            .def_property_readonly("error", &Expected<T>::error)
            .def_property_readonly("errors", &Expected<T>::errors)
            .def("hasError", &Expected<T>::hasError);
}

PYBIND11_MODULE(mazeLib, m) {
    register_expected<MazePath>(m, "MazePathExpected");
    register_expected<MazeBuilder>(m, "MazeBuilderExpected");
    register_expected<Maze>(m, "MazeExpected");
    register_expected<int>(m, "IntExpected");
    register_expected<std::vector<unsigned char>>(m,"VectorUnsignedCharExpected");

    // Bind the Algorithm class
    py::class_<Algorithm, std::shared_ptr<Algorithm>>(m,"Algorithm")
            .def(py::init<std::string, std::string>())
            .def(py::init<std::string, std::string, std::string>())
            .def(py::init<std::string, std::string, std::string, std::string>())
            .def("getName",&Algorithm::getName)
            .def("getType",&Algorithm::getType)
            .def("getComplexity",&Algorithm::getComplexity)
            .def("getDescription",&Algorithm::getDescription)
            .def_static("getAlgorithms",&Algorithm::getAlgorithms)
            .def_static("getGenerators",&Algorithm::getGenerators)
            .def_static("getGenerator",[=](const std::string& name) {
                return Algorithm::getGenerator(name);
            })
            .def_static("getGenerator", [=](const std::string& name, unsigned int seed) {
                return Algorithm::getGenerator(name, seed);
            })
            .def_static("getSolvers",&Algorithm::getSolvers)
            .def_static("getSolver",[=](const std::string& name) {
                return Algorithm::getSolver(name);
            });

    // Bind the GeneratingAlgorithm class
    py::class_<GeneratingAlgorithm, Algorithm, std::shared_ptr<GeneratingAlgorithm>>(m,"GeneratingAlgorithm")
    //      .def(py::init<std::string, unsigned int>())
            .def("setSeed",&GeneratingAlgorithm::setSeed);

    // Bind the KruskalAlgorithm class
    py::class_<KruskalAlgorithm, GeneratingAlgorithm, std::shared_ptr<KruskalAlgorithm>>(m,"KruskalAlgorithm")
            .def(py::init())
            .def(py::init<unsigned int>())
            .def("generate",&KruskalAlgorithm::generate);

    // Bind the SolvingAlgorithm class
    py::class_<SolvingAlgorithm, Algorithm, std::shared_ptr<SolvingAlgorithm>>(m,"SolvingAlgorithm")
    //      .def(py::init<std::string>())
            .def("solve",&SolvingAlgorithm::solve);

    // Bind the WallFollowingAlgorithm class
    py::class_<WallFollowingAlgorithm, SolvingAlgorithm, std::shared_ptr<WallFollowingAlgorithm>>(m,"WallFollowingAlgorithm")
            .def(py::init())
            .def("solve",&WallFollowingAlgorithm::solve);

    // Bind the TremauxsAlgorithm class
    py::class_<TremauxsAlgorithm, SolvingAlgorithm, std::shared_ptr<TremauxsAlgorithm>>(m,"TremauxsAlgorithm")
            .def(py::init())
            .def("solve",&TremauxsAlgorithm::solve);

    // Bind the BreadthFirstSearchAlgorithm class
    py::class_<BreadthFirstSearchAlgorithm, SolvingAlgorithm, std::shared_ptr<BreadthFirstSearchAlgorithm>>(m,"BreadthFirstSearchAlgorithm")
            .def(py::init())
            .def("solve",&BreadthFirstSearchAlgorithm::solve);

    // Bind the DepthFirstSearchAlgorithm class
    py::class_<DepthFirstSearchAlgorithm, SolvingAlgorithm, std::shared_ptr<DepthFirstSearchAlgorithm>>(m,"DepthFirstSearchAlgorithm")
            .def(py::init())
            .def("solve",&DepthFirstSearchAlgorithm::solve);

    // Bind the LeeAlgorithm class
    py::class_<LeeAlgorithm, SolvingAlgorithm, std::shared_ptr<LeeAlgorithm>>(m,"LeeAlgorithm")
            .def(py::init())
            .def("solve",&LeeAlgorithm::solve);

    // Bind the DijkstraAlgorithm class
    py::class_<DijkstraAlgorithm, SolvingAlgorithm, std::shared_ptr<DijkstraAlgorithm>>(m,"DijkstraAlgorithm")
            .def(py::init())
            .def("solve",&DijkstraAlgorithm::solve);

    // Bind the Node class
    py::class_<Node>(m,"Node")
            .def(py::init<int, int>())
            .def("getX",&Node::getX)
            .def("getY",&Node::getY)
            .def("setID",&Node::setID)
            .def("getID",&Node::getID)
            .def("addNeighbour",&Node::addNeighbour)
            .def("getNeighbours",&Node::getNeighbours)
            .def("__str__",[](const Node& node) {
                return "(" + std::to_string(node.getX()) + "," + std::to_string(node.getY()) + ")";
            });

    // Bind the Graph class
    py::class_<Graph>(m,"Graph")
            .def(py::init<int, int>())
            .def("getWidth",&Graph::getWidth)
            .def("getHeight",&Graph::getHeight)
            .def("getNodes",&Graph::getNodes)
            .def("getNode",(std::shared_ptr<Node> (Graph::*)(Coordinate)) &Graph::getNode)
            .def("getNode",(std::shared_ptr<Node> (Graph::*)(int, int)) &Graph::getNode)
            .def("size",&Graph::size)
            .def("clone",&Graph::clone);

    // Bind the Maze class
    py::class_<Maze>(m,"Maze")
            .def(py::init<int, int, long long, std::string, Coordinate, Coordinate, int, int, unsigned int, const Graph&>())
            .def("getWidth",&Maze::getWidth)
            .def("getHeight",&Maze::getHeight)
            .def("getGenerationTime",&Maze::getGenerationTime)
            .def("getGenerationAlgorithm",&Maze::getGenerationAlgorithm)
            .def("getStart",&Maze::getStart)
            .def("getEnd",&Maze::getEnd)
            .def("getPathWidth",&Maze::getPathWidth)
            .def("getWallWidth",&Maze::getWallWidth)
            .def("getSeed",&Maze::getSeed)
            .def("getGraph",&Maze::getGraph)
            .def("isValid",&Maze::isValid);

    // Bind the MazePath class
    py::class_<MazePath>(m,"MazePath")
            .def(py::init<long long, std::string, std::vector<std::shared_ptr<Node>>>())
            .def("getSolvingAlgorithm",&MazePath::getSolvingAlgorithm)
            .def("getSolvingTime",&MazePath::getSolvingTime)
            .def("getLength",&MazePath::getLength)
            .def("getJunctionCount",&MazePath::getJunctionCount)
            .def("addNode",&MazePath::addNode)
            .def("getNodes",&MazePath::getNodes)
            .def("isValid",&MazePath::isValid);

    // Bind the MazeBuilder class
    py::class_<MazeBuilder>(m,"MazeBuilder")
            .def(py::init<int, int, long long, std::string, unsigned int>())
            .def(py::init<int, int, long long, std::string, unsigned int, const Graph&>())
            .def("getWidth",&MazeBuilder::getWidth)
            .def("getHeight",&MazeBuilder::getHeight)
            .def("getGenerationTime",&MazeBuilder::getGenerationTime)
            .def("getGenerationAlgorithm",&MazeBuilder::getGenerationAlgorithm)
            .def("setStart",&MazeBuilder::setStart)
            .def("getStart",&MazeBuilder::getStart)
            .def("setEnd",&MazeBuilder::setEnd)
            .def("getEnd",&MazeBuilder::getEnd)
            .def("setPathWidth",&MazeBuilder::setPathWidth)
            .def("getPathWidth",&MazeBuilder::getPathWidth)
            .def("setWallWidth",&MazeBuilder::setWallWidth)
            .def("getWallWidth",&MazeBuilder::getWallWidth)
            .def("setSeed",&MazeBuilder::setSeed)
            .def("getSeed",&MazeBuilder::getSeed)
            .def("setGraph",&MazeBuilder::setGraph)
            .def("getGraph",&MazeBuilder::getGraph)
            .def("build",&MazeBuilder::build)
            .def("buildExpected",&MazeBuilder::buildExpected);

    // Bind the Method class
    py::class_<Method>(m,"Method")
            .def(py::init<std::string, std::string>())
            .def("getName",&Method::getName)
            .def("getType",&Method::getType);

    // Bind the SavingMethod class
    py::class_<SavingMethod, Method>(m,"SavingMethod")
            .def("save",py::overload_cast<const Maze&, std::string>(&SavingMethod::save))
            .def("save",py::overload_cast<const Maze&, std::string, std::optional<MazePath>>(&SavingMethod::save));

    // Bind the MemoryMethod class
    py::class_<MemoryMethod, Method>(m,"MemoryMethod")
            .def("save",py::overload_cast<const Maze&>(&MemoryMethod::save))
            .def("save",py::overload_cast<const Maze&, std::optional<MazePath>>(&MemoryMethod::save));

    // Bind the LoadingMethod class
    py::class_<LoadingMethod, Method>(m,"LoadingMethod")
            .def("load",py::overload_cast<std::string>(&LoadingMethod::load));

    // Bind the TextFileSavingMethod class
    py::class_<TextFileSavingMethod, SavingMethod>(m,"TextFileSavingMethod")
            .def("save",[=](const Maze& maze, std::string pathToFile) {
                return TextFileSavingMethod().save(maze,pathToFile);
            })
            .def("save",[=](const Maze& maze, std::string pathToFile, std::optional<MazePath> path) {
                return TextFileSavingMethod().save(maze,pathToFile, path);
            });

    // Bind the ImageSavingMethod class
    py::class_<ImageSavingMethod, SavingMethod>(m,"ImageSavingMethod")
            .def("save",[=](const Maze& maze, std::string pathToFile) {
                return ImageSavingMethod().save(maze,pathToFile);
            })
            .def("save",[=](const Maze& maze, std::string pathToFile, std::optional<MazePath> path) {
                return ImageSavingMethod().save(maze,pathToFile,path);
            });

//    // Bind the ImageMemoryMethod class
    py::class_<ImageMemoryMethod, MemoryMethod>(m,"ImageMemoryMethod")
            .def("save",[=](const Maze& maze) {
                return ImageMemoryMethod().save(maze);
            })
            .def("save",[=](const Maze& maze, std::optional<MazePath> path) {
                return ImageMemoryMethod().save(maze, path);
            });

    // Bind the TextFileLoadingMethod class
    py::class_<TextFileLoadingMethod, LoadingMethod>(m,"TextFileLoadingMethod")
            .def("load",[=](std::string path) {
                return TextFileLoadingMethod().load(path);
            });
}