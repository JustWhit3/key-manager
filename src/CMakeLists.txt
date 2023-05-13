# Project settings
cmake_minimum_required( VERSION 3.15 )

project( key-manager-build-src
    VERSION 1.0
    DESCRIPTION "Build system for key manager source code."
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

# Specific Qt settings
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON ) 

# Include directories
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../include )

# File variables
file( GLOB_RECURSE INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.hpp )
file( GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp )

# Creating the main executable
set( APP "key-manager" )
set( LIB "key-manager-static" )
add_executable( ${APP} ${SRC_FILES} ${INC_FILES} )

# Adding specific compiler flags
if( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
    set( COMPILE_FLAGS "/Wall /Yd" )
else()
    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder -g" )
    else()
        set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder" )
    endif()
endif()
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )

# Adding cppcheck properties
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set( cppcheck cppcheck "--enable=warning" "--inconclusive" "--force" "--inline-suppr" )
    set_target_properties( ${APP} PROPERTIES CXX_CPPCHECK ${cppcheck})
endif()

# Link to Qt6
find_package( Qt6 CONFIG REQUIRED COMPONENTS Core Widgets StateMachine )
target_link_libraries( ${APP} PRIVATE Qt::Core Qt::Widgets Qt::StateMachine )

# Install
install ( TARGETS ${APP} RUNTIME )
