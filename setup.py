from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

ext_modules = [
    Pybind11Extension("mazeLib", [
        "src/pybind/bind.cpp",

        "src/main.cpp",
        "src/image/Image.cpp",
        "src/graph/Graph.cpp",
        "src/maze/Maze.cpp",
        "src/interface/Interface.cpp",
        "src/algorithms/Algorithm.cpp",
        "src/algorithms/type/KruskalAlgorithm.cpp",
        "src/algorithms/type/DepthFirstSearchAlgorithm.cpp",
        "src/method/Method.cpp",
        "src/method/type/ImageSavingMethod.cpp",
        "src/method/type/ImageMemoryMethod.cpp",
        "src/method/type/TextFileLoadingMethod.cpp",
        "src/method/type/TextFileSavingMethod.cpp",
        "src/algorithms/type/BreadthFirstSearchAlgorithm.cpp",
        "src/algorithms/type/TremauxsAlgorithm.cpp",
        "src/algorithms/type/WallFollowingAlgorithm.cpp",
        "src/algorithms/type/DijkstraAlgorithm.cpp",
        "src/algorithms/type/LeeAlgorithm.cpp"
    ]),
]

setup(
    name="mazeLib",
    version="1.0",
    author="Pavel Mikula",
    author_email="mik0486@vsb.cz",
    description="A python binding for mazeLib",
    long_description="",
    ext_modules=ext_modules,
    extras_require={"dev": ["pytest>=3.7"]},
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.7",
)