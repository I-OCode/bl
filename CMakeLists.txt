cmake_minimum_required(VERSION 3.15...4.1)

project(bl LANGUAGES CXX)

add_library(bl STATIC bl.cpp cfg.cpp emplacement.cpp traits.cpp)

set_target_properties(
  bl
  PROPERTIES CXX_STANDARD 20
             CXX_EXTENSIONS OFF
             CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(bl PRIVATE -Wall -Wextra -Wpedantic)
endif()
