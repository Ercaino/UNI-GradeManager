# Minimum required CMake version
cmake_minimum_required(VERSION 3.25)

# Project name
project("UNI-GradeManager"
        VERSION 1.0
        DESCRIPTION "University management system"
        LANGUAGES CXX)

# Set src/main.cpp in SOURCES
set(SOURCES src/students.cpp src/grades.cpp src/classes.cpp
            src/courses.cpp src/utils.cpp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#find library
find_package(raylib REQUIRED)

# Automatically generate the compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # which contains all the information about paths, macros, compiler flags, etc. 

# Configuration of a header file for passing CMake settings to the source code
configure_file(CMakeConfig.h.in CMakeConfig.h) # CMakeConfig.h save in ${PROJECT_BINARY_DIR} (/builda)


# --- GUI Executable ---
add_executable(UNI-GradeManager-GUI src/main_gui.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(UNI-GradeManager-GUI PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           "${PROJECT_BINARY_DIR}")

# --- CLI Executable ---
add_executable(UNI-GradeManager-CLI src/main_cli.cpp ${SOURCES})

target_include_directories(UNI-GradeManager-CLI PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           "${PROJECT_BINARY_DIR}")

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Tell CMake to compile main.cpp as an executable
# add_executable(${PROJECT_NAME} ${SOURCES})

# Add this binary include file search path
# target_include_directories(${PROJECT_NAME} PUBLIC
#                           "${PROJECT_SOURCE_DIR}/include" # For include file
#                           "${PROJECT_BINARY_DIR}" # For CMakeConfig.h
#                           )