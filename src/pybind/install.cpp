#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(mazeLib, m) {
    m.attr("__version__") = "1.0";

    m.def("add", &add, R"pbdoc(
            Add two numbers

            Some other explanation about the add function.
        )pbdoc");

    m.def("subtract", &sub, R"pbdoc(
            Subtract two numbers

            Some other explanation about the subtract function.
        )pbdoc");

    m.def("test", &test);
}

