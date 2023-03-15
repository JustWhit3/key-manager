# Finding the package
find_package( Qt6 CONFIG COMPONENTS Core Widgets StateMachine )

# Fetching the package if not found
if( NOT Qt6_FOUND )

    # Fetching the package
    include( FetchContent )

    FetchContent_Declare(
      Qt6
      GIT_REPOSITORY "https://github.com/qt/qt5"
      GIT_TAG v6.4.2
      CONFIGURE_COMMAND "perl init-repository && ./configure"
    )

    # Make it available
    message( STATUS "Fetching Qt6..." )
    FetchContent_MakeAvailable( Qt6 ) 
endif() 