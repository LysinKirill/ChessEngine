//
// Created by klysin on 24.07.2026.
//

#pragma once
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

#include "Move.h"
#include "Piece.h"

#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

using BitBoard = std::uint64_t;

struct Board {
    BitBoard whitePawns{};
    BitBoard blackPawns{};
    BitBoard whiteKnights{};
    BitBoard blackKnights{};
    BitBoard whiteBishops{};
    BitBoard blackBishops{};
    BitBoard whiteRooks{};
    BitBoard blackRooks{};
    BitBoard whiteQueens{};
    BitBoard blackQueens{};
    BitBoard whiteKing{};
    BitBoard blackKing{};
    BitBoard occupiedSquares{};

    bool whiteKingMoved = false;
    bool blackKingMoved = false;
    std::uint8_t enPassantSquaresForWhite {};
    std::uint8_t enPassantSquaresForBlack {};

    struct {
        BitBoard byWhite{};
        BitBoard byBlack{};
    } attackedSquares;

    void initBoard() {
        for (std::int8_t pawnColumn = 0; pawnColumn < 8; ++pawnColumn) {
            setPiece(Piece{.color = White, .type = Pawn, .row = 1, .col = pawnColumn});
            setPiece(Piece{.color = Black, .type = Pawn, .row = 6, .col = pawnColumn});
        }

        // White pieces at row 0
        setPiece(Piece{.color = White, .type = Rook, .row = 0, .col = 0});
        setPiece(Piece{.color = White, .type = Rook, .row = 0, .col = 7});
        setPiece(Piece{.color = White, .type = Knight, .row = 0, .col = 1});
        setPiece(Piece{.color = White, .type = Knight, .row = 0, .col = 6});
        setPiece(Piece{.color = White, .type = Bishop, .row = 0, .col = 2});
        setPiece(Piece{.color = White, .type = Bishop, .row = 0, .col = 5});
        setPiece(Piece{.color = White, .type = Queen, .row = 0, .col = 3});
        setPiece(Piece{.color = White, .type = King, .row = 0, .col = 4});

        // Black pieces at row 7
        setPiece(Piece{.color = Black, .type = Rook, .row = 7, .col = 0});
        setPiece(Piece{.color = Black, .type = Rook, .row = 7, .col = 7});
        setPiece(Piece{.color = Black, .type = Knight, .row = 7, .col = 1});
        setPiece(Piece{.color = Black, .type = Knight, .row = 7, .col = 6});
        setPiece(Piece{.color = Black, .type = Bishop, .row = 7, .col = 2});
        setPiece(Piece{.color = Black, .type = Bishop, .row = 7, .col = 5});
        setPiece(Piece{.color = Black, .type = Queen, .row = 7, .col = 3});
        setPiece(Piece{.color = Black, .type = King, .row = 7, .col = 4});
    }

    std::vector<Move> getAvailableMoves() {
        std::vector<Move> moves{};

    }

    bool isKingInCheck(const PieceColor color) const {
        if (color == White) return whiteKing & attackedSquares.byBlack;

        return blackKing & attackedSquares.byWhite;
    }

    void setPiece(const Piece piece) {
        if (const auto existing = getBoardWithPiece(piece.row, piece.col))
            removePiece(*existing, piece.row, piece.col);

        const std::uint64_t setPieceMask = getBoardBitMaskOrZero(piece.row, piece.col);
        if (const auto bitBoard = getBoard(piece.color, piece.type); bitBoard != nullptr) {
            *bitBoard |= setPieceMask;
            occupiedSquares |= setPieceMask;
        }
    }

    BitBoard *getBoard(const PieceColor color, const PieceType pieceType) {
        switch (pieceType) {
            case Pawn: return color == White ? &whitePawns : &blackPawns;
            case Knight: return color == White ? &whiteKnights : &blackKnights;
            case Bishop: return color == White ? &whiteBishops : &blackBishops;
            case Rook: return color == White ? &whiteRooks : &blackRooks;
            case Queen: return color == White ? &whiteQueens : &blackQueens;
            case King: return color == White ? &whiteKing : &blackKing;
        }

        return nullptr;
    }

