# Finding the package
find_package( Qt6 CONFIG COMPONENTS Core Widgets StateMachine )

# Fetching the package if not found
if( NOT Qt6_FOUND )

    # Fetching the package
    include( FetchContent )

    FetchContent_Declare(
      Qt6
      GIT_REPOSITORY "https://code.qt.io/qt/qt5.git"
      GIT_TAG v6.4.2
    )

    # Make it available
    message( STATUS "Fetching Qt6. This may take a while since the library is big..." )
    FetchContent_MakeAvailable( Qt6 )
endif() 