#include "menu.h"

Menu::Menu() : main_menu(nullptr) {}

Menu::~Menu() {
    if (main_menu) SDL_DestroyTexture(main_menu);
    if (highlight_Play) SDL_DestroyTexture(highlight_Play);
    if (highlight_Sound) SDL_DestroyTexture(highlight_Sound);
    if (highlight_Mute) SDL_DestroyTexture(highlight_Mute);
}

void Menu::init(Graphics& graphics) {

    main_menu = graphics.loadTexture("img/main_menu.png");
    highlight_Play = graphics.loadTexture("img/2lightplay.png");
    highlight_Sound = graphics.loadTexture("img/2lightsound.png");
    highlight_Mute = graphics.loadTexture("img/2lightmute.png");


    // Toa độ các nút
    playButton = { 520, 295, 335, 70 };
    soundButton = { 795, 498, 31, 47 };
    muteButton = { 893, 496, 35, 52 };

}

void Menu::render(Graphics& graphics) {
    graphics.prepareScene();

    // Highlight thì đổi ảnh
    if (isPlayHighlight && highlight_Play) {
        graphics.render(0, 0, highlight_Play);
    } else if (isSoundHighlight && highlight_Sound) {
        graphics.render(0, 0, highlight_Sound);
    } else if (isMuteHighlight && highlight_Mute) {
        graphics.render(0, 0, highlight_Mute);
    } else if (main_menu) {
        graphics.render(0, 0, main_menu);
    }


    graphics.presentScene();
}


bool Menu::handleEvents(Audio& audio) {
    SDL_Event e;


    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Point mousePos = { mouseX, mouseY };


    // Reset trạng thái highlight mỗi frame
    isPlayHighlight = SDL_PointInRect(&mousePos, &playButton);
    isSoundHighlight = SDL_PointInRect(&mousePos, &soundButton);
    isMuteHighlight = SDL_PointInRect(&mousePos, &muteButton);

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return false;
        }

        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            int clickX = e.button.x;
            int clickY = e.button.y;
            SDL_Point clickPoint = { clickX, clickY };

            if (SDL_PointInRect(&clickPoint, &playButton)) {
                SDL_Log("Click nút PLAY");
                return true;
            }

            if (SDL_PointInRect(&clickPoint, &muteButton)) {
                audio.stopMusic();
                SDL_Log("Mute âm thanh");
            }

            if (SDL_PointInRect(&clickPoint, &soundButton)) {
                audio.playMusic();
                SDL_Log("Bật âm thanh");
            }
        }
    }

    return false;
}


