#include <raylib.h>
#include <vector>
#include <algorithm>

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
    virtual void update() = 0;
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
        
        // if (CheckCollisionCircles(
        //         Vector2{(float)posX, (float)posY}, radius,
        //         Vector2{(float)entity.getPosX(), (float)entity.getPosY()}, entity.getRadius()
        // )) {
        //     if (&entity != owner) {  // Pastikan peluru tidak mengenai dirinya sendiri
        //         entity.takeDamage(damage);  // Berikan damage pada entity yang tertabrak
                
        //         std::vector<Bullet>::iterator it = std::find(bullets.begin(), bullets.end(), *this);  // Cari peluru di vektor
        //         if (it != bullets.end()) {
        //             bullets.erase(it);  // Hapus peluru dari vektor
        //         }
        //     }
        // }
        if (CheckCollisionCircleRec(
                Vector2{(float)posX, (float)posY}, radius,
                Rectangle{(float)entity.getPosX(), (float)entity.getPosY(), (float)entity.getWidth(), (float)entity.getHeight()}
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
};

std::vector<Bullet> bullets;

class Player: public Entity {
private:
    float scale = 3.0f;
    int tilePosition = 4;

    int scaleWidth = width * scale;
    int scaleHeight = height * scale;
public:
    Player(int x, int y, int sx, int sy, int w, int h, Texture2D t, int d, int hp)
        : Entity(x, y, sx, sy, w, h,  t, d, hp) {}

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

    void update() override {
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
    
    int scaleWidth = width * scale;
    int scaleHeight = height * scale;
public:
    Enemy(int x, int y, int sx, int sy, int w, int h, Texture2D t, int d, int hp)
        : Entity(x, y, sx, sy, w, h, t, d, hp), delay(1), time(0) {}

    void draw() override {
        // DrawCircle(posX, posY, radius, color);
        Rectangle src = {(float)width * tilePosition, 0, (float)width, (float)height}; // BAGIAN TILESET YG INGIN DI GAMBAR
        Rectangle dst = {(float)posX, (float)posY, (float)width * scale, (float)height * scale}; // AREA TUJUAN DI LAYAR
        Vector2 origin = { 0, 0 };
        DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
    }

    void attack(Entity& player) override {
        time += GetFrameTime();
        if(time >= delay){
            if(posX + 3 == player.getPosX()|| posX - 3 == player.getPosX()){
                bullets.emplace_back(Bullet(posX + (scaleWidth / 2), posY + 20, damage, 5, 7, BLUE, this));
                time = 0.0f;
            }
        }
    }

    void update() override {
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


int main() {
    const int screenWidth = 600;
    const int screenHeight = 800;
    const int health_point = 100;
    
    InitWindow(screenWidth, screenHeight, "Space Invades");

    int tileWidth = 16;
    int tileHeight = 16;
    Texture2D tileImage = LoadTexture("./assets/SpaceInvaders.png");
    Player player(GetScreenWidth() / 2, GetScreenHeight() - (GetScreenHeight() / 3), 7, 7, tileWidth, tileHeight, tileImage, 5, health_point);
    Enemy enemy(100, 200, 7, 7, tileWidth, tileHeight, tileImage, 5, health_point);


    // // Load and set window icon
    Image icon = LoadImage("./assets/GameIcon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);  // Unload icon image after setting it

    // // Load border image
    // Image borderImage = LoadImage("./assets/SpaceInvaders_Borders.png");
    // Texture2D borderTexture = LoadTextureFromImage(borderImage);
    // UnloadImage(borderImage);  // Unload image from RAM, as we now have a texture

    Image backgroundImage = LoadImage("./assets/SpaceInvaders_Background.png");
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);


    Image buildingImage = LoadImage("./assets/SpaceInvaders_BackgroundBuildings.png");
    Texture2D buildingTexture = LoadTextureFromImage(backgroundImage);
    UnloadImage(buildingImage);


    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        BeginDrawing();

        // if(enemy.getHp() <= 0){

        // }


        // if(player.getHp() <= 0){
            
        // }
        float tileSize = 64.0f;
        DrawTexturePro(backgroundTexture, {0, 0, 64, 64}, {0, 0, screenWidth, screenHeight}, {0, 0}, 0.0f, WHITE);
        DrawTexturePro(buildingTexture, {0, 0, tileSize, tileSize}, {0, screenHeight - (tileSize * 6), tileSize * 6, tileSize * 6}, {0, 0}, 0.0f, WHITE);
        DrawTexturePro(buildingTexture, {0, 0, tileSize, tileSize}, {screenWidth - (tileSize * 6), screenHeight - (tileSize * 6), tileSize * 6, tileSize * 6}, {0, 0}, 0.0f, WHITE);

        enemy.update();
        enemy.attack(player);

        player.update();
        player.attack(enemy);


        DrawText(TextFormat("Player HP: %i", player.getHp()), 0, screenHeight - 20, 20, WHITE);
        DrawText(TextFormat("Enemy HP : %i", enemy.getHp()), 0, 0, 20, WHITE);

        enemy.draw();
        player.draw();

        EndDrawing();
    }

    // Clean up resources
    // UnloadTexture(borderTexture);
    CloseWindow();

    return 0;
}