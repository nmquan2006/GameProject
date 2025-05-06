#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "graphics.h"
#include "audio.h"

class Menu {
public:
    Menu();
    ~Menu();

    void init(Graphics& graphics);
    void render(Graphics& graphics);
    bool handleEvents(Audio& audio); // Kiểm tra nếu nút được click

private:
    SDL_Texture* main_menu;
    SDL_Texture* highlight_Play = nullptr;
    SDL_Texture* highlight_Sound = nullptr;
    SDL_Texture* highlight_Mute = nullptr;

    bool isPlayHighlight = false;
    bool isSoundHighlight = false;
    bool isMuteHighlight = false;


    SDL_Rect playButton;
    SDL_Rect soundButton;
    SDL_Rect muteButton;

};

#endif // MENU_H
