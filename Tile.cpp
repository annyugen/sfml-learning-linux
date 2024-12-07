#include "Tile.h"

Tile::Tile(sf::Texture& texture, sf::IntRect textureRect) {
    this->sprite.setTexture(texture);
    this->sprite.setTextureRect(textureRect);
}

const sf::FloatRect Tile::getGlobalBounds() const { 
    return this->sprite.getGlobalBounds(); 
}

void Tile::update() {

}

void Tile::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(this->sprite);
}
