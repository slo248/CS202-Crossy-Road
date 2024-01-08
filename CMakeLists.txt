cmake_minimum_required(VERSION 3.10)
project(CrossyRoad)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory
set(OSBit 32)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBit 64)
endif()

set(AllOutDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBit}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${AllOutDir})

# Copy data folder to output directory
file(COPY ${CMAKE_SOURCE_DIR}/asset DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Find SFML, if not found, download it
find_package(SFML 2.6 COMPONENTS graphics window system audio)

if(NOT SFML_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
    )

    FetchContent_GetProperties(SFML)

    if(NOT SFML_POPULATED)
        FetchContent_Populate(SFML)
        add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
    endif()

    set(SFML_INCLUDE_DIR ${sfml_SOURCE_DIR}/include)
endif()

set(SFML_LIBRARIES sfml-graphics sfml-window sfml-system sfml-audio)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC include ${SFML_INCLUDE_DIR})
