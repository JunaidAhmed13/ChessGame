#pragma once
#include "Piece.h"
#include "Board.h"

class Rook : public Piece {
public:
    Rook(Color c);
    void draw(sf::RenderWindow& window, int x, int y) override;
    bool isValidMove(int sx, int sy, int dx, int dy, const Board& board) override;
private:
    static sf::Texture whiteTexture;
    static sf::Texture blackTexture;
    static bool texturesLoaded;
    static void loadTextures();
};
