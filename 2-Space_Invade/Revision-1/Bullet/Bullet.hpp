#ifndef BULLET_HPP
#define BULLET_HPP

#include <raylib.h>
#include "../Entity/Entity.hpp"
#include <vector>
#include <algorithm>

class Bullet {
private:
    int posX;
    int posY;
    int damage;
    float radius;
    int speedY;
    Color color;
    Entity *owner;
public:
    Bullet(int x, int y, int d, float r, int sy, Color c, Entity* o);

    int getPosX();
    int getPosY();
    int getDamage();
    float getRadius();
    int getSpeedY();
    Color getColor();

    void setPosX(int newValue);
    void setPosY(int newValue);
    void setDamage(int newValue);
    void setRadius(float newValue);
    void setSpeedY(int newValue);
    void setColor(Color newValue);

    bool operator==(const Bullet& other) const;

    void draw();

    void update(Entity& entity, std::vector<Bullet>& bullets);
};

#endif