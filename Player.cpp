#include <iostream>

#include "Player.h"

void Player::initSpriteState() {
    this->moving = false;
}

void Player::initTexture() {
    if(!this->texture.loadFromFile("assets/FreeCatCharacterAnimations/1_Cat_Idle-Sheet.png")) {
        std::cout << "ERROR::PLAYER::Could not load player sprite sheet" << "\n";
    }
}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(100.f, 100.f);
    this->currentFrame = sf::IntRect(0 ,0, 32, 32);
    this->sprite.setTextureRect(this->currentFrame);
    this->sprite.setScale(3.f, 3.f);
}

void Player::initAnimation() {
    this->animationClock.restart();
}

Player::Player() {
    // Order matters. Need to load texture first before applying to sprite. 
    // Remember sprite is just pixels that got texture applied on them
    this->initSpriteState();
    this->initTexture();
    this->initSprite();
    this->initAnimation();
}

Player::~Player() {}

void Player::updateMovement() {
    this->moving = false;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this->sprite.move(-5.f, 0.f);
        this->moving = true;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this->sprite.move(5.f, 0.f);
        this->moving = true;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        this->sprite.move(0.f, -5.f);
        this->moving = true;
    }
}

void Player::updateAnimation() {
    // Idle animation
    // animationClock will control how fast the sprite frame will cycle
    if (this->animationClock.getElapsedTime().asSeconds() >= 0.25f) {
        if (this->moving == false) {
            this->currentFrame.left += 32.f;
            if (this->currentFrame.left >= 224.f) {
                this->currentFrame.left = 0;
            }
        }
        // Restart animation clock.
        this->animationClock.restart();
        this->sprite.setTextureRect(this->currentFrame);
    }
}

void Player::update() {
    this->updateMovement();
    this->updateAnimation();
}

void Player::render(sf::RenderTarget & renderTarget) {
    renderTarget.draw(this->sprite);
}
