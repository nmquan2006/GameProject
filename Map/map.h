#ifndef MAP_H
#define MAP_H

#include "../defs.h"
#include <vector>
#include <unordered_map>
#include <string>
class Graphics;

class Map {
public:
    Map();
    ~Map();

    void loadMap(Graphics& graphics);
    void render(Graphics& graphics);
    void loadFromFile(const std::string& filename);
    SDL_Rect getTileBoundingBox(int tileX, int tileY) const;


    // Kiểm tra va chạm
    bool isBlocked(int x, int y,int w, int h);
    bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return !(a.x + a.w <= b.x ||
             a.x >= b.x + b.w ||
             a.y + a.h <= b.y ||
             a.y >= b.y + b.h);
}

private:
    static const int TILE_SIZE = 32;
    static const int MAP_WIDTH = 32;
    static const int MAP_HEIGHT = 19;

    std::vector<std::vector<int>> tileMap;
    std::unordered_map<int, SDL_Texture*> tileTextures;

    void loadTileTextures(Graphics& graphics);
};

#endif // MAP_H
