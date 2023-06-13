# Project settings
#[[cmake_minimum_required( VERSION 3.15 )

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

    # Set Ninja for compilation
    set( CMAKE_GENERATOR "Ninja" CACHE STRING "CMake generator" FORCE )

    # Initial message
    message( STATUS "Qt 6.4.2 not found. Downloading and configuring Qt..." )

    # Download and extract archive of Qt 6.4.2
    set( QT_VERSION "6.4.2" )
    set( QT_ARCHIVE_URL "https://download.qt.io/official_releases/qt/6.4/${QT_VERSION}/submodules/qtbase-everywhere-src-${QT_VERSION}.tar.xz" )
    set( QT_ARCHIVE_FILE "${CMAKE_CURRENT_BINARY_DIR}/qtbase-everywhere-src-${QT_VERSION}.tar.xz" )
    set( QT_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/qtbase-everywhere-src-${QT_VERSION}" )
    message( STATUS "Downloading the package from the official repository..." )
    file( DOWNLOAD ${QT_ARCHIVE_URL} ${QT_ARCHIVE_FILE}
          SHOW_PROGRESS
          EXPECTED_HASH SHA256=a88bc6cedbb34878a49a622baa79cace78cfbad4f95fdbd3656ddb21c705525d )
    message( STATUS "Unpacking the release..." )
    execute_process( COMMAND ${CMAKE_COMMAND} -E tar xvf ${QT_ARCHIVE_FILE}
                     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} 
                     OUTPUT_QUIET
    )

    # Configure Qt (skip building of useless modules)
    set( QT_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/qt-build" )
    file( MAKE_DIRECTORY ${QT_BUILD_DIR} )
    message( STATUS "Configuring..." )
    execute_process( COMMAND ${QT_SOURCE_DIR}/configure -prefix ${QT_BUILD_DIR}
                     WORKING_DIRECTORY ${QT_BUILD_DIR} )

    # Check if system supports parallelization
    if( DEFINED ENV{NUMBER_OF_PROCESSORS} )
        set( JOBS_OPTION "-j$ENV{NUMBER_OF_PROCESSORS}" )
    elseif( DEFINED ENV{PROCESSOR_COUNT} )
        set( JOBS_OPTION "-j$ENV{PROCESSOR_COUNT}" )
    else()
        set( JOBS_OPTION "" )
    endif()

    # Use -j option to compile if possible (qt is very big)
    if( JOBS_OPTION )
        message( STATUS "Compiling with parallelization..." )
        execute_process( COMMAND ninja ${JOBS_OPTION}
                     WORKING_DIRECTORY ${QT_BUILD_DIR} )
    else()
        message( STATUS "Compiling without parallelization..." )
        execute_process( COMMAND ninja
                     WORKING_DIRECTORY ${QT_BUILD_DIR} )
    endif()

    # Set necessary environment variables to use Qt
    set( ENV{QTDIR} ${QT_BUILD_DIR} )
    set( ENV{PATH} ${QT_BUILD_DIR}/bin:$ENV{PATH})

else()
    message( STATUS "Qt 6.4.2 found in the system." )
endif()
]]#

cmake_minimum_required(VERSION 3.15)
project(fetch-qt6.4.2)

# Imposta la versione di Qt desiderata
set(QT_VERSION "6.4.2")

# Cerca la versione di Qt nel sistema
find_package(Qt6 ${QT_VERSION} QUIET COMPONENTS Core Widgets StateMachine)

# Se Qt 6.4.2 non è trovato, scarica il repository di Qt da GitHub
if( NOT Qt6_FOUND)
    include(FetchContent)
    set(FETCHCONTENT_QUIET OFF)

    # Scarica il repository di Qt da GitHub
    FetchContent_Declare(
        qt
        GIT_REPOSITORY https://github.com/qt/qt5.git
        GIT_TAG v${QT_VERSION}
    )

    # Imposta la directory di output per il repository scaricato
    set(QT_SOURCE_DIR "${CMAKE_BINARY_DIR}/qt-src")

    # Esegui il download e la configurazione di Qt
    FetchContent_GetProperties(qt)
    if(NOT qt_POPULATED)
        FetchContent_Populate(qt)
        message(STATUS "Qt repository scaricato in: ${qt_SOURCE_DIR}")
    endif()

    # Imposta la variabile Qt6_DIR per specificare il percorso della versione scaricata di Qt
    set(Qt6_DIR "${QT_SOURCE_DIR}/lib/cmake/Qt6")
endif()

# Stampa il percorso completo alla directory del codice sorgente di Qt
message(STATUS "Percorso completo alla directory del codice sorgente di Qt: ${QT_SOURCE_DIR}")

# Utilizza Qt 6.4.2 se è stato trovato nel sistema o se è stato appena scaricato
if(Qt6_FOUND)
    message(STATUS "Qt 6.4.2 trovato nel sistema.")
    # Aggiungi qui le tue configurazioni per utilizzare Qt 6.4.2
else()
    message(STATUS "Qt 6.4.2 non trovato nel sistema. Utilizzerà la versione scaricata.")
    # Aggiungi qui le tue configurazioni per utilizzare la versione scaricata di Qt 6.4.2
endif()


# TODO: essere sicuri di usare ninja per build