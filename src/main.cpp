#include "chess/engine.hpp"

#include <iostream>

int main() {
    chess::ChessEngine engine;
    std::cout << engine.greet() << '\n';
    return 0;
}
