
#include "item.h"

void Gate::init(SDL_Texture* _texture, int frames, const int _clips [][4]){
       texture = _texture;
       SDL_Rect clip;
       for(int i = 0; i < frames;i++){
        clip.x = _clips[i][0];
        clip.y = _clips[i][1];
        clip.w = _clips[i][2];
        clip.h = _clips[i][3];

        clips.push_back(clip);
       }

       if (!clips.empty()) {
        width = clips[0].w;
        height = clips[0].h;
    }
}

void Gate:: tick(){
        currentFrame = (currentFrame + 1) % clips.size();
}


const SDL_Rect* Gate:: getCurrentClip() const{
        return &(clips[currentFrame]);
}
