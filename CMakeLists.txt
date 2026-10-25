cmake_minimum_required(VERSION 4.0)

# This project requires a C++26 reflection capable compiler and runtime.

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(comet CXX)

set(COMET_GLOBAL_COMPILE_OPTIONS 
  "-Wall" "-Wextra" "-Werror" "-Wshadow" "-Wconversion"
  "-freflection" "-fexpansion-statements" "-freflection-latest")

add_subdirectory(comet)
add_subdirectory(sandbox)
