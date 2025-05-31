# Minimum required CMake version
cmake_minimum_required(VERSION 3.25)

# Project name
project(
  "UNI-GradeManager"
  VERSION 1.0
  DESCRIPTION "University management system"
  LANGUAGES CXX)

# Set src/main.cpp in SOURCES
set(GUI_SOURCES
    src/gui/globals.cpp
    src/gui/sidebar.cpp
    src/gui/students.cpp
    src/gui/loginscreen.cpp
    src/gui/grades.cpp
    src/gui/popups.cpp
    src/gui/classes.cpp
    src/gui/courses.cpp
    src/gui/utils.cpp)

set(CLI_SOURCES src/cli/students.cpp src/cli/grades.cpp src/cli/classes.cpp
                src/cli/courses.cpp src/cli/utils.cpp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Automatically generate the compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # which contains all the information about
                                      # paths, macros, compiler flags, etc.

# Configuration of a header file for passing CMake settings to the source code
configure_file(CMakeConfig.h.in CMakeConfig.h) # CMakeConfig.h save in
                                               # ${PROJECT_BINARY_DIR} (/builda)

# --- GUI Executable ---

# find library
find_package(raylib REQUIRED)

add_executable(UNI-GradeManager-GUI src/gui/main.cpp ${GUI_SOURCES})

target_link_libraries(UNI-GradeManager-GUI PRIVATE raylib pthread dl)

target_include_directories(
  UNI-GradeManager-GUI PUBLIC "${PROJECT_SOURCE_DIR}/include/gui"
                              "${PROJECT_BINARY_DIR}")

# --- CLI Executable ---
add_executable(UNI-GradeManager-CLI src/cli/main.cpp ${CLI_SOURCES})

target_include_directories(
  UNI-GradeManager-CLI PUBLIC "${PROJECT_SOURCE_DIR}/include/cli"
                              "${PROJECT_BINARY_DIR}")

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