    BitBoard *getBoardWithPiece(const std::int8_t row, const std::int8_t col) {
        const std::uint64_t positionMask = getBoardBitMaskOrZero(row, col);
        if (positionMask & whitePawns) return &whitePawns;
        if (positionMask & blackPawns) return &blackPawns;
        if (positionMask & whiteKnights) return &whiteKnights;
        if (positionMask & blackKnights) return &blackKnights;
        if (positionMask & whiteBishops) return &whiteBishops;
        if (positionMask & blackBishops) return &blackBishops;
        if (positionMask & whiteRooks) return &whiteRooks;
        if (positionMask & blackRooks) return &blackRooks;
        if (positionMask & whiteQueens) return &whiteQueens;
        if (positionMask & blackQueens) return &blackQueens;
        if (positionMask & whiteKing)  return &whiteKing;
        if (positionMask & blackKing) return &blackKing;

        return nullptr;
    }

    void removePiece(BitBoard& board, const std::int8_t row, const std::int8_t col) {
        const std::uint64_t clearMask = ~getBoardBitMaskOrZero(row, col);
        board &= clearMask;
        occupiedSquares &= clearMask;
    }

    constexpr static std::uint64_t getBoardBitMaskOrZero(const std::int8_t row, const std::int8_t col) {
        if (row > 7 || col > 7 || row < 0 || col < 0)
            return 0;

        return 1ULL << (row * 8 + col);
    }

    constexpr static bool belongsToBoard(const std::int8_t row, const std::int8_t col) {
        return row <= 7 && col <= 7 && row >= 0 && col >= 0;
    }

    Board() {
        initBoard();
    }

private:
    void addPawnMoves(const PieceColor color, std::vector<Move>& moves) {
        const auto kingBoard = color == White ? whiteKing : blackKing;
        const auto kingRow = static_cast<std::uint8_t>(kingBoard / 8);
        const auto kingColumn = static_cast<std::uint8_t>(kingBoard % 8);


    }

    bool isAttackedFast(const PieceColor color, const std::int8_t row, const std::int8_t col) const {
        return
                isAttackedByPawn(color, row, col) ||
                isAttackedByBishop(color, row, col) ||
                isAttackedByKnight(color, row, col) ||
                isAttackedByRook(color, row, col) ||
                isAttackedByQueen(color, row, col) ||
                isAttackedByKing(color, row, col);
    }

    bool isSquareOccupied(const std::int8_t row, const std::int8_t col) const {
        return (getBoardBitMaskOrZero(row, col) & occupiedSquares) != 0;
    }

    bool isAttackedByKing(const PieceColor color, const std::int8_t row, const std::int8_t col) const {
        const auto attackingKing = color == White ? blackKing : whiteKing;

        const auto kingMask =
                        getBoardBitMaskOrZero(static_cast<std::int8_t>(row + 1), static_cast<std::int8_t>(col - 1)) |
                        getBoardBitMaskOrZero(static_cast<std::int8_t>(row - 1), static_cast<std::int8_t>(col - 1)) |
                        getBoardBitMaskOrZero(row, static_cast<std::int8_t>(col - 1)) |
                        getBoardBitMaskOrZero(static_cast<std::int8_t>(row + 1), col) |
                        getBoardBitMaskOrZero(static_cast<std::int8_t>(row - 1), col) |
                        getBoardBitMaskOrZero(static_cast<std::int8_t>(row - 1), static_cast<std::int8_t>(col + 1)) |
                        getBoardBitMaskOrZero(row, static_cast<std::int8_t>(col + 1)) |
                        getBoardBitMaskOrZero(static_cast<std::int8_t>(row + 1), static_cast<std::int8_t>(col + 1));

        return attackingKing & kingMask;
    }

    bool isAttackedByQueen(const PieceColor color, const std::int8_t row, const std::int8_t col) const {
        const auto attackingQueens = color == White ? blackQueens : whiteQueens;

        return isAttackedByDiagonalPiece(attackingQueens, row, col) || isAttackedByLateralPiece(attackingQueens, row, col);
    }

    bool isAttackedByRook(const PieceColor color, const std::int8_t row, const std::int8_t col) const {
        const auto attackingRooks = color == White ? blackRooks : whiteRooks;

        return isAttackedByLateralPiece(attackingRooks, row, col);
    }

