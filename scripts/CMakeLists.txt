# Project settings
cmake_minimum_required( VERSION 3.15 )

project( key-manager-build-scripts
    VERSION 1.0
    DESCRIPTION "Build system for key manager scripts."
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
file( GLOB_RECURSE INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../include/utility/generic.hpp )
file( GLOB_RECURSE SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/copy_files.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/utility/generic.cpp
)

# Creating the main executable
set( COPY_EXEC "copy-files" )
add_executable( ${COPY_EXEC} ${SRC_FILES} ${INC_FILES} )

# Adding specific compiler flags
if( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
    set( COMPILE_FLAGS "/Wall /Yd /fsanitize=address,undefined /Oy" )
else()
    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder -fsanitize=address,undefined -fno-omit-frame-pointer -g" )
    else()
        set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder -fsanitize=address,undefined -fno-omit-frame-pointer" )
    endif()
endif()
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )

# Adding cppcheck properties
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set( cppcheck cppcheck "--enable=warning" "--inconclusive" "--force" "--inline-suppr" )
    set_target_properties( ${COPY_EXEC} PROPERTIES CXX_CPPCHECK ${cppcheck})
endif()

# Link to Qt6
find_package( Qt6 6.4.2 CONFIG REQUIRED COMPONENTS Core Widgets )
target_link_libraries( ${COPY_EXEC} PRIVATE Qt::Core Qt::Widgets )
