cmake_minimum_required(VERSION 3.10)
project(Playground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OSBit 32)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBit 64)
endif()

set(AllOutDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBit}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${AllOutDir}/StaticLibs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${AllOutDir}/SharedLibs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${AllOutDir})

find_package(SFML 2.5 COMPONENTS graphics window system audio network REQUIRED)

if(NOT SFML_FOUND)
    message(STATUS "SFML not found. Downloading from the internet...")
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
    )
    FetchContent_MakeAvailable(SFML)
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    sfml-network
)
target_include_directories(${PROJECT_NAME} PRIVATE include)