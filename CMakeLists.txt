cmake_minimum_required(VERSION 3.10)
project(SDL_Project)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    execute_process(COMMAND uname -r OUTPUT_VARIABLE MACOSX_VERSION)
    message(STATUS "Mac OS version: ${MACOSX_VERSION}")
    add_definitions(-DIS_DARWIN=1)
endif()

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)


# Find SDL2
find_package(SDL2 REQUIRED)

# Find SDL2_ttf
set(SDL2_ttf_DIR /usr/lib/x86_64-linux-gnu/libSDL2_ttf.a)
find_library(SDL2_TTF_LIBRARY SDL2_ttf)


# Add your source files
set(SOURCES src/main.cpp)

# Add your header files
set(HEADER_FILES /usr/include/SDL2 include/canvas.h include/geometry.h)

# Create the executable
add_executable(SDL_Project ${SOURCES})

# Specify the directories for the compiler to find the headers
target_include_directories(SDL_Project PRIVATE /usr/include/SDL2 ${CMAKE_CURRENT_SOURCE_DIR}/include ${SDL2_TTF_INCLUDE_DIRS})

# Link SDL2 library
target_link_libraries(SDL_Project ${SDL2_LIBRARIES}  ${SDL2_TTF_LIBRARY})

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(DEST_DIR "${CMAKE_BINARY_DIR}/assets")

add_custom_command(
    OUTPUT ${DEST_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR} ${DEST_DIR}
    COMMENT "Copying assets to build directory"
)

add_custom_target(
    copy_assets ALL
    DEPENDS ${DEST_DIR}
)
