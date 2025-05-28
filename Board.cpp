

#include "Board.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include <iostream>
#include <SFML/Graphics.hpp>




Board::Board() {
    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
            squares[x][y] = nullptr;
}

Board::~Board() {
    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
            delete squares[x][y];
}

Piece* Board::getPiece(int x, int y) const {
    if (!isInsideBoard(x, y)) return nullptr;
    return squares[x][y];
}

void Board::setPiece(int x, int y, Piece* piece) {
    if (isInsideBoard(x, y))
        squares[x][y] = piece;
}

bool Board::isInsideBoard(int x, int y) const {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

bool Board::isPathClear(int sx, int sy, int dx, int dy) const {
    int xDir = (dx - sx) == 0 ? 0 : (dx - sx) / abs(dx - sx);
    int yDir = (dy - sy) == 0 ? 0 : (dy - sy) / abs(dy - sy);

    int x = sx + xDir;
    int y = sy + yDir;
    while (x != dx || y != dy) {
        if (getPiece(x, y) != nullptr)
            return false;
        x += xDir;
        y += yDir;
    }
    return true;
}

bool Board::isValidMove(int sx, int sy, int dx, int dy, Color color) const {
    if (!isInsideBoard(sx, sy) || !isInsideBoard(dx, dy)) return false;
    Piece* piece = getPiece(sx, sy);
    if (!piece || piece->getColor() != color) return false;
    return piece->isValidMove(sx, sy, dx, dy, *this);
}

bool Board::movePiece(int sx, int sy, int dx, int dy) {
    if (!isInsideBoard(sx, sy) || !isInsideBoard(dx, dy)) return false;
    Piece* piece = getPiece(sx, sy);
    if (!piece) return false;
    if (!piece->isValidMove(sx, sy, dx, dy, *this)) return false;
    Piece* dest = getPiece(dx, dy);
    if (dest) delete dest;
    setPiece(dx, dy, piece);
    setPiece(sx, sy, nullptr);

    // Pawn promotion check
    Pawn* pawn = dynamic_cast<Pawn*>(piece);
    if (pawn) {
        if ((pawn->getColor() == WHITE && dy == 7) ||
            (pawn->getColor() == BLACK && dy == 0)) {
            promotionPending = true;
            promotionColor = pawn->getColor();
        }
    }
    return true;
}

void Board::promotePawn(int x, int y, Piece* newPiece) {
    Piece* oldPawn = getPiece(x, y);
    if (oldPawn) delete oldPawn;
    setPiece(x, y, newPiece);
    promotionPending = false;
}

void Board::setup() {
    // Clear board
    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y) {
            delete squares[x][y];
            squares[x][y] = nullptr;
        }

    // Place pawns
    for (int x = 0; x < 8; ++x) {
        setPiece(x, 6, new Pawn(BLACK)); // Black pawns at bottom
        setPiece(x, 1, new Pawn(WHITE)); // White pawns at top
    }

    // Place other pieces
    setPiece(0, 7, new Rook(BLACK));
    setPiece(7, 7, new Rook(BLACK));
    setPiece(0, 0, new Rook(WHITE));
    setPiece(7, 0, new Rook(WHITE));

    setPiece(1, 7, new Knight(BLACK));
    setPiece(6, 7, new Knight(BLACK));
    setPiece(1, 0, new Knight(WHITE));
    setPiece(6, 0, new Knight(WHITE));

    setPiece(2, 7, new Bishop(BLACK));
    setPiece(5, 7, new Bishop(BLACK));
    setPiece(2, 0, new Bishop(WHITE));
    setPiece(5, 0, new Bishop(WHITE));

    setPiece(3, 7, new Queen(BLACK));
    setPiece(3, 0, new Queen(WHITE));

    setPiece(4, 7, new King(BLACK));
    setPiece(4, 0, new King(WHITE));
}

void Board::draw(sf::RenderWindow& window) const {
    sf::Vector2u winSize = window.getSize();
    float tileSize = std::min(winSize.x, winSize.y) / 8.f;
    sf::Color light(234, 233, 210);
    sf::Color dark(75, 115, 75);

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            sf::RectangleShape square(sf::Vector2f(tileSize, tileSize));
            square.setFillColor(((x + y) % 2 == 0) ? light : dark);
            square.setPosition(x * tileSize, y * tileSize);
            window.draw(square);
        }
    }

    // Draw pieces
    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
            if (squares[x][y])
                squares[x][y]->draw(window, x, y); // y is not flipped
}

