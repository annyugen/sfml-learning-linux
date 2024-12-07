#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"

void Game::initWindow() {
    this->window.create(sf::VideoMode(800, 600), "Cat Attack", sf::Style::Default);
    this->window.setFramerateLimit(60);
}

void Game::initPlayer() { this->player = new Player(); }

// Construct
Game::Game() {
    this->initWindow();    
    this->initPlayer();
}

// Destructor
Game::~Game() {
    delete this->player;
}

void Game::renderPlayer() {
    this->player->render(this->window);
}

void Game::updatePlayer() {
    this->player->update();
}

void Game::update() {
    while(this->window.pollEvent(this->windowEvent)) {
        switch(this->windowEvent.type) {
            case sf::Event::Closed:
                this->window.close();
                break;
            case sf::Event::KeyPressed:
                if(this->windowEvent.key.code == sf::Keyboard::Escape)
                    this->window.close();
                break;
        }
    }

    this->updatePlayer();
}

void Game::render() {
    // Always clear first before rendering per SFML guideline.
    this->window.clear();

    // Render game
    this->renderPlayer();

    this->window.display();
}

const sf::RenderWindow& Game::getWindow() const {
    return this->window;
}
