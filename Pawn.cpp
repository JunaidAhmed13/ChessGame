#include "Pawn.h"
#include <iostream>

sf::Texture Pawn::whiteTexture;
sf::Texture Pawn::blackTexture;
bool Pawn::texturesLoaded = false;

void Pawn::loadTextures() {
    if (!texturesLoaded) {
        if (!whiteTexture.loadFromFile("images/white/pawn.png"))
            std::cerr << "Failed to load images/white/pawn.png\n";
        if (!blackTexture.loadFromFile("images/black/pawn.png"))
            std::cerr << "Failed to load images/black/pawn.png\n";
        texturesLoaded = true;
    }
}

Pawn::Pawn(Color c) : Piece(c) {
    loadTextures();
}

void Pawn::draw(sf::RenderWindow& window, int x, int y) {
    sf::Sprite sprite;
    sprite.setTexture(color == WHITE ? whiteTexture : blackTexture);
    float scaleX = 75.f / sprite.getTexture()->getSize().x;
    float scaleY = 75.f / sprite.getTexture()->getSize().y;
    float scale = std::min(scaleX, scaleY);
    sprite.setScale(scale, scale);
    float spriteWidth = sprite.getTexture()->getSize().x * scale;
    float spriteHeight = sprite.getTexture()->getSize().y * scale;
    float offsetX = (75.f - spriteWidth) / 2.f;
    float offsetY = (75.f - spriteHeight) / 2.f;
    sprite.setPosition(x * 75 + offsetX, y * 75 + offsetY);
    window.draw(sprite);
}

bool Pawn::isValidMove(int sx, int sy, int dx, int dy, const Board& board) {
    int direction = (color == WHITE) ? 1 : -1;
    int startRow = (color == WHITE) ? 1 : 6;

    // Forward move
    if (dx == sx && dy == sy + direction) {
        if (board.getPiece(dx, dy) == nullptr)
            return true;
    }
    // Double move from starting position
    if (dx == sx && dy == sy + 2 * direction && sy == startRow) {
        if (board.getPiece(dx, sy + direction) == nullptr &&
            board.getPiece(dx, dy) == nullptr)
            return true;
    }
    // Capture
    if (abs(dx - sx) == 1 && dy == sy + direction) {
        Piece* target = board.getPiece(dx, dy);
        if (target != nullptr && target->getColor() != color)
            return true;
    }
    return false;
}
