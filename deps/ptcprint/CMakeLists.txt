# Finding the package
find_package( ptcprint )

# Fetching the package if not found
if( NOT ptcprint_FOUND )

    # Fetching the package
    include( FetchContent )

    FetchContent_Declare(
      ptcprint
      GIT_REPOSITORY "https://github.com/JustWhit3/ptc-print"
      GIT_TAG 4f7c20ec1219c24e6113008c46eaa1611f1c46c5 # 1.4.0
    )

    # No need to build tests
    set( PTCPRINT_TESTS OFF )

    # Make it available
    message( STATUS "Fetching ptc-print..." )
    FetchContent_MakeAvailable( ptcprint )
endif()