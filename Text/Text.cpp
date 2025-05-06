#include "Text.h"
#include "graphics.h"

Text::Text() : font(nullptr) {}

Text::~Text() {
    quit();
}

bool Text::loadFont(const char* fontPath, int fontSize) {
    font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Không thể tải font: %s", TTF_GetError());
        return false;
    }
    return true;
}

void Text::render(Graphics& graphics, const char* message, int x, int y, SDL_Color color) {
    if (!font) return;

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, message, color);
    if (!textSurface) return;

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), textSurface);
    if (!textTexture) return;

    SDL_Rect destRect = {x, y, textSurface->w, textSurface->h};
    SDL_FreeSurface(textSurface);

    SDL_RenderCopy(graphics.getRenderer(), textTexture, nullptr, &destRect);
    SDL_DestroyTexture(textTexture);
}


void Text::quit() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}
