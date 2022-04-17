add_subdirectory(googletest)

add_definitions(-DLOCAL_MACHINE)

add_executable(${PROJECT_NAME}-test
        ../../PNU/include/commands.h
        ../../PNU/include/connection.h
        ../../PNU/include/objects.h
        ../../PNU/include/reader.h
        ../../PNU/include/transformer.h
        ../../PNU/src/connection.cpp
        ../../PNU/src/objects.cpp
        ../../PNU/src/reader.cpp
        ../../PNU/src/transformer.cpp

        angles_test.cpp)

target_link_libraries(${PROJECT_NAME}-test gtest_main)