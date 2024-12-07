#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Player {
    private:
        sf::Sprite sprite;
        sf::Texture texture;
        bool moving;

        // Animation
        sf::IntRect currentFrame;
        sf::Clock animationClock;
        // Movement

        // Core

        // Intitializers
        void initSpriteState();
        void initTexture();
        void initSprite();
        void initAnimation();

    public:
        Player();
        virtual ~Player();

        void updateMovement();
        void updateAnimation();

        // Rendering Functions
        void update();
        void render(sf::RenderTarget& renderTarget);
};