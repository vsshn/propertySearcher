cmake_minimum_required(VERSION 3.10)
project(Search VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(CURL REQUIRED)
find_package(spdlog REQUIRED)
find_package(gflags REQUIRED)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl spdlog::spdlog)
target_include_directories(${PROJECT_NAME} PRIVATE ${GFLAGS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GFLAGS_LIBRARIES})