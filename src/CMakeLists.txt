# Engine library target. Keep engine logic here; the executable (in src/ via
# add_subdirectory) stays a thin wrapper that wires `main` to the library.

add_library(chess_engine STATIC
    engine.cpp
        state/board.cpp
        state/board.h
)

target_include_directories(chess_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Executable entry point.
add_executable(chess_main main.cpp)
target_link_libraries(chess_main PRIVATE chess_engine)
set_target_properties(chess_main PROPERTIES OUTPUT_NAME chess-engine)
