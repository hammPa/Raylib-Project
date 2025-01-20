#ifndef BALL_HPP
#define BALL_HPP

#include <raylib.h>

class Ball {
private:
    int posX, posY;
    float radius;
    int speedX, speedY;
    Color color;
public:
    Ball(int posX, int posY, float radius, int speedX, int speedY, Color color);

    int getPosX();
    int getPosY();
    float getRadius();
    int getspeedX();
    int getSpeedY();
    Color getColor();

    void setPosX(int newValue);
    void setPosY(int newValue);
    void setRadius(float newValue);
    void setSpeedX(int newValue);
    void setSpeedY(int newValue);
    void setColor(Color newValue);
    void draw();
    void update(int& playerScore, int& enemyScore);
};

#endif