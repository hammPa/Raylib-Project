#include "Player.hpp"

Player::Player(int x, int y, int sx, int sy, int w, int h, Texture2D t, int d, int hp)
    : Entity(x, y, sx, sy, w, h,  t, d, hp) {
        scaleWidth = width * scale;
        scaleHeight = height * scale;
    }

void Player::draw(){
    // DrawCircle(posX, posY, radius, color);
    Rectangle src = {(float)width * tilePosition, 0, (float)width, (float)height}; // BAGIAN TILESET YG INGIN DI GAMBAR
    Rectangle dst = {(float)posX, (float)posY, (float)width * scale, (float)height * scale}; // AREA TUJUAN DI LAYAR
    Vector2 origin = { 0, 0 };
    DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
}

void Player::attack(Entity& enemy){
    if(IsKeyPressed(KEY_SPACE)){
        address_of_bullets->emplace_back(Bullet(posX + (scaleWidth / 2), posY - 20, damage, 5, -7, RED, this));
    }
}

void Player::update(Entity& enemy){
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
        posX -= speedX;
    }
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
        posX += speedX;
    }
    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
        posY -= speedY;
    }
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        posY += speedY;
    }

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

void Player::set_bullets(std::vector<Bullet>& bullets){
    address_of_bullets = &bullets;
}