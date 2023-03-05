# Finding the package
find_package( Qt6 COMPONENTS Core Widgets REQUIRED )

# Fetching the package if not found
if( NOT Qt6_FOUND )

    # Fetching the package
    include( FetchContent )

    FetchContent_Declare(
      Qt6
      GIT_REPOSITORY "https://github.com/qt/qtbase"
      GIT_TAG v6.2.4
    )

    # Make it available
    message( STATUS "Fetching Qt6..." )
    FetchContent_MakeAvailable( Qt6 )
endif()