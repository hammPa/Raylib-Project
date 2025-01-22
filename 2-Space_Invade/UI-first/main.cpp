#include <raylib.h>
#include <vector>
#include <algorithm>
#include <iostream>

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
    Entity(int x, int y, int sx, int sy, int w, int h, Texture2D t, int d, int hp)
        : posX(x), posY(y), speedX(sx), speedY(sy), width(w), height(h), texture(t), damage(d), healthPoint(hp) {}

    int getPosX(){ return posX; }
    int getPosY(){ return posY; }
    int getSpeedX(){ return speedX; }
    int getSpeedY(){ return speedY; }
    int getWidth(){ return width; }
    int getHeight(){ return height; }    
    Texture2D getTexture(){ return texture; }
    int getHp(){ return healthPoint; }

    int getScaleWidth(){ return scaleWidth; }
    int getScaleHeight(){ return scaleHeight; }

    void setPosX(int newValue){ posX = newValue; }
    void setPosY(int newValue){ posY = newValue; }
    void setSpeedX(int newValue){ speedX = newValue; }
    void setSpeedY(int newValue){ speedY = newValue; }
    void setWidth(int newValue){ width = newValue; }
    void setHeight(int newValue){ height = newValue; }
    void setTexture(Texture newValue){ texture = newValue; }
    void setHp(int newValue){ healthPoint = newValue; }

    void takeDamage(int bulletDamage){ healthPoint -= bulletDamage; }

    virtual void draw() = 0;
    virtual void update(Entity& target) = 0;
    virtual void attack(Entity& entity) = 0;
};

class Bullet {
private:
    int posX;
    int posY;
    int damage;
    float radius;
    int speedY;
    Color color;
    Entity *owner;
public:
    Bullet(int x, int y, int d, float r, int sy, Color c, Entity* o)
        : posX(x), posY(y), damage(d), radius(r), speedY(sy), color(c), owner(o) {}

    int getPosX(){ return posX; }
    int getPosY(){ return posY; }
    int getDamage(){ return damage; }
    float getRadius(){ return radius; }
    int getSpeedY(){ return speedY; }
    Color getColor(){ return color; }

    void setPosX(int newValue){ posX = newValue; }
    void setPosY(int newValue){ posY = newValue; }
    void setDamage(int newValue){ damage = newValue; }
    void setRadius(float newValue){ radius = newValue; }
    void setSpeedY(int newValue){ speedY = newValue; }
    void setColor(Color newValue){ color = newValue; }

    bool operator==(const Bullet& other) const { // untuk std::find
        return posX == other.posX &&
               posY == other.posY &&
               damage == other.damage &&
               radius == other.radius &&
               speedY == other.speedY &&
               color.r == other.color.r && color.g == other.color.g &&
               color.b == other.color.b && color.a == other.color.a &&
               owner == other.owner;  // assuming owner comparison is valid
    }

    void draw(){
        DrawCircle(posX, posY, radius, color);
    }

    void update(Entity& entity, std::vector<Bullet>& bullets){
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
        std::cout << bullets.size() << "\n";
    }
};

std::vector<Bullet> bullets;

class Player: public Entity {
private:
    float scale = 3.0f;
    int tilePosition = 4;
public:
    Player(int x, int y, int sx, int sy, int w, int h, Texture2D t, int d, int hp)
        : Entity(x, y, sx, sy, w, h,  t, d, hp) {
            scaleWidth = width * scale;
            scaleHeight = height * scale;
        }

    void draw() override {
        // DrawCircle(posX, posY, radius, color);
        Rectangle src = {(float)width * tilePosition, 0, (float)width, (float)height}; // BAGIAN TILESET YG INGIN DI GAMBAR

        Rectangle dst = {(float)posX, (float)posY, (float)width * scale, (float)height * scale}; // AREA TUJUAN DI LAYAR
        Vector2 origin = { 0, 0 };
        DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
    }

    void attack(Entity& enemy) override {
        if(IsKeyPressed(KEY_SPACE)){
            bullets.emplace_back(Bullet(posX + (scaleWidth / 2), posY - 20, damage, 5, -7, RED, this));
        }
    }

    void update(Entity& enemy) override {
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
        for(Bullet& bullet: bullets){
            bullet.update(*this, bullets);
            bullet.draw();
        }
    }
};

class Enemy: public Entity {
private:
    float delay;
    float time;
    int tilePosition = 0;
    float scale = 3.0f;
    float radius;
public:
    Enemy(int x, int y, int sx, int sy, int w, int h, Texture2D t, int d, int hp)
        : Entity(x, y, sx, sy, w, h, t, d, hp), delay(1), time(0) {
            scaleWidth = width * scale;
            scaleHeight = height * scale;
            radius = 300.0f;
        }

    void draw() override {
        // DrawCircle(posX, posY, radius, color);
        Rectangle src = {(float)width * tilePosition, 0, (float)width, (float)height}; // BAGIAN TILESET YG INGIN DI GAMBAR
        Rectangle dst = {(float)posX, (float)posY, (float)width * scale, (float)height * scale}; // AREA TUJUAN DI LAYAR
        Vector2 origin = { 0, 0 };
        DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
        // DrawCircle(posX + scaleWidth / 2, posY + scaleHeight / 2, radius, SKYBLUE);
    }

    void attack(Entity& player) override {
        time += GetFrameTime();
        std::cout << "time: " << time << "\n";
        if(time >= delay){
            if(CheckCollisionCircleRec(
                Vector2{(float)posX + scaleWidth / 2, (float)posY + scaleHeight / 2}, radius,
                Rectangle{(float)player.getPosX() + player.getScaleWidth() / 2, (float)player.getPosY() + player.getScaleHeight() / 2, (float)player.getWidth(), (float)player.getHeight()}))
            {
                bullets.emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
                time = 0.0f;
            }
        }
        if(time > 2){
            std::cout << "ULTI!!!\n";
            bullets.emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
            bullets.emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
            bullets.emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
            bullets.emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
            bullets.emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
            bullets.emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
            time = 0.0f;
        }
    }

    void update(Entity& player) override {
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
        for(Bullet& bullet: bullets){
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
        for(Bullet& bullet: bullets){
            bullet.update(*this, bullets);
            bullet.draw();
        }
    }
};

class Assets {
private:
Texture2D hpTexture;
Texture2D buildingTexture;
Texture2D backgroundTexture;
Texture2D floorTexture;
public:
    Assets(){
        Texture2D tileImage = LoadTexture("./assets/SpaceInvaders.png");

        // // Load and set window icon
        Image icon = LoadImage("./assets/GameIcon.png");
        SetWindowIcon(icon);
        UnloadImage(icon);  // Unload icon image after setting it

        // // Load hp image
        Image hpImage = LoadImage("./assets/SpaceInvaders_Health.png");
        hpTexture = LoadTextureFromImage(hpImage);
        UnloadImage(hpImage);  // Unload image from RAM, as we now have a texture


        Image buildingImage = LoadImage("./assets/SpaceInvaders_BackgroundBuildings.png");
        buildingTexture = LoadTextureFromImage(buildingImage);
        UnloadImage(buildingImage);

        Image backgroundImage = LoadImage("./assets/SpaceInvaders_Background.png");
        backgroundTexture = LoadTextureFromImage(backgroundImage);
        UnloadImage(backgroundImage);

        Image floorImage = LoadImage("./assets/SpaceInvaders_BackgroundFloor.png");
        floorTexture = LoadTextureFromImage(floorImage);
        UnloadImage(floorImage);
    }

    void drawBackground(){
        float tileSize = 64.0f;
        for(int i = 0; i < 9; i++){ // background
            for(int j= 0; j < 12; j++){
                DrawTexturePro(backgroundTexture, {0, 0, tileSize, tileSize}, {i * tileSize, j * tileSize, tileSize * 2, tileSize * 2}, {0, 0}, 0.0f, WHITE);
            }
        }
    }

    void drawFloor(){
        float tileSize = 64.0f;
        DrawTexturePro(floorTexture, {0, 0, tileSize, tileSize}, {0 , GetScreenHeight() - (tileSize * 1.2f), (float)GetScreenWidth(), tileSize * 1.2f}, {0, 0}, 0.0f, WHITE);
    }

    void drawBuilding(){
        float tileSize = 64.0f;
        for(int i = 0; i < 4; i++){ // background
            DrawTexturePro(buildingTexture, {0, 0, tileSize, tileSize}, {i * tileSize * 2, GetScreenHeight() - (tileSize * 4) - (tileSize * 1.2f), tileSize * 4, tileSize * 4}, {0, 0}, 0.0f, WHITE);
        }
    }

    void drawHpBar(Player& player){
        int scale = 4;
        float widthSize = 32.0f;
        float heightSize = 16.0f;
        int tilePos;
        if(player.getHp() >= 81) tilePos = 0;
        else if(player.getHp() >= 61) tilePos = 1;
        else if(player.getHp() >= 41) tilePos = 2;
        else if(player.getHp() >= 21) tilePos = 3;
        else if(player.getHp() >= 1) tilePos = 3;
        else tilePos = 5;
        DrawTexturePro(hpTexture, Rectangle{0, tilePos * (GetScreenHeight() - heightSize), widthSize, heightSize}, Rectangle{0, GetScreenHeight() - heightSize * scale, widthSize * scale, heightSize * scale}, {0, 0}, 0.0f, WHITE);
        DrawText(TextFormat("%i", player.getHp()), (widthSize * scale) + 10, GetScreenHeight() - (heightSize * scale / 2) - 10, 20, WHITE);
    }

    Texture2D getBuildingTexture(){ return buildingTexture; }
    Texture2D getHpTexture(){ return hpTexture; }
    Texture2D getBackgroundTexture(){ return backgroundTexture; }
    Texture2D getFloorTexture(){ return floorTexture; }
};


int main() {
    const int screenWidth = 600;
    const int screenHeight = 800;
    const int health_point = 100;
    
    InitWindow(screenWidth, screenHeight, "Space Invades");

    SetTargetFPS(60);


    int tileWidth = 16;
    int tileHeight = 16;
    Texture2D tileImage = LoadTexture("./assets/SpaceInvaders.png");
    Player player(GetScreenWidth() / 2, GetScreenHeight() - (GetScreenHeight() / 3), 7, 7, tileWidth, tileHeight, tileImage, 5, health_point);
    Enemy enemy(100, 200, 4, 4, tileWidth, tileHeight, tileImage, 5, health_point);
    Assets assets;

    while (!WindowShouldClose()) {
        BeginDrawing();

        // if(player.getHp() <= 0){
            
        // }
        assets.drawBackground();
        assets.drawFloor();
        assets.drawBuilding();

        enemy.update(player);
        enemy.attack(player);
        enemy.draw();

        player.update(enemy);
        player.attack(enemy);
        player.draw();


        assets.drawHpBar(player);
        DrawText(TextFormat("Enemy HP : %i", enemy.getHp()), 0, 0, 20, WHITE);


        EndDrawing();
    }

    // Clean up resources
    CloseWindow();

    return 0;
}
