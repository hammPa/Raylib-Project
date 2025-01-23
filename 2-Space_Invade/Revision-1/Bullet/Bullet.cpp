#include "Bullet.hpp"
    
Bullet::Bullet(int x, int y, int d, float r, int sy, Color c, Entity* o)
    : posX(x), posY(y), damage(d), radius(r), speedY(sy), color(c), owner(o) {}

int Bullet::getPosX(){ return posX; }
int Bullet::getPosY(){ return posY; }
int Bullet::getDamage(){ return damage; }
float Bullet::getRadius(){ return radius; }
int Bullet::getSpeedY(){ return speedY; }
Color Bullet::getColor(){ return color; }

void Bullet::setPosX(int newValue){ posX = newValue; }
void Bullet::setPosY(int newValue){ posY = newValue; }
void Bullet::setDamage(int newValue){ damage = newValue; }
void Bullet::setRadius(float newValue){ radius = newValue; }
void Bullet::setSpeedY(int newValue){ speedY = newValue; }
void Bullet::setColor(Color newValue){ color = newValue; }

bool Bullet::operator==(const Bullet& other) const { // untuk std::find
    return posX == other.posX &&
           posY == other.posY &&
           damage == other.damage &&
           radius == other.radius &&
           speedY == other.speedY &&
           color.r == other.color.r && color.g == other.color.g &&
           color.b == other.color.b && color.a == other.color.a &&
           owner == other.owner;  // assuming owner comparison is valid
}

void Bullet::draw(){
    DrawCircle(posX, posY, radius, color);
}

void Bullet::update(Entity& entity, std::vector<Bullet>& bullets){
    posY += speedY;
    
    if(posY < 0 || posY > GetScreenHeight()){
        std::vector<Bullet>::iterator it = std::find(bullets.begin(), bullets.end(), *this);  // Cari peluru di vektor
        if (it != bullets.end()) {
            bullets.erase(it);  // Hapus peluru dari vektor
        }
    }
    if (CheckCollisionCircleRec(
            Vector2{(float)posX, (float)posY}, radius,
            Rectangle{(float)entity.getPosX(), (float)entity.getPosY(), (float)entity.getScaleWidth(), (float)entity.getScaleHeight()}
    )) {
        if (&entity != owner) {  // Pastikan peluru tidak mengenai dirinya sendiri
            entity.takeDamage(damage);  // Berikan damage pada entity yang tertabrak
            
            std::vector<Bullet>::iterator it = std::find(bullets.begin(), bullets.end(), *this);  // Cari peluru di vektor
            if (it != bullets.end()) {
                bullets.erase(it);  // Hapus peluru dari vektor
            }
        }
    }
}