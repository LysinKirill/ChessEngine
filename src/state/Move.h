//
// Created by Kirill on 26.07.2026.
//

#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H
#pragma once
#include "PieceColor.h"
#include <cstdint>
#include <optional>

#include "PieceType.h"

#endif //CHESSENGINE_MOVE_H

struct Move {
    PieceColor movedPieceColor;
    std::uint8_t sourceRow;
    std::uint8_t sourceCol;
    std::uint8_t targetRow;
    std::uint8_t targetCol;
    std::optional<PieceType> promotedToPieceType;
    //consider bit field
    bool captureOnSpot = false;
    bool captureEnPassantLeft = false;
    bool captureEnPassantRight = false;
    bool longCastle = false;
    bool shortCastle = false;
};