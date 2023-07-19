# Project settings
cmake_minimum_required( VERSION 3.15 )

project( key-manager-dependencies-cryptopp
    VERSION 1.0
    DESCRIPTION "Build system for key-manager cryptopp dependency."
    LANGUAGES CXX
)

# Error if building out of a build directory
file( TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH )
if( EXISTS "${LOC_PATH}" )
    message( FATAL_ERROR "You cannot build in a source directory (or any directory with "
                         "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                         "remove CMakeCache.txt and CMakeFiles." )
endif()

# Try finding Crypto++ using find_package
find_package( cryptopp 8.8.0 )

# If Crypto++ is not found, fetch cryptopp-cmake repository
if( NOT cryptopp_FOUND )

    # Initial settings
    set( CMAKE_BUILD_TYPE "Release" )
    include( ${CMAKE_SOURCE_DIR}/cmake/CPM.cmake )
    include( ${CMAKE_SOURCE_DIR}/cmake/FasterBuild.cmake )

    # Fetching cryptopp
    message( STATUS "Fetching crypto++ 8.8.0..." )
    set( CRYPTOPP_INCLUDE_PREFIX "cryptopp" )
    cpmaddpackage(
        NAME cryptopp-cmake
        GIT_REPOSITORY https://github.com./abdes/cryptopp-cmake
        GIT_TAG v8.8.0
        OPTIONS "CRYPTOPP_BUILD_TESTING OFF" "CRYPTOPP_INSTALL ON"
    )
endif()
