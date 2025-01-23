#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <raylib.h>

class Entity {
protected:
    int posX;
    int posY;
    int speedX;
    int speedY;
    int width;
    int height;
    Texture2D texture;
    int damage;
    int healthPoint;
    int scaleWidth;
    int scaleHeight;
public:
    Entity(int x, int y, int sx, int sy, int w, int h, Texture2D t, int d, int hp);

    int getPosX();
    int getPosY();
    int getSpeedX();
    int getSpeedY();
    int getWidth();
    int getHeight();    
    Texture2D getTexture();
    int getHp();

    int getScaleWidth();
    int getScaleHeight();

    void setPosX(int newValue) ;
    void setPosY(int newValue);
    void setSpeedX(int newValue);
    void setSpeedY(int newValue);
    void setWidth(int newValue);
    void setHeight(int newValue);
    void setTexture(Texture newValue);
    void setHp(int newValue);

    void takeDamage(int bulletDamage);

    virtual void draw() = 0;
    virtual void update(Entity& target) = 0;
    virtual void attack(Entity& entity) = 0;
};


#endif