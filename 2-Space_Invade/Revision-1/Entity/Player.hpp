#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "../Bullet/Bullet.hpp"

class Player: public Entity {
private:
    float scale = 3.0f;
    int tilePosition = 4;
    std::vector<Bullet> *address_of_bullets;

public:
    Player(int x, int y, int sx, int sy, int w, int h, Texture2D t, int d, int hp);

    void draw() override;

    void attack(Entity& enemy) override;

    void update(Entity& enemy) override;

    void set_bullets(std::vector<Bullet>& bullets);
};

#endif