#include "game.h"

Game::Game() : gundam(&gameMap) {}  // Truyền con trỏ &gameMap vào gundam

void Game::init() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        SDL_Log("Lỗi khi khởi tạo SDL: %s", SDL_GetError());
        return;
    }

    graphics.init();

    menu.init(graphics);
    startTime = SDL_GetTicks();



    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("Lỗi khi khởi tạo SDL_mixer: %s", Mix_GetError());
    }

    gameAudio.loadMusic("backgroundmusic.mp3");
    gameAudio.playMusic();


     if (TTF_Init() == -1) {
        SDL_Log("Lỗi khi khởi tạo SDL_ttf: %s", TTF_GetError());
        return;
    }

    gameText.loadFont("font.ttf", 24);


    background = graphics.loadTexture("img\\background.png");
    gameMap.loadMap(graphics);
    gameMap.loadFromFile("Map.txt");


    winTexture = graphics.loadTexture("img/win_menu.png");
    loseTexture = graphics.loadTexture("img/lose_menu.png");


    SDL_Texture* gundamTexture = graphics.loadTexture("img\\gundam.png");
    gundam.init(gundamTexture, GUNDAM_FRAMES, GUNDAM_CLIPS);

    SDL_Texture* gateTexture = graphics.loadTexture("img\\COIN.png");
    gate.init(gateTexture, GATE_FRAMES, GATE_CLIPS);
}


void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) quit = true;

        const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);

        gundam.stopHorizontal();

         if (isWin && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            state = MENU; // Quay lại menu
        }

         if (isLose && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            state = MENU; // Cũng quay lại menu
        }


        if (currentKeyState[SDL_SCANCODE_LEFT] || currentKeyState[SDL_SCANCODE_A]) {
            gundam.vx = -gundam.moveSpeed;
            gundam.facingleft = true;
        }
        if (currentKeyState[SDL_SCANCODE_RIGHT] || currentKeyState[SDL_SCANCODE_D]) {
            gundam.vx = gundam.moveSpeed;
            gundam.facingleft = false;
        }

        if (currentKeyState[SDL_SCANCODE_UP] || currentKeyState[SDL_SCANCODE_W]) {
            gundam.jump();
        }

    }
}


int Game::getRemainingTime() const {
    Uint32 now = SDL_GetTicks();
    Uint32 elapsed = (now - startTime) / 1000;
    return std::max(0, GAME_DURATION - static_cast<int>(elapsed));
}

void Game::renderTimer() {
    int remaining = getRemainingTime();
    std::string text = "Time: " + std::to_string(remaining);

    SDL_Color white = {255, 255, 255, 255};
    gameText.render(graphics, text.c_str(), 96, 10, white);
}





void Game::update() {
    gundam.update();
    
    if (isWin || isLose) return;

    // Cuộn background
    bgOffsetX -= BG_SCROLL_SPEED;
    if (bgOffsetX <= -SCREEN_WIDTH) {
        bgOffsetX = 0;
    }


    SDL_Rect gundamBox = gundam.getBoundingBox();

    if (graphics.isContact(gundamBox, gate.getBoundingBox())) {
         isWin = true;
    }

    if (gundam.lifeCount == 0 || getRemainingTime() == 0) {
        isLose = true;
    }

    gate.tick();
}

void Game::resetGame() {
    isWin = false;  // Đặt lại trạng thái mặc định
    isLose = false;
    gundam.lifeCount = 3;
    gundam.x = gundam.startX;
    gundam.y = gundam.startY;
    startTime = SDL_GetTicks(); // Reset thời gian chơi
}



void Game::render() {
    graphics.prepareScene();


    // Vẽ background cuộn
    SDL_Rect bgRect1 = { bgOffsetX, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_Rect bgRect2 = { bgOffsetX + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_RenderCopy(graphics.getRenderer(), background, nullptr, &bgRect1);
    SDL_RenderCopy(graphics.getRenderer(), background, nullptr, &bgRect2);


    gameMap.render(graphics);


    renderTimer();


    graphics.render(gundam.x, gundam.y, gundam);
    if (!isWin) graphics.render(gate.x, gate.y, gate);

    if (isWin) {
       SDL_RenderCopy(graphics.getRenderer(), winTexture, NULL, NULL);
    }

    if (isLose) {
       SDL_RenderCopy(graphics.getRenderer(), loseTexture, NULL, NULL);
    }


    if (!isWin && !isLose) {
        SDL_Color white = {255, 255, 255, 255};
        std::string lifeText = "x" + std::to_string(gundam.lifeCount);
        gameText.render(graphics, lifeText.c_str(), SCREEN_WIDTH - 300, 10, white);
    }


    graphics.presentScene();
}


void Game::run() {
    init();
    Uint32 frameStart;
    const int frameDelay = 1000 / 30;

    while (!quit) {
        frameStart = SDL_GetTicks();

        if (state == MENU) {
            // Xử lý sự kiện menu
            if (menu.handleEvents(gameAudio)) {
                resetGame();
                state = GAME;
            }



            menu.render(graphics);
        } else if (state == GAME) {
            handleEvents();
            update();
            render();
        }

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

