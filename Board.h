#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "Piece.h"

class Board {
public:
    Board();
    ~Board();

    void setup();
    void draw(sf::RenderWindow& window) const;

    Piece* getPiece(int x, int y) const;
    void setPiece(int x, int y, Piece* piece);

    bool isInsideBoard(int x, int y) const;
    bool isPathClear(int sx, int sy, int dx, int dy) const;
    bool isValidMove(int sx, int sy, int dx, int dy, Color color) const;
    bool movePiece(int sx, int sy, int dx, int dy);

    void promotePawn(int x, int y, Piece* newPiece);
    bool promotionPending = false;
    Color promotionColor;

private:
    Piece* squares[8][8];
};

#endif // BOARD_H
