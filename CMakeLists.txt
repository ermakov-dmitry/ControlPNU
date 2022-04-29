cmake_minimum_required(VERSION 3.21)
project(Diploma)

set(CMAKE_CXX_STANDARD 11)

include_directories(PNU/include PNU/src)

# Including Tools Projects:
add_subdirectory(PNU)

# Including Tests Project:
enable_testing()
include(GoogleTest)
add_subdirectory(Tests/Unit)
