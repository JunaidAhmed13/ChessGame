#include "Knight.h"
#include <iostream>

sf::Texture Knight::whiteTexture;
sf::Texture Knight::blackTexture;
bool Knight::texturesLoaded = false;

void Knight::loadTextures() {
    if (!texturesLoaded) {
        if (!whiteTexture.loadFromFile("images/white/knight.png"))
            std::cerr << "Failed to load images/white/knight.png\n";
        if (!blackTexture.loadFromFile("images/black/knight.png"))
            std::cerr << "Failed to load images/black/knight.png\n";
        texturesLoaded = true;
    }
}

Knight::Knight(Color c) : Piece(c) {
    loadTextures();
}

void Knight::draw(sf::RenderWindow& window, int x, int y) {
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

bool Knight::isValidMove(int sx, int sy, int dx, int dy, const Board& board) {
    int dxAbs = abs(dx - sx);
    int dyAbs = abs(dy - sy);
    if (!((dxAbs == 2 && dyAbs == 1) || (dxAbs == 1 && dyAbs == 2)))
        return false;
    Piece* dest = board.getPiece(dx, dy);
    if (dest == nullptr || dest->getColor() != color)
        return true;
    return false;
}
