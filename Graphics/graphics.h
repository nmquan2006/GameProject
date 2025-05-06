#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include "../defs.h"
struct Gate;
struct Player;

class Graphics {
public:

    SDL_Texture *loadTexture(const char *filename);

	void logErrorAndExit(const char* msg, const char* error);
	void init();
	void prepareScene(SDL_Texture * background = nullptr);
    void presentScene();
    void renderTexture(SDL_Texture *texture, int x, int y);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
    void quit();
    void render(int x, int y, const Player& gundam);
    void render(int x, int y, const Gate& gate);
    void render(int x, int y, SDL_Texture* texture);

    bool isContact (SDL_Rect rect1, SDL_Rect rect2);

    SDL_Renderer* getRenderer() { return renderer; }



private:
    SDL_Renderer *renderer;
	SDL_Window *window;
};


#endif // _GRAPHICS__H
