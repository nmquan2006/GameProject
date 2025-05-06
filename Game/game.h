#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "player.h"
#include "item.h"
#include "Text.h"
#include "audio.h"
#include "menu.h"

class Game {
public:
    Game();

    void run();
    void init();
    void handleEvents();


    void update();
    void render();

    int getRemainingTime() const;
    void renderTimer();

    void resetGame();


private:

    Graphics graphics;
    Map gameMap;
    SDL_Texture* background;
    int bgOffsetX = 0;  // Vị trí background bắt đầu vẽ
    const int BG_SCROLL_SPEED = 1;


    Player gundam;
    Gate gate;

    Text gameText;
    Audio gameAudio;

    bool quit = false;
    bool isWin = false;
    bool isLose = false;

    Menu menu;
    enum GameState { MENU, GAME };
    GameState state = MENU;

    SDL_Texture* winTexture = nullptr;
    SDL_Texture* loseTexture = nullptr;


    Uint32 startTime;
    const int GAME_DURATION = 120;


};

#endif // GAME_H
