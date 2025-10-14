cmake_minimum_required(VERSION 3.25)
project(PQVIEW VERSION 0 LANGUAGES C)

# USE C11 Standart

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES
    main.c
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

# Link Library
target_link_libraries(${PROJECT_NAME} PRIVATE 
    user32
    gdi32
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