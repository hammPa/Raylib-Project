#include "Assets.hpp"


Assets::Assets(){
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

void Assets::drawBackground(){
    float tileSize = 64.0f;
    for(int i = 0; i < 9; i++){ // background
        for(int j= 0; j < 12; j++){
            DrawTexturePro(backgroundTexture, {0, 0, tileSize, tileSize}, {i * tileSize, j * tileSize, tileSize * 2, tileSize * 2}, {0, 0}, 0.0f, WHITE);
        }
    }
}

void Assets::drawFloor(){
    float tileSize = 64.0f;
    DrawTexturePro(floorTexture, {0, 0, tileSize, tileSize}, {0 , GetScreenHeight() - (tileSize * 1.2f), (float)GetScreenWidth(), tileSize * 1.2f}, {0, 0}, 0.0f, WHITE);
}

void Assets::drawBuilding(){
    float tileSize = 64.0f;
    for(int i = 0; i < 4; i++){ // background
        DrawTexturePro(buildingTexture, {0, 0, tileSize, tileSize}, {i * tileSize * 2, GetScreenHeight() - (tileSize * 4) - (tileSize * 1.2f), tileSize * 4, tileSize * 4}, {0, 0}, 0.0f, WHITE);
    }
}

void Assets::drawHpBar(Player& player){
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

Texture2D Assets::getBuildingTexture(){ return buildingTexture; }
Texture2D Assets::getHpTexture(){ return hpTexture; }
Texture2D Assets::getBackgroundTexture(){ return backgroundTexture; }
Texture2D Assets::getFloorTexture(){ return floorTexture; }