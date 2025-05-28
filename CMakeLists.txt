# Minimum required CMake version
cmake_minimum_required(VERSION 3.16)

# Project name
project("UNI-GradeManager"
        VERSION 1.0
        DESCRIPTION "University management system"
        LANGUAGES CXX)

# Set src/main.cpp in SOURCES
set(SOURCES 
    src/main.cpp

)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Automatically generate the compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # which contains all the information about paths, macros, compiler flags, etc. 

# Configuration of a header file for passing CMake settings to the source code
configure_file(CMakeConfig.h.in CMakeConfig.h) # CMakeConfig.h save in ${PROJECT_BINARY_DIR} (/builda)

# Tell CMake to compile main.cpp as an executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add this binary include file search path
target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_SOURCE_DIR}/include" # For include file
                           "${PROJECT_BINARY_DIR}" # For CMakeConfig.h
                           )