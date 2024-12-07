#pragma once

#include<iostream>

#include "Player.h"

class Game {
    private:
        sf::RenderWindow window;
        sf::Event windowEvent;
        void initWindow();
        bool endGame;

        Player* player;
        void initPlayer();

    public:
        //Functions
        Game();
        virtual ~Game();

        //Functions
        void updatePlayer();
        void update();
        void updateCollision();

        void renderPlayer();
        void render();

        const sf::RenderWindow& getWindow() const;
};
