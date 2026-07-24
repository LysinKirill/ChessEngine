#include "chess/engine.hpp"

#include <gtest/gtest.h>

TEST(Engine, HasName) {
    chess::ChessEngine engine;
    EXPECT_FALSE(engine.name().empty());
}

TEST(Engine, GreetingContainsName) {
    chess::ChessEngine engine;
    EXPECT_NE(engine.greet().find(engine.name()), std::string::npos);
}
