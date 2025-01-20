#include "Entity.hpp"

Entity::Entity(int width, int height, int posX, int posY, int speedY, Color color)
: width(width), height(height), posX(posX), posY(posY), speedY(speedY), color(color) {}

int Entity::getPosX(){ return posX; }
int Entity::getPosY(){ return posY; }
int Entity::getWidth(){ return width; }
int Entity::getHeight(){ return height; }
int Entity::getSpeedY(){ return speedY; }
Color Entity::getColor(){ return color; }


void Entity::setPosX(int newVal){ posX = newVal; }
void Entity::setPosY(int newVal){ posY = newVal; }
void Entity::setWidth(int newVal){ width = newVal; }
void Entity::setHeight(int newVal){ height = newVal; }
void Entity::setSpeedY(int newVal){ speedY = newVal; }
void Entity::setColor(Color newVal){ color = newVal; }
    
void Entity::draw(){};
void Entity::update(int ballPosY){};