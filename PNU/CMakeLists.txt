add_definitions(-DLOCAL_MACHINE)

add_executable(${PROJECT_NAME}
        include/commands.h
        include/connection.h
        include/objects.h
        include/reader.h
        include/transformer.h
        src/connection.cpp
        src/objects.cpp
        src/reader.cpp
        src/transformer.cpp

        main.cpp)

if(MINGW)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()
