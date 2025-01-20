#include "Ball.hpp"

Ball::Ball(int posX, int posY, float radius, int speedX, int speedY, Color color)
    : posX(posX), posY(posY), radius(radius), speedX(speedX), speedY(speedY), color(color) {}

int Ball::getPosX(){ return posX; }
int Ball::getPosY(){ return posY; }
float Ball::getRadius(){ return radius; }
int Ball::getspeedX(){ return speedX; }
int Ball::getSpeedY(){ return speedY; }
Color Ball::getColor(){ return color; }

void Ball::setPosX(int newValue){ posX = newValue; }
void Ball::setPosY(int newValue){ posY = newValue; }
void Ball::setRadius(float newValue){ radius = newValue; }
void Ball::setSpeedX(int newValue){ speedX = newValue; }
void Ball::setSpeedY(int newValue){ speedY = newValue; }
void Ball::setColor(Color newValue){ color = newValue; }

void Ball::draw(){
    DrawCircle(posX, posY, radius, color);
}

void Ball::update(int& playerScore, int& enemyScore){
    setPosX(getPosX() + getspeedX());
    setPosY(getPosY() + getSpeedY());
    if(getPosY() < 0 + getRadius() || getPosY() > GetScreenHeight() - getRadius()){
        setSpeedY(getSpeedY() * -1);
    }
    if(getPosX() < 0 + getRadius() || getPosX() > GetScreenWidth() - getRadius()){
        setSpeedX(getspeedX() * -1);
    }

    if (getPosX() + getRadius() >= GetScreenWidth()) {
        playerScore++;
        setPosX(GetScreenWidth() / 2);
        setPosY(GetScreenHeight() / 2);
        setSpeedX(GetRandomValue(0, 1) == 0 ? -7 : 7);  // Bola bergerak dengan kecepatan -7 atau 7
        setSpeedY(GetRandomValue(0, 1) == 0 ? -7 : 7);  // Bisa diatur untuk kecepatan Y juga
    }

    if (getPosX() - getRadius() <= 0) {
        enemyScore++;
        setPosX(GetScreenWidth() / 2);
        setPosY(GetScreenHeight() / 2);
        setSpeedX(GetRandomValue(0, 1) == 0 ? -7 : 7);  // Bola bergerak dengan kecepatan -7 atau 7
        setSpeedY(GetRandomValue(0, 1) == 0 ? -7 : 7);  // Bisa diatur untuk kecepatan Y juga
    }
}