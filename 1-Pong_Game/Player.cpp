#include "Player.hpp"

Player::Player(int width, int height, int posX, int posY, int speedY, Color color)
    : Entity(width, height, posX, posY, speedY, color) {}

void Player::draw() {
    DrawRectangle(getPosX(), getPosY(), getWidth(), getHeight(), getColor());
}

void Player::update(int ballPosY) {
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        setPosY(getPosY() + getSpeedY());
    }
    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
        setPosY(getPosY() - getSpeedY());
    }
    if(getPosY() < 0) setPosY(0);
    if(getPosY() > GetScreenHeight() - getHeight()) setPosY(GetScreenHeight() - getHeight());
}