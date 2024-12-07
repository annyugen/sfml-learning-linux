#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Tile {
    private:
        sf::Sprite sprite; 
    public:
        Tile(sf::Texture& texture, sf::IntRect textureRect);
        const sf::FloatRect getGlobalBounds() const;

        // Render functions
        void update();
        void render(sf::RenderTarget& renderTarget);
};
