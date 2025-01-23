#include "Enemy.hpp"

Enemy::Enemy(int x, int y, int sx, int sy, int w, int h, Texture2D t, int d, int hp)
    : Entity(x, y, sx, sy, w, h, t, d, hp), delay(1), time(0) {
        scaleWidth = width * scale;
        scaleHeight = height * scale;
        radius = 300.0f;
    }

void Enemy::draw(){
    // DrawCircle(posX, posY, radius, color);
    Rectangle src = {(float)width * tilePosition, 0, (float)width, (float)height}; // BAGIAN TILESET YG INGIN DI GAMBAR
    Rectangle dst = {(float)posX, (float)posY, (float)width * scale, (float)height * scale}; // AREA TUJUAN DI LAYAR
    Vector2 origin = { 0, 0 };
    DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
    // DrawCircle(posX + scaleWidth / 2, posY + scaleHeight / 2, radius, SKYBLUE);
}

void Enemy::attack(Entity& player){
    time += GetFrameTime();
    std::cout << "time: " << time << "\n";
    if(time >= delay){
        if(CheckCollisionCircleRec(
            Vector2{(float)posX + scaleWidth / 2, (float)posY + scaleHeight / 2}, radius,
            Rectangle{(float)player.getPosX() + player.getScaleWidth() / 2, (float)player.getPosY() + player.getScaleHeight() / 2, (float)player.getWidth(), (float)player.getHeight()}))
        {
            address_of_bullets->emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
            time = 0.0f;
        }
    }
    if(time > 2){
        std::cout << "ULTI!!!\n";
        address_of_bullets->emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
        address_of_bullets->emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
        address_of_bullets->emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
        address_of_bullets->emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
        address_of_bullets->emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
        address_of_bullets->emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
        time = 0.0f;
    }
}

void Enemy::update(Entity& player){
    // gerak random y
    // if(time <= 1.0f){
    //     posY += speedY * GetFrameTime();
    // }
    // else {
    //     posY -= speedY * GetFrameTime();
    // }
    // cek apakah ada player dalam radius 300

    if(CheckCollisionCircleRec(
            Vector2{(float)posX + scaleWidth / 2, (float)posY + scaleHeight / 2}, radius,
            Rectangle{(float)player.getPosX() + player.getScaleWidth() / 2, (float)player.getPosY() + player.getScaleHeight() / 2, (float)player.getWidth(), (float)player.getHeight()}))
    {

        if(posX + width / 2 > player.getPosX() + player.getWidth() / 2 + 2){
            posX -= speedX;
        }
        else if(posX + width / 2 < player.getPosX() + player.getWidth() / 2 - 2){
            posX += speedX;
        }
        else {
            std::cout << "diam\n";
            posX = posX;
        }
    }

    // cek apakah ada peluru dalam radius 100, jika ada menghindar
    for(Bullet& bullet: *address_of_bullets){
        if(CheckCollisionCircles(
                Vector2{(float)posX + scaleWidth / 2, (float)posY + scaleHeight / 2}, 100,
                Vector2{(float)bullet.getPosX() + bullet.getRadius() / 2, (float)bullet.getPosY() + bullet.getRadius() / 2}, (float)bullet.getRadius()))
        {
            std::cout << "i\n";
            if(posX + scaleWidth / 2 > bullet.getPosX() + bullet.getRadius() / 2){ // jika posisi peluru di kiri
                // if(posX + speedX >= GetScreenWidth()) std::cout << "struck";
                posX += speedX;
            }
            else {
                // if(posX - speedX <= 0) posX += speedX * 2;
                posX += -speedX;
            }
        }
    }


    // DrawCircle(posX + scaleWidth / 2, posY + scaleHeight / 2, 100, LIGHTGRAY);

    // cek border
    if(posX < 0) posX = 0;
    else if(posX + scaleWidth > GetScreenWidth()) posX = GetScreenWidth() - scaleWidth;
    
    if(posY < 0) posY = 0;
    else if(posY + scaleHeight > GetScreenHeight()) posY = GetScreenHeight() - scaleHeight;

    // render peluru
    for(Bullet& bullet: *address_of_bullets){
        bullet.update(*this, *address_of_bullets);
        bullet.draw();
    }
}

void Enemy::set_bullets(std::vector<Bullet>& bullets){
    address_of_bullets = &bullets;
}