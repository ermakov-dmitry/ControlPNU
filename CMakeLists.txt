cmake_minimum_required(VERSION 3.21)
project(Diploma)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-DLOCAL_MACHINE)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCE_DIR}/include/commands.h
        ${PROJECT_SOURCE_DIR}/include/connection.h
        ${PROJECT_SOURCE_DIR}/include/objects.h
        ${PROJECT_SOURCE_DIR}/include/reader.h
        ${PROJECT_SOURCE_DIR}/include/transformer.h
        ${PROJECT_SOURCE_DIR}/src/connection.cpp
        ${PROJECT_SOURCE_DIR}/src/objects.cpp
        ${PROJECT_SOURCE_DIR}/src/reader.cpp
        ${PROJECT_SOURCE_DIR}/src/transformer.cpp
        ${PROJECT_SOURCE_DIR}/src/main.cpp)
