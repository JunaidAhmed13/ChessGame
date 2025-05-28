#pragma once
#include <SFML/Graphics.hpp>

enum Color { WHITE, BLACK };

class Board; // Forward declaration

class Piece {
public:
    Piece(Color c) : color(c) {}
    virtual ~Piece() {}
    Color getColor() const { return color; }
    virtual void draw(sf::RenderWindow& window, int x, int y) = 0;
    virtual bool isValidMove(int sx, int sy, int dx, int dy, const Board& board) = 0;
protected:
    Color color;
};
