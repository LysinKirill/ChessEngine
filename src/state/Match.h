//
// Created by Kirill on 25.07.2026.
//
#pragma once
#include <cstdint>
#include "Board.h"
#include "Move.h"

#ifndef CHESSENGINE_MATCH_H
#define CHESSENGINE_MATCH_H

#endif //CHESSENGINE_MATCH_H

class Match {
    Board board;
    std::uint32_t ply;

    std::uint32_t getMove() const {
        return ply / 2;
    }

    bool isCheckmatedBlack() {
        if (!board.isKingInCheck(Black))
            return false;

        if (getTurnColor() == White)
            return false;

        if
        return false;
    }

public:
    PieceColor getTurnColor() const {
        return ply % 2 == 0 ? White : Black;
    }

    bool isCheckmated(PieceColor color) {

    }

    void makeMove(Move move) {
        ssfsf
    }
};