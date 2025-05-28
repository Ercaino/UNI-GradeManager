cmake_minimum_required(VERSION 3.16)

project(
  "UNI-GradeManager"
  VERSION 1.0
  DESCRIPTION "University management system"
  LANGUAGES CXX)

set(SOURCES src/main.cpp src/students.cpp src/grades.cpp src/classes.cpp
            src/courses.cpp src/utils.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_include_directories(${PROJECT_NAME} PUBLIC include)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

