cmake_minimum_required(VERSION 4.0)

# This project requires a C++26 reflection capable compiler and runtime.

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(comet CXX)

include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG d9d6f0f1f967807ffade6598ea9a631ebaf37a56
)
FetchContent_MakeAvailable(glfw)

set(COMET_GLOBAL_COMPILE_OPTIONS 
  "-Wall" "-Wextra" "-Werror" "-Wshadow" "-Wconversion"
  "-freflection" "-fexpansion-statements" "-freflection-latest")

add_subdirectory(comet)
add_subdirectory(sandbox)
