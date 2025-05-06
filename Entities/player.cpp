#include "player.h"


Player::Player(Map* _map) : map(_map) {}

void Player::init(SDL_Texture* _texture, int frames, const int _clips[][4]) {
    texture = _texture;
    SDL_Rect clip;
    for (int i = 0; i < frames; i++) {
        clip.x = _clips[i][0];
        clip.y = _clips[i][1];
        clip.w = _clips[i][2];
        clip.h = _clips[i][3];
        clips.push_back(clip);
    }
}


void Player::jump() {
    if (onGround) {
        vy = jumpStrength;
        onGround = false;
        isJumping = true;
    }
}

void Player::stopHorizontal() {
    vx = 0;
}

void Player::update() {
    // Apply gravity
    vy += gravity;
    if (vy > maxFallSpeed) vy = maxFallSpeed;


    int hitbox_w = clips[0].w - 24;
    int hitbox_h = clips[0].h - 14;

    int newX = x + vx;
    if (!map->isBlocked(newX, y, hitbox_w, hitbox_h)) {
        x = newX;
    }


    int newY = y + vy;
    if (!map->isBlocked(x, newY, hitbox_w, hitbox_h)) {
        y = newY;
        onGround = false;

        if ((y + 50) >= SCREEN_HEIGHT) {
        x = startX;
        y = startY;
        vx = 0;
        vy = 0;
        isJumping = false;
        onGround = false;

        if (lifeCount > 0) {
            lifeCount--;
        }
    }

    } else {
        // Chạm đất nè
        if (vy > 0) onGround = true;
        vy = 0;
    }


    // Cập nhật animation
    currentFrame = (currentFrame + 1) % clips.size();
}


const SDL_Rect* Player::getCurrentClip() const {
    return &(clips[currentFrame]);
}

SDL_Rect Player::getBoundingBox() const {
    return {x - 4, y - 4, clips[0].w - 16, clips[0].h - 16}; // Em trừ mấy con số để sát nhân vật do sai lệch khi vẽ
}
