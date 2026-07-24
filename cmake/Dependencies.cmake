# ---------------------------------------------------------------------------
# Dependency management via FetchContent (declarative, no vcpkg/Conan needed).
#
# Add a dependency by calling chess_add_dependency(<name> ...). It is fetched
# into the build tree on first configure and made available to every target
# via target_link_libraries(... PRIVATE <name>).
#
# Example (uncomment to pull {fmt} for fast type-safe formatting):
#
#   chess_add_dependency(fmt
#       GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#       GIT_TAG        11.0.2
#   )
#
# Then in a target:
#   target_link_libraries(my_target PRIVATE fmt::fmt)
# ---------------------------------------------------------------------------
include_guard(GLOBAL)
include(FetchContent)

function(chess_add_dependency name)
    cmake_parse_arguments(ARG
        ""               # options
        "GIT_TAG"        # one-value
        "GIT_REPOSITORY" # one-value
        ""               # remaining (ignored)
        ${ARGN})

    FetchContent_Declare(${name}
        GIT_REPOSITORY ${ARG_GIT_REPOSITORY}
        GIT_TAG        ${ARG_GIT_TAG}
        GIT_SHALLOW    TRUE
    )
    FetchContent_MakeAvailable(${name})
endfunction()

# ---------------------------------------------------------------------------
# Place real chess_add_dependency(...) calls below this line.
# The project builds with zero external dependencies by default.
# ---------------------------------------------------------------------------
