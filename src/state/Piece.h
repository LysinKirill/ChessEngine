//
// Created by Kirill on 25.07.2026.
//

#ifndef CHESSENGINE_PIECE_H
#define CHESSENGINE_PIECE_H
#pragma once
#include "PieceColor.h"
#include "PieceType.h"
#include <cstdint>

#endif //CHESSENGINE_PIECE_H

struct Piece {
    PieceColor color;
    PieceType type;
    std::int8_t row;
    std::int8_t col;
};