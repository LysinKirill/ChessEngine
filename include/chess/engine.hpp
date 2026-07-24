#pragma once

#include <string>
#include <string_view>

namespace chess {

/// Placeholder engine entry point.
///
/// `ChessEngine` is the public façade that the executable (and the tests)
/// will talk to. As the engine grows, this is where you expose things like
/// `position`, `search`, `perft`, `move`, etc.
class ChessEngine {
public:
    ChessEngine() = default;

    /// Returns the engine name and version string, e.g. for UCI `id name`.
    [[nodiscard]] std::string name() const;

    /// Returns a human-readable greeting. Stand-in for real functionality.
    [[nodiscard]] std::string greet() const;
};

} // namespace chess
