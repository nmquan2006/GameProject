#ifndef ITEM_H
#define ITEM_H

#include "../defs.h"

struct Gate {
    int x = 990, y = 0;
    int width = 0, height=0;


    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips [][4]);

    void tick();

    const SDL_Rect* getCurrentClip() const;

     SDL_Rect getBoundingBox() const {
        return {x, y, width, height};
    }

};


#endif // ITEM_H
