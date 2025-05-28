#include "AI.h"
#include <cstdlib>
#include <ctime>

bool AI::makeMove(Board& board, Color color) {
    std::vector<std::tuple<int, int, int, int>> moves = getAllValidMoves(board, color);
    if (moves.empty())
        return false;

    // Seed random once per program run
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    // Pick a random move
    int idx = std::rand() % moves.size();
    int sx, sy, dx, dy;
    std::tie(sx, sy, dx, dy) = moves[idx];
    board.movePiece(sx, sy, dx, dy);
    return true;
}

std::vector<std::tuple<int, int, int, int>> AI::getAllValidMoves(const Board& board, Color color) const {
    std::vector<std::tuple<int, int, int, int>> moves;
    for (int sx = 0; sx < 8; ++sx) {
        for (int sy = 0; sy < 8; ++sy) {
            Piece* piece = board.getPiece(sx, sy);
            if (piece && piece->getColor() == color) {
                for (int dx = 0; dx < 8; ++dx) {
                    for (int dy = 0; dy < 8; ++dy) {
                        if ((sx != dx || sy != dy) && board.isValidMove(sx, sy, dx, dy, color)) {
                            moves.emplace_back(sx, sy, dx, dy);
                        }
                    }
                }
            }
        }
    }
    return moves;
}
