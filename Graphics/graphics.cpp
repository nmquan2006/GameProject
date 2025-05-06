
#include "graphics.h"
#include "player.h"
#include "item.h"

void Graphics::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
        logErrorAndExit("CreateWindow", SDL_GetError());


    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Graphics::prepareScene(SDL_Texture * background )
{
    SDL_RenderClear(renderer);
    if(background!=nullptr)
        SDL_RenderCopy( renderer, background, NULL, NULL);
}

void Graphics::presentScene()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::loadTexture(const char *filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(renderer, texture, src, &dest);
}

void Graphics::quit()
{
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Graphics::render(int x, int y, const Player& gundam){
     const SDL_Rect clip = {
        GUNDAM_CLIPS[gundam.currentFrame][0],
        GUNDAM_CLIPS[gundam.currentFrame][1],
        GUNDAM_CLIPS[gundam.currentFrame][2],
        GUNDAM_CLIPS[gundam.currentFrame][3]
    };
    SDL_Rect renderQuad = {x, y, (clip.w), (clip.h)};
     // Nếu facingLeft == true, lật ảnh theo chiều ngang
    SDL_RendererFlip flipType = gundam.facingleft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    SDL_RenderCopyEx(renderer, gundam.texture, &clip, &renderQuad, 0, nullptr,flipType);

}

void Graphics::render(int x, int y, const Gate& gate){
     const SDL_Rect clip = {
        GATE_CLIPS[gate.currentFrame][0],
        GATE_CLIPS[gate.currentFrame][1],
        GATE_CLIPS[gate.currentFrame][2],
        GATE_CLIPS[gate.currentFrame][3]
    };

    SDL_Rect renderQuad = {x, y, (clip.w), (clip.h)};



    SDL_RenderCopy(renderer, gate.texture, &clip, &renderQuad);
}

void Graphics::render(int x, int y, SDL_Texture* texture) {
    if (!texture) return;  // Kiểm tra nếu texture hợp lệ

    SDL_Rect dest = {x, y, SCREEN_WIDTH, SCREEN_HEIGHT};  // Hình nền toàn màn hình
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}


bool Graphics::isContact(SDL_Rect r1, SDL_Rect r2) {
    return r1.x + 20< r2.x + r2.w &&
           r1.x + r1.w > r2.x &&
           r1.y + 20 < r2.y + r2.h &&
           r1.y + r1.h > r2.y;
}



