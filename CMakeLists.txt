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

# Fetching deps
add_subdirectory( deps )

# Copy configuration files
message( STATUS "Copy configuration files in the system location." )
execute_process(
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/copy_files.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE SCRIPT_RESULT
)

# Qt paths
set( QT_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/_deps/qt6/qt6-build/qtbase" )
set( ENV{QTDIR} ${QT_BUILD_DIR} )
set( ENV{PATH} ${QT_BUILD_DIR}/bin:$ENV{PATH} )
set( CMAKE_PREFIX_PATH ${QT_BUILD_DIR} CACHE PATH "Qt installation path" )
list( APPEND CMAKE_INCLUDE_PATH ${QT_BUILD_DIR}/qtbase/include )
list( APPEND CMAKE_INCLUDE_PATH ${QT_BUILD_DIR}/qtbase/include/QtWidgets )
list( APPEND CMAKE_INCLUDE_PATH ${QT_BUILD_DIR}/qtbase/include/QtStateMachine )

# crypto++ paths
list( APPEND CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_BINARY_DIR}/_deps/cryptopp-cmake-build/cryptopp )

# Compiling the main app
add_subdirectory( src )

# Compile tests
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    add_subdirectory( test/unit_tests )
endif()
