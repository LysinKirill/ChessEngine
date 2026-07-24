#include "chess/engine.hpp"

namespace chess {

std::string ChessEngine::name() const {
    return "ChessEngine 0.1.0";
}

std::string ChessEngine::greet() const {
    return std::string{"Hello from "} + name() + " — ready to move.";
}

} // namespace chess
