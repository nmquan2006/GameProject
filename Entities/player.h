#ifndef PLAYER_H
#define PLAYER_H

#include "../defs.h"
#include "map.h"

struct Player {
    Map* map; // Con trỏ đến bản đồ

    Player(Map* _map);

    int x = 24, y = 524;
    int startX = 24, startY = 524;

    int vx = 0, vy = 0;
    bool onGround = false;
    bool isJumping = false;

    const int gravity = 2;
    const int jumpStrength = -18;
    const int maxFallSpeed = 12;
    const int moveSpeed = 5;

    bool facingleft = false;

    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips[][4]);


    void jump();
    void update();
    void stopHorizontal();

    const SDL_Rect* getCurrentClip() const;
    SDL_Rect getBoundingBox() const;

    int lifeCount = 3;
};

#endif // PLAYER_H
