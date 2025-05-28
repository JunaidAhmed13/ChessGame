#pragma once
#include "Board.h"
#include <vector>
#include <tuple>

class AI {
public:
    AI() = default;
    // Attempts to make a move for the given color. Returns true if a move was made.
    bool makeMove(Board& board, Color color);

private:
    // Returns all valid moves for the given color as (sx, sy, dx, dy) tuples.
    std::vector<std::tuple<int, int, int, int>> getAllValidMoves(const Board& board, Color color) const;
};
