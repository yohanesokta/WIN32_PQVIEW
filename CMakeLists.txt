cmake_minimum_required(VERSION 3.25)
project(PQVIEW VERSION 0.1.0 LANGUAGES C)

# USE C11 Standart

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(PostgreSQL_ROOT "C:/gajahweb/postgres")

find_package(PostgreSQL REQUIRED)
message(STATUS "POSTGRESQL Include Dirs" : ${PostgreSQL_INCLUDE_DIRS})
message(STATUS "POSTGRESQL Library Dirs" : ${PostgreSQL_LIBRARY_DIRS})

set(SOURCES
    main.c
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${PostgreSQL_INCLUDE_DIRS}
)

# Link Library
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${PostgreSQL_LIBRARIES}
    user32
    gdi32
    comctl32
    ws2_32
)

target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN)

# if(MSVC)
#     target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
# else()
#     target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
# endif()

# POST-BUILD Message

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Build of ${PROJECT_NAME} v${PROJECT_VERSION} complete."
)