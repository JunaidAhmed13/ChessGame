#include "Rook.h"
#include <iostream>

sf::Texture Rook::whiteTexture;
sf::Texture Rook::blackTexture;
bool Rook::texturesLoaded = false;

void Rook::loadTextures() {
    if (!texturesLoaded) {
        if (!whiteTexture.loadFromFile("images/white/rook.png"))
            std::cerr << "Failed to load images/white/rook.png\n";
        if (!blackTexture.loadFromFile("images/black/rook.png"))
            std::cerr << "Failed to load images/black/rook.png\n";
        texturesLoaded = true;
    }
}

Rook::Rook(Color c) : Piece(c) {
    loadTextures();
}

void Rook::draw(sf::RenderWindow& window, int x, int y) {
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

bool Rook::isValidMove(int sx, int sy, int dx, int dy, const Board& board) {
    if (sx != dx && sy != dy) return false;
    if (!board.isPathClear(sx, sy, dx, dy)) return false;
    Piece* dest = board.getPiece(dx, dy);
    if (dest == nullptr || dest->getColor() != color)
        return true;
    return false;
}
