#include "Entity.hpp"

Entity::Entity(int x, int y, int sx, int sy, int w, int h, Texture2D t, int d, int hp)
    : posX(x), posY(y), speedX(sx), speedY(sy), width(w), height(h), texture(t), damage(d), healthPoint(hp) {}

int Entity::getPosX(){ return posX; }
int Entity::getPosY(){ return posY; }
int Entity::getSpeedX(){ return speedX; }
int Entity::getSpeedY(){ return speedY; }
int Entity::getWidth(){ return width; }
int Entity::getHeight(){ return height; }    
Texture2D Entity::getTexture(){ return texture; }
int Entity::getHp(){ return healthPoint; }

int Entity::getScaleWidth(){ return scaleWidth; }
int Entity::getScaleHeight(){ return scaleHeight; }

void Entity::setPosX(int newValue){ posX = newValue; }
void Entity::setPosY(int newValue){ posY = newValue; }
void Entity::setSpeedX(int newValue){ speedX = newValue; }
void Entity::setSpeedY(int newValue){ speedY = newValue; }
void Entity::setWidth(int newValue){ width = newValue; }
void Entity::setHeight(int newValue){ height = newValue; }
void Entity::setTexture(Texture newValue){ texture = newValue; }
void Entity::setHp(int newValue){ healthPoint = newValue; }

void Entity::takeDamage(int bulletDamage){ healthPoint -= bulletDamage; }