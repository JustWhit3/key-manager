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

# Setting Qt environment variables
#set( QT_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/deps/qt6/qt-build/qtbase" )
#set( ENV{QTDIR} ${QT_BUILD_DIR} )
#set( ENV{PATH} ${QT_BUILD_DIR}/bin:$ENV{PATH} )
#set( CMAKE_PREFIX_PATH ${QT_BUILD_DIR} CACHE PATH "Qt installation path" )
#list( APPEND CMAKE_INCLUDE_PATH ${QT_BUILD_DIR}/include )
#list( APPEND CMAKE_INCLUDE_PATH ${QT_BUILD_DIR}/include/QtWidgets )
#list( APPEND CMAKE_INCLUDE_PATH ${QT_BUILD_DIR}/include/QtStateMachine )


set( QT_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/_deps/qt-src" )
set( ENV{QTDIR} ${QT_BUILD_DIR} )
set( ENV{PATH} ${QT_BUILD_DIR}/bin:$ENV{PATH} )
set( CMAKE_PREFIX_PATH ${QT_BUILD_DIR} CACHE PATH "Qt installation path" )
list( APPEND CMAKE_INCLUDE_PATH ${QT_BUILD_DIR}/include )
list( APPEND CMAKE_INCLUDE_PATH ${QT_BUILD_DIR}/include/QtWidgets )
list( APPEND CMAKE_INCLUDE_PATH ${QT_BUILD_DIR}/include/QtStateMachine )

# Compiling the main app
add_subdirectory( src )

# Compile tests
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    add_subdirectory( test/unit_tests )
endif()