    bool isAttackedByLateralPiece(const BitBoard attackingLateralPieces, const std::int8_t row, const std::int8_t col) const {
        for (std::int8_t i = 1; row + i < 8; ++i) {
            const auto newRow = static_cast<std::int8_t>(row + i);
            if (!isSquareOccupied(newRow, col))
                continue;

            if (attackingLateralPieces & getBoardBitMaskOrZero(newRow, col))
                return true;

            break;
        }

        for (std::int8_t i = 1; col + i < 8; ++i) {
            const auto newCol = static_cast<std::int8_t>(col + i);
            if (!isSquareOccupied(row, newCol))
                continue;

            if (attackingLateralPieces & getBoardBitMaskOrZero(row, newCol))
                return true;

            break;
        }

        for (std::int8_t i = 1; row - i >= 0; ++i) {
            const auto newRow = static_cast<std::int8_t>(row - i);
            if (!isSquareOccupied(newRow, col))
                continue;

            if (attackingLateralPieces & getBoardBitMaskOrZero(newRow, col))
                return true;

            break;
        }

        for (std::int8_t i = 1; col - i >= 0; ++i) {
            const auto newCol = static_cast<std::int8_t>(col - i);
            if (!isSquareOccupied(row, newCol))
                continue;

            if (attackingLateralPieces & getBoardBitMaskOrZero(row, newCol))
                return true;

            break;
        }

        return false;
    }

    static constexpr std::pair<std::int8_t, std::int8_t> knightMoves[8] = {
        {-2, -1},
        {-2, 1},
        {-1, -2},
        {-1, 2},
        {2, -1},
        {2, 1},
        {1, -2},
        {1, 2},
    };

    bool isAttackedByKnight(const PieceColor color, const std::int8_t row, const std::int8_t col) const {
        const auto attackerKnights = color == White ? blackKnights : whiteKnights;

        return std::ranges::any_of(knightMoves, [&](const auto& move) {
            const auto [xOffset, yOffset] = move;
            const std::int8_t newRow = row + yOffset;
            const std::int8_t newCol = col + xOffset;

            if (!belongsToBoard(newRow, newCol)) return false;
            return (getBoardBitMaskOrZero(newRow, newCol) & attackerKnights) != 0;
        });

    }

    bool isAttackedByBishop(const PieceColor color, const std::int8_t row, const std::int8_t col) const {
        const auto attackerPieces = color == White ? blackBishops : whiteBishops;
        return isAttackedByDiagonalPiece(attackerPieces, row, col);
    }

    bool isAttackedByDiagonalPiece(
        const BitBoard attackingDiagonalPieces,
        const std::int8_t row,
        const std::int8_t col
    ) const {
        // top right diagonal
        for (std::int8_t i = 1; col + i < 8 && row + i < 8; ++i) {
            const auto y = static_cast<int8_t>(row + i);
            const auto x = static_cast<int8_t>(col + i);
            if (isSquareOccupied(y, x) ) {
                if (attackingDiagonalPieces & getBoardBitMaskOrZero(y, x))
                    return true;
                break;
            }
        }

        // bottom right diagonal
        for (std::int8_t i = 1; col + i < 8 && row - i >= 0; ++i) {
            const auto y = static_cast<int8_t>(row - i);
            const auto x = static_cast<int8_t>(col + i);
            if (isSquareOccupied(y, x) ) {
                if (attackingDiagonalPieces & getBoardBitMaskOrZero(y, x))
                    return true;
                break;
            }
        }

        // top left diagonal
        for (std::int8_t i = 1; col - i >= 0 && row + i < 8; ++i) {
            const auto y = static_cast<int8_t>(row + i);
            const auto x = static_cast<int8_t>(col - i);
            if (isSquareOccupied(y, x) ) {
                if (attackingDiagonalPieces & getBoardBitMaskOrZero(y,x))
                    return true;
                break;
            }
        }

        // bottom left diagonal
        for (std::int8_t i = 1; col - i >= 0 && row - i >= 0; ++i) {
            const auto y = static_cast<int8_t>(row - i);
            const auto x = static_cast<int8_t>(col - i);
            if (isSquareOccupied(y, x) ) {
                if (attackingDiagonalPieces & getBoardBitMaskOrZero(y, x))
                    return true;
                break;
            }
        }

        return false;
    }

    bool isAttackedByPawn(const PieceColor color, const std::int8_t row, const std::int8_t col) const {
        if (color == White && row >= 6)
            return false;

        if (color == Black && row <= 1)
            return false;

        if (color == White) {
            return (col != 0 && (getBoardBitMaskOrZero(static_cast<int8_t>(row - 1), static_cast<int8_t>(col - 1)) & blackPawns)) ||
                   (col != 7 && (getBoardBitMaskOrZero(static_cast<int8_t>(row - 1), static_cast<int8_t>(col + 1)) & blackPawns));
        }

        return (getBoardBitMaskOrZero(static_cast<int8_t>(row + 1), static_cast<int8_t>(col - 1)) & whitePawns) ||
              (getBoardBitMaskOrZero(static_cast<int8_t>(row + 1), static_cast<int8_t>(col + 1)) & whitePawns);
    }
};


#endif //CHESSENGINE_BOARD_H
