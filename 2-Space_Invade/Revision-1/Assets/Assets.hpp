#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <raylib.h>
#include "../Entity/Entity.hpp"
#include "../Entity/Player.hpp"

class Assets {
private:
    Texture2D hpTexture;
    Texture2D buildingTexture;
    Texture2D backgroundTexture;
    Texture2D floorTexture;
public:
    Assets();

    void drawBackground();

    void drawFloor();

    void drawBuilding();

    void drawHpBar(Player& player);

    Texture2D getBuildingTexture();
    Texture2D getHpTexture();
    Texture2D getBackgroundTexture();
    Texture2D getFloorTexture();
};

#endif