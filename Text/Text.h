#ifndef TEXT_H
#define TEXT_H

#include "../defs.h"

class Graphics;

class Text {
public:
    Text();
    ~Text();

    bool loadFont(const char* fontPath, int fontSize);
    void render(Graphics& graphics, const char* message, int x, int y, SDL_Color color);
    void quit();

private:
    TTF_Font* font;
};

#endif // TEXT_H
