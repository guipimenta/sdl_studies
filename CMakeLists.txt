cmake_minimum_required(VERSION 3.10)
project(SDL_Project)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    execute_process(COMMAND uname -r OUTPUT_VARIABLE MACOSX_VERSION)
    message(STATUS "Mac OS version: ${MACOSX_VERSION}")
    add_definitions(-DIS_DARWIN=1)
endif()

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Find SDL2
find_package(SDL2 REQUIRED)

# Add your source files
set(SOURCES src/main.cpp)

# Add your header files
set(HEADER_FILES /usr/include/SDL2 include/canvas.h include/geometry.h)

# Create the executable
add_executable(SDL_Project ${SOURCES})

# Specify the directories for the compiler to find the headers
target_include_directories(SDL_Project PRIVATE /usr/include/SDL2 ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link SDL2 library
target_link_libraries(SDL_Project ${SDL2_LIBRARIES})