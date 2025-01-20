#include <raylib.h>
#include "Ball.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

int playerScore = 0;
int enemyScore = 0;

Ball ball(GetScreenWidth() / 2, GetScreenHeight() / 2, 20, 7, 7, WHITE);
Player player(30, 120, 0, 0, 7, WHITE);
Enemy enemy(30, 120, 0, 0, 7, GRAY);

int main() {
    const int window_width = 800;
    const int window_height = 600;

    InitWindow(window_width, window_height, "Pong Game");

    const int fps = 60;
    SetTargetFPS(fps);

    player.setPosX(0);
    player.setPosY((GetScreenHeight() / 2) - (player.getHeight() / 2));
    enemy.setPosX(GetScreenWidth() - enemy.getWidth() - 10);
    enemy.setPosY((GetScreenHeight() / 2) - (enemy.getHeight() / 2));

    while (!WindowShouldClose()) {
        BeginDrawing();

        // Pembaruan objek
        DrawText(TextFormat("Player: %d", playerScore), window_width / 4, 30, 20, BLACK);
        DrawText(TextFormat("Enemy: %d", enemyScore), window_width - window_width / 4 - 100, 30, 20, BLACK);
        ball.update(playerScore, enemyScore);
        player.update(ball.getPosY());
        enemy.update(ball.getPosY());

        // Cek tabrakan bola dengan pemain
        if (CheckCollisionCircleRec(Vector2{(float)ball.getPosX(), (float)ball.getPosY()}, ball.getRadius(),
                                    Rectangle{(float)player.getPosX(), (float)player.getPosY(), (float)player.getWidth(), (float)player.getHeight()})) {
            ball.setSpeedX(ball.getspeedX() * -1);
        }

        // Cek tabrakan bola dengan musuh
        if (CheckCollisionCircleRec(Vector2{(float)ball.getPosX(), (float)ball.getPosY()}, ball.getRadius(),
                                    Rectangle{(float)enemy.getPosX(), (float)enemy.getPosY(), (float)enemy.getWidth(), (float)enemy.getHeight()})) {
            ball.setSpeedX(ball.getspeedX() * -1);
        }

        ClearBackground(SKYBLUE);

        // Gambar objek
        ball.draw();
        player.draw();
        enemy.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
