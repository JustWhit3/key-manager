# Project settings
cmake_minimum_required(VERSION 3.15)

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
find_package( cryptopp REQUIRED )

# If Crypto++ is not found, fetch cryptopp-cmake repository
if( NOT cryptopp_FOUND )
    include(FetchContent)

    # Set the URL and tag of the cryptopp-cmake repository for version 8.8.0
    set( CRYPTOPP_CMAKE_URL "https://github.com/abdes/cryptopp-cmake.git" )
    set( CRYPTOPP_CMAKE_TAG "v8.8.0" )  # Use the desired tag for version 8.8.0

    # Fetch cryptopp-cmake repository using FetchContent and rename it to cryptopp
    FetchContent_Declare(
        cryptopp
        GIT_REPOSITORY ${CRYPTOPP_CMAKE_URL}
        GIT_TAG ${CRYPTOPP_CMAKE_TAG}
    )

    # Enable FetchContent to download and configure the repository
    FetchContent_MakeAvailable( cryptopp )
else()
    message( STATUS "crypto++ 8.8.0 found in the system." )
endif()
