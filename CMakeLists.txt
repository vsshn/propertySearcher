cmake_minimum_required(VERSION 3.10)
project(Search VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(CURL REQUIRED)
find_package(spdlog REQUIRED)
find_package(gflags REQUIRED)
find_package(OpenCV REQUIRED)


find_package(nlohmann_json REQUIRED)


# add libraries

add_library(ImageProcessing
    src/image_processing/ImageProcessing.cpp)

target_include_directories(ImageProcessing PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(ImageProcessing ${OpenCV_LIBS})


add_library(Fetcher
    src/fetcher/CurlWrapper.cpp)

target_include_directories(Fetcher PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(Fetcher PUBLIC CURL::libcurl spdlog::spdlog)

add_library(LinksProvider
    src/links/RightmoveLinksProvider.cpp)

target_include_directories(LinksProvider PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(LinksProvider PUBLIC CURL::libcurl spdlog::spdlog nlohmann_json::nlohmann_json)
target_link_libraries(LinksProvider PRIVATE Fetcher)

add_library(Parsers src/parsers/HtmlParser.cpp src/parsers/JsonParser.cpp)

target_link_libraries(Parsers spdlog::spdlog nlohmann_json::nlohmann_json)


add_library(ListingsProvider
    src/listings/RightmoveListingsProvider.cpp
    src/listings/RightmoveSimpleListingsProvider.cpp)

target_include_directories(ListingsProvider PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(ListingsProvider PRIVATE CURL::libcurl spdlog::spdlog nlohmann_json::nlohmann_json)
target_link_libraries(ListingsProvider PRIVATE Fetcher)


add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Fetcher ListingsProvider)

# Link libraries
target_include_directories(${PROJECT_NAME} PRIVATE ${GFLAGS_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GFLAGS_LIBRARIES})


set(ONE_PAGE_GETTER onePageHtmlGetter)
add_executable(${ONE_PAGE_GETTER} src/oneHtmlGetterMain.cpp)
target_link_libraries(${ONE_PAGE_GETTER} PRIVATE Fetcher)

# Link libraries
target_include_directories(${ONE_PAGE_GETTER} PRIVATE ${GFLAGS_INCLUDE_DIRS})
target_include_directories(${ONE_PAGE_GETTER} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${ONE_PAGE_GETTER} PRIVATE ${GFLAGS_LIBRARIES})

# ---- GoogleTest ----
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Prevent GoogleTest from forcing PIC
set(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ---- Tests ----
file(GLOB TEST_SOURCES "src/tests/*.cpp")
add_executable(runTests ${TEST_SOURCES})
target_link_libraries(runTests PRIVATE gtest gtest_main gmock
    gmock_main CURL::libcurl spdlog::spdlog LinksProvider Parsers ListingsProvider ImageProcessing)
target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_compile_definitions(runTests PRIVATE
    TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/src/tests"
)

add_test(NAME AllTests COMMAND runTests)
