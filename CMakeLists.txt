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

# Copy data and asset folder to output directory
file(COPY ${CMAKE_SOURCE_DIR}/asset DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/asset DESTINATION ${CMAKE_SOURCE_DIR}/build)
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_SOURCE_DIR}/build)

# Find SFML, if not found, download it
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

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    sfml-network
)
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR} include)

# # Make tests
include(CTest)
enable_testing()

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Get all test files
file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")

# Loop over all test files
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Get the file name without the full path and extension
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    # Add executable
    add_executable(${TEST_NAME} ${TEST_SOURCE} ${SOURCES})

    # Link libraries
    target_link_libraries(${TEST_NAME} PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
    )

    # Include directories
    target_include_directories(${TEST_NAME} PRIVATE ${SFML_INCLUDE_DIR} include)

    # Add the test
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
