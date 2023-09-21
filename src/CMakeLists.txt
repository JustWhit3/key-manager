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
    set( COMPILE_FLAGS "/Wall /Yd /fsanitize=address,undefined /Oy" )
else()
    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder -fsanitize=address,undefined -fno-omit-frame-pointer -g" )
    else()
        set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder -fsanitize=address,undefined -fno-omit-frame-pointer" )
    endif()
endif()
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )

# Format the code using clang-format
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    option( FORMAT "Format the code using clang-format" ON )
    if( FORMAT )
        find_program( CLANG_FORMAT_EXECUTABLE clang-format )
        if( CLANG_FORMAT_EXECUTABLE )
            message( STATUS "clang-format found: ${CLANG_FORMAT_EXECUTABLE}" )
            file( GLOB_RECURSE SOURCE_FILES
                ${CMAKE_SOURCE_DIR}/src/**/*.cpp
                ${CMAKE_SOURCE_DIR}/include/**/*.hpp
                ${CMAKE_SOURCE_DIR}/test/unit_tests/**/*.cpp
                ${CMAKE_SOURCE_DIR}/examples/**/*.cpp
            )
            add_custom_target(format
                COMMAND ${CLANG_FORMAT_EXECUTABLE}
                -i
                ${SOURCE_FILES}
            )
            add_dependencies( ${APP} format )
        else()
            message(STATUS "clang-format not found. Skipping code formatting.")
        endif()
    endif()
endif()

# Adding cppcheck properties
find_program( CPPCHECK_FOUND cppcheck )
if ( CPPCHECK_FOUND AND CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set( cppcheck_options "--enable=warning" "--inconclusive" "--force" "--inline-suppr" )
    set_target_properties( ${APP} PROPERTIES CXX_CPPCHECK "${CPPCHECK_FOUND}" )
endif()

# Link to Qt6
find_package( Qt6 6.4.2 CONFIG REQUIRED COMPONENTS Core Widgets StateMachine )
target_link_libraries( ${APP} PRIVATE Qt::Core Qt::Widgets Qt::StateMachine )

# Link to crypto++
find_package( cryptopp 8.8.0 CONFIG )
target_link_libraries( ${APP} PRIVATE cryptopp::cryptopp )

# Install
include( GNUInstallDirs )
install( TARGETS ${APP} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} )