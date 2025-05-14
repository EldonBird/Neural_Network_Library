cmake_minimum_required(VERSION 3.14)
project(Neural_Network)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(pybind11)

# Optional: ensure includes work in all cases
include_directories(${CMAKE_SOURCE_DIR}/pybind11/include)

add_executable(Neural_Network main.cpp)

# Python module (bindings.cpp must exist!)
pybind11_add_module(module_name bindings.cpp)
