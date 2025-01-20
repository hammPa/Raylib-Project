#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>
#include "Entity.hpp"

class Player: public Entity {
public:
    Player(int width, int height, int posX, int posY, int speedY, Color color);

    void draw() override;

    void update(int ballPosY) override;
};

#endif