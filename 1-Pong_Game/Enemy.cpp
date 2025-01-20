#include "Enemy.hpp"

Enemy::Enemy(int width, int height, int posX, int posY, int speedY, Color color)
    : Entity(width, height, posX, posY, speedY, color) {}

void Enemy::draw() {
    DrawRectangle(getPosX(), getPosY(), getWidth(), getHeight(), getColor());
}

void Enemy::update(int ballPosY) {
    if(getPosY() + getHeight() / 2 > ballPosY) setPosY(getPosY() - getSpeedY());
    if(getPosY() + getHeight() / 2 < ballPosY) setPosY(getPosY() + getSpeedY());
}