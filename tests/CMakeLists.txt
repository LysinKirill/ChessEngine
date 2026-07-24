# Unit tests. Enabled with -DCHESS_BUILD_TESTS=ON.
#
# GoogleTest is fetched via FetchContent the first time tests are built, so
# building tests requires network access on first configure.

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
    GIT_SHALLOW    TRUE
)
# On Windows / MSVC gtest needs shared CRT; harmless elsewhere.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(chess_tests test_main.cpp)
target_link_libraries(chess_tests PRIVATE
    chess_engine
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(chess_tests)
