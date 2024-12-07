#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT = 1, MOVING_RIGHT = 2, JUMPING = 3, FALLING = 4 };

class Player {
    private:
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Sprite runningSprite;
        sf::Texture runningTexture;

        // Animation
        short animationState;
        sf::IntRect currentFrame;
        sf::Clock animationClock;
        bool animationSwitch;
        
        // Physics
        sf::Vector2f velocity;
        float maxVelocity;
        float minVelocity;
        float acceleration;
        float deceleration;
        float gravity;
        float maxVelocityY;
        

        // Core

        // Intitializers
        void initSpriteState();
        void initTexture();
        void initSprite();
        void initAnimation();
        void initPhysics();

    public:
        Player();
        virtual ~Player();

        const bool& getAnimationSwitch();
        const sf::FloatRect getGlobalBounds() const;

        // Modifier for bounding
        void setPosition(const float x, const float y);
        void resetVelocityY();

        // Animation functions
        void updateMovement(const float xDirection, const float yDirection); 
        void updatePhysics();
        void updateMovement();
        void updateAnimation();
        void resetAnimationClock();

        // Rendering functions
        void update();
        void render(sf::RenderTarget& renderTarget);
};