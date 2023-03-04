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

# Extra settings
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )

# Include directories
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../include )

# Creating the main executable
set( APP "key-manager" )
file( GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp )
add_executable( ${APP} ${SRC_FILES} )

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
find_package( Qt6 COMPONENTS Core Widgets REQUIRED )
target_link_libraries( ${APP} Qt6::Widgets )

# Link to ptc-print
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    find_package( ptcprint )
    target_link_libraries( ${APP} PUBLIC ptcprint::ptcprint )
endif()

# Install
install ( TARGETS ${APP} RUNTIME )
