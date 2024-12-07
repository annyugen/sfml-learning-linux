#include <iostream>

#include "Player.h"

void Player::initSpriteState() {
    this->animationState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::initTexture() {
    if(!this->texture.loadFromFile("assets/FreeCatCharacterAnimations/1_Cat_Idle-Sheet.png")) {
        std::cout << "ERROR::PLAYER::Could not load player sprite sheet" << "\n";
    }

    if(!this->runningTexture.loadFromFile("assets/FreeCatCharacterAnimations/2_Cat_Run-Sheet.png")) {
        std::cout << "ERROR::PLAYER::Could not load player running sprite sheet" << "\n";
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
    this->animationSwitch = true;
}

void Player::initPhysics() {
    this->maxVelocity = 10.f;
    this->minVelocity = 1.f;
    this->acceleration = 2.f;
    this->deceleration = 0.8f; // Less value means more drag and stops faster
    this->gravity = 4.f;
    this->maxVelocityY = 15.f; 
}

Player::Player() {
    // Order matters. Need to load texture first before applying to sprite. 
    // Remember sprite is just pixels that got texture applied on them
    this->initSpriteState();
    this->initTexture();
    this->initSprite();
    this->initAnimation();
    this->initPhysics();
}

Player::~Player() {}

const bool& Player::getAnimationSwitch() {
    // To avoid return a local var temAnimationSwitch, since it would be allocated on a Stack and would be delete at the end of the function. To circumvent that, assign it as a static variable instead which is allocated on the heap.
    static bool tempAnimationSwitch = this->animationSwitch;
    if (this->animationSwitch) 
        this->animationSwitch = false;
    
    return tempAnimationSwitch;
}

const sf::FloatRect Player::getGlobalBounds() const { 
    return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y) {
    this->sprite.setPosition(x , y);
}


void Player::resetVelocityY() {
    this->velocity.y = 0.f;
}

void Player::updateMovement(const float xDirection, const float yDirection) {
    // Accelerate 
    this->velocity.x += xDirection * this->acceleration;

    // Limit velocity
    if (std::abs(this->velocity.x) > this->maxVelocity) {
        this->velocity.x = this->maxVelocity * ((this->velocity.x < 0) ? -1.f : 1.f); // checking if velocity.x is negative or positive to signal moving left or right. 
    }
}

void Player::updatePhysics() {
    // Gravity
    this->velocity.y += 1.0 * this->gravity;
    // Limit gravity
    if (std::abs(this->velocity.y) > this->maxVelocityY) {
        this->velocity.y = this->maxVelocityY * ((this->velocity.y < 0) ? -1.f : 1.f); 
    }

    // Decelerate
    this->velocity *= this->deceleration;

    // Limit deceleration
    if (std::abs(this->velocity.x) < this->minVelocity) {
        this->velocity.x = 0.f;
    }
    if (std::abs(this->velocity.y) < this->minVelocity) {
        this->velocity.y = 0.f;
    }

    this->sprite.move(this->velocity);
}

void Player::updateMovement() {
    this->animationState = PLAYER_ANIMATION_STATES::IDLE;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this->updateMovement(-5.f, 0.f);
        this->animationState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this->updateMovement(5.f, 0.f);
        this->animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        this->updateMovement(0.f, -5.f);
        this->animationState = PLAYER_ANIMATION_STATES::JUMPING;
    }
}

void Player::updateAnimation() {
    // Idle animation
    if (this->animationState == PLAYER_ANIMATION_STATES::IDLE) {
    // animationClock will control how fast the sprite frame will cycle
        if (this->animationClock.getElapsedTime().asSeconds() >= 0.15f) {
                this->sprite.setTexture(this->texture);
                this->currentFrame.left += 32.f;
                if (this->currentFrame.left >= 224.f) {
                    this->currentFrame.left = 0;
                }
            
            // Restart animation clock.
            this->animationClock.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    } else if (this->animationState == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
        if (this->animationClock.getElapsedTime().asSeconds() >= 0.1f) {
            this->sprite.setTexture(this->runningTexture);
            this->currentFrame.left += 32.f;
            if (this->currentFrame.left >= 288.f) {
                this->currentFrame.left = 0;
            }
            
            // Restart animation clock.
            this->animationClock.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    } else {
        this->animationClock.restart();
    }
}

void Player::resetAnimationClock() {
    this->animationClock.restart();
    this->animationSwitch = true;
}

void Player::update() {
    this->updateMovement();
    this->updateAnimation();
    this->updatePhysics();
}

void Player::render(sf::RenderTarget & renderTarget) {
    renderTarget.draw(this->sprite);
}
