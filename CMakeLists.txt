cmake_minimum_required(VERSION 3.11)
project(GameOfLife CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)

# Source files
add_executable(${PROJECT_NAME} main.cpp)

# Link raylib
target_link_libraries(${PROJECT_NAME} raylib)

# Copy resources to build directory if needed
# file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

# Platform-specific settings
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()
