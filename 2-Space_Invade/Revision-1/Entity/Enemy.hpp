#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "../Bullet/Bullet.hpp"
#include <iostream>

class Enemy: public Entity {
private:
    float delay;
    float time;
    int tilePosition = 0;
    float scale = 3.0f;
    float radius;
    std::vector<Bullet> *address_of_bullets;
public:
    Enemy(int x, int y, int sx, int sy, int w, int h, Texture2D t, int d, int hp);

    void draw() override;

    void attack(Entity& player) override;

    void update(Entity& player) override;

    void set_bullets(std::vector<Bullet>&  bullets);
};

#endif