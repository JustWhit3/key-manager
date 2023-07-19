# CMake project settings
cmake_minimum_required( VERSION 3.15 )

project( key-manager-unit-tests
    VERSION 1.0
    DESCRIPTION "Build system for key-manager unit tests."
    LANGUAGES CXX
)

# Error if building out of a build directory
file( TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH )
if( EXISTS "${LOC_PATH}" )
    message( FATAL_ERROR "You cannot build in a source directory (or any directory with "
                         "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                         "remove CMakeCache.txt and CMakeFiles." )
endif()

# Set compiler options
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Other settings for paths
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../include )

# File variables
file( GLOB_RECURSE TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp )
file( GLOB_RECURSE SRC_FILES 
    ../../src/utility/crypto.cpp
)

# Create executables
set( UNIT "key-manager_unit_tests" )
add_executable( ${UNIT} ${TEST_FILES} ${SRC_FILES} )

# Adding specific compiler flags
if( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
    set( COMPILE_FLAGS "/Wall /Yd" )
else()
    set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder" )
endif()
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

# Link to doctest
find_package( doctest )
target_link_libraries( ${UNIT} PUBLIC doctest::doctest )

# Link to crypto++
find_package( cryptopp 8.8.0 CONFIG )
target_link_libraries( ${UNIT} PRIVATE cryptopp::cryptopp )