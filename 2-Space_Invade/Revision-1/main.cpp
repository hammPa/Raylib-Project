#include <raylib.h>
#include "Entity/Entity.hpp"
#include "Bullet/Bullet.hpp"
#include "Entity/Player.hpp"
#include "Entity/Enemy.hpp"
#include "Assets/Assets.hpp"


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

    std::vector<Bullet> bullets;
    player.set_bullets(bullets);
    enemy.set_bullets(bullets);

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
