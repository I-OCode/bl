cmake_minimum_required(VERSION 3.15...4.1)

project(bl LANGUAGES CXX)
option(BL_BUILD_PYTHON_BINDINGS "Build Python bindings" OFF)

if(BL_BUILD_PYTHON_BINDINGS)
  include(FetchContent)

  FetchContent_Declare(pybind11
                       GIT_REPOSITORY https://github.com/pybind/pybind11)

  FetchContent_MakeAvailable(pybind11)

  pybind11_add_module(pybl bl.cpp cfg.cpp emplacement.cpp traits.cpp py.cpp)

  set_target_properties(
    pybl
    PROPERTIES CXX_STANDARD 20
               CXX_EXTENSIONS OFF
               CXX_STANDARD_REQUIRED ON)
endif()

add_library(bl STATIC bl.cpp cfg.cpp emplacement.cpp traits.cpp)

set_target_properties(
  bl
  PROPERTIES CXX_STANDARD 20
             CXX_EXTENSIONS OFF
             CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(bl PRIVATE -Wall -Wextra -Wpedantic)
endif()
