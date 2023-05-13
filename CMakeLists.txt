# Project settings
cmake_minimum_required( VERSION 3.15 )

# Info about the build type
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    message( STATUS "Build type: DEBUG" )
    add_compile_definitions( DEBUG_KEY_MANAGER )
else()
    message( STATUS "Build type: RELEASE" )
endif()

project( key-manager-build
    VERSION 1.0
    DESCRIPTION "Build system for key manager app."
    LANGUAGES CXX
)

# Error if building out of a build directory
file( TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH )
if( EXISTS "${LOC_PATH}" )
    message( FATAL_ERROR "You cannot build in a source directory (or any directory with "
                         "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                         "remove CMakeCache.txt and CMakeFiles." )
endif()

# Compiling the main app
add_subdirectory( src )

# Compile tests
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    add_subdirectory( test/unit_tests )
endif()
