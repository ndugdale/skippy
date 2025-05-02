cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME skippy)
set(PROJECT_VERSION 1.0.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra --use-port=sdl2 --use-port=sdl2_image:formats=png --use-port=sdl2_mixer --use-port=sdl2_ttf")

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PUBLIC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/public")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dist")

file(GLOB_RECURSE SRC_FILES "${SOURCE_DIR}/*.c")
file(GLOB_RECURSE PUBLIC_FILES "${PUBLIC_DIR}/*")

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Add Emscripten-specific linker flags only to the final target
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    set(ASSET_FLAGS "--use-preload-plugins")

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        list(APPEND ASSET_FLAGS "--emrun")
    endif()

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
        list(APPEND ASSET_FLAGS "--preload-file" "../assets")
    endif()

    target_link_options(${PROJECT_NAME} PRIVATE ${ASSET_FLAGS})
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${SOURCE_DIR}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    OUTPUT_NAME index
)

add_custom_target(
    watch_public ALL
    DEPENDS ${PUBLIC_DIR}
)

add_custom_command(
    TARGET ${PROJECT_NAME} watch_public POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PUBLIC_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

message(STATUS "C Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} ${CMAKE_C_COMPILER}")
