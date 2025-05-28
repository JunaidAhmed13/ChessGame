#include "King.h"
#include <iostream>

sf::Texture King::whiteTexture;
sf::Texture King::blackTexture;
bool King::texturesLoaded = false;

void King::loadTextures() {
    if (!texturesLoaded) {
        if (!whiteTexture.loadFromFile("images/white/king.png"))
            std::cerr << "Failed to load images/white/king.png\n";
        if (!blackTexture.loadFromFile("images/black/king.png"))
            std::cerr << "Failed to load images/black/king.png\n";
        texturesLoaded = true;
    }
}

King::King(Color c) : Piece(c) {
    loadTextures();
}

void King::draw(sf::RenderWindow& window, int x, int y) {
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

bool King::isValidMove(int sx, int sy, int dx, int dy, const Board& board) {
    if (abs(dx - sx) <= 1 && abs(dy - sy) <= 1) {
        Piece* dest = board.getPiece(dx, dy);
        if (dest == nullptr || dest->getColor() != color)
            return true;
    }
    return false;
}
