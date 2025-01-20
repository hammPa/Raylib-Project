#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>
#include "Entity.hpp"

class Enemy: public Entity {
public:
    Enemy(int width, int height, int posX, int posY, int speedY, Color color);

    void draw() override;

    void update(int ballPosY) override;
};

#endif