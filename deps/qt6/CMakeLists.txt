# Project settings
cmake_minimum_required( VERSION 3.15 )

project( key-manager-dependencies-qt6
    VERSION 1.0
    DESCRIPTION "Build system for key-manager Qt6 dependency."
    LANGUAGES CXX
)

# Error if building out of a build directory
file( TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH )
if( EXISTS "${LOC_PATH}" )
    message( FATAL_ERROR "You cannot build in a source directory (or any directory with "
                         "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                         "remove CMakeCache.txt and CMakeFiles." )
endif()

# Fetch the package
find_package( Qt6 6.4.2 QUIET )

if( NOT Qt6_FOUND )
    message( STATUS "Qt 6.4.2 not found. Downloading and configuring Qt..." )

    # Download and extract archive of Qt 6.4.2
    set( QT_VERSION "6.4.2" )
    set( QT_ARCHIVE_URL "https://download.qt.io/official_releases/qt/6.4/${QT_VERSION}/single/qt-everywhere-src-${QT_VERSION}.tar.xz" )
    set( QT_ARCHIVE_FILE "${CMAKE_CURRENT_BINARY_DIR}/qt-everywhere-src-${QT_VERSION}.tar.xz" )
    set( QT_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/qt-everywhere-src-${QT_VERSION}" )
    message( STATUS "Downloading the package from the official repository..." )
    file( DOWNLOAD ${QT_ARCHIVE_URL} ${QT_ARCHIVE_FILE}
          SHOW_PROGRESS
          EXPECTED_HASH SHA256=689f53e6652da82fccf7c2ab58066787487339f28d1ec66a8765ad357f4976be )
    message( STATUS "Unpacking the release..." )
    execute_process( COMMAND ${CMAKE_COMMAND} -E tar xvf ${QT_ARCHIVE_FILE}
                     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} 
                     OUTPUT_QUIET
    )

    # Configure and compile Qt
    set( QT_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/qt-build" )
    file( MAKE_DIRECTORY ${QT_BUILD_DIR} )
    message( STATUS "Configuring..." )
    execute_process( COMMAND ${QT_SOURCE_DIR}/configure -prefix ${QT_BUILD_DIR} --skip qtwebengine,qtwebsockets,qtserialport,qtbluetooth,qtcharts,qtdatavisualization,qtnetworkauth
                     WORKING_DIRECTORY ${QT_BUILD_DIR} )
    message( STATUS "Compiling..." )
    execute_process( COMMAND make
                     WORKING_DIRECTORY ${QT_BUILD_DIR} )

    # Set necessary environment variables to use Qt
    set( ENV{QTDIR} ${QT_BUILD_DIR} )
    set( ENV{PATH} ${QT_BUILD_DIR}/bin:$ENV{PATH})
else()
    message( STATUS "Qt 6.4.2 found in the system." )
endif()