cmake_minimum_required(VERSION 3.12)
project(MyProject)

find_path(RL_INCLUDE_DIR NAMES raylib.h PATHS /opt/homebrew/opt/raylib/include)
include_directories(${RL_INCLUDE_DIR})
find_library(RL_LIBRARY NAMES raylib PATHS /opt/homebrew/opt/raylib/lib)

# Set the source files for your project
set(SOURCES main.c)

# Create the executable
add_executable(MyProject ${SOURCES})

# Link against the raylib library
target_link_libraries(MyProject ${RL_LIBRARY})
