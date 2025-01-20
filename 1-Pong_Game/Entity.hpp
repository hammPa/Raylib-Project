#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <raylib.h>

class Entity {
private:
    int posX, posY, width, height;
    int speedY;
    Color color;
public:
    Entity(int width, int height, int posX, int posY, int speedY, Color color);

    int getPosX();
    int getPosY();
    int getWidth();
    int getHeight();
    int getSpeedY();
    Color getColor();


    void setPosX(int newVal);    void setPosY(int newVal);
    void setWidth(int newVal);
    void setHeight(int newVal);
    void setSpeedY(int newVal);
    void setColor(Color newVal);

    virtual void draw() = 0;
    virtual void update(int ballPosY) = 0;
};

#endif