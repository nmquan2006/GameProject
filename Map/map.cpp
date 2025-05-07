#include "map.h"
#include "graphics.h"
#include <fstream>
#include <sstream>
#include <iostream>

Map::Map() : tileMap(MAP_HEIGHT, std::vector<int>(MAP_WIDTH, 0)) {}

Map::~Map() {
    for (auto& pair : tileTextures) {
        SDL_DestroyTexture(pair.second);
    }
}

void Map::loadMap(Graphics& graphics) {
    loadTileTextures(graphics);
    loadFromFile("Map.txt");
}

void Map::loadTileTextures(Graphics& graphics) {
    tileTextures[1] = graphics.loadTexture("img/ground.png");
}

void Map::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Lỗi: Không thể mở file map!" << std::endl;
        return;
    }

    std::string line;
    int row = 0;

    while (std::getline(file, line) && row < MAP_HEIGHT) {
        std::stringstream ss(line);
        std::string tile;
        int col = 0;

        while (std::getline(ss, tile, ',') && col < MAP_WIDTH) {
            tileMap[row][col] = std::stoi(tile);
            col++;
        }
        row++;
    }

    file.close();
}


void Map::render(Graphics& graphics) {
    for (int row = 0; row < MAP_HEIGHT; ++row) {
        for (int col = 0; col < MAP_WIDTH; ++col) {
            int tileID = tileMap[row][col];

            if (tileTextures.find(tileID) != tileTextures.end()) {
                SDL_Texture* texture = tileTextures[tileID];

                SDL_Rect srcRect = {0, 0, TILE_SIZE, TILE_SIZE};
                SDL_Rect destRect = {col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                graphics.blitRect(texture, &srcRect, destRect.x, destRect.y);
            }
        }
    }
}


SDL_Rect Map::getTileBoundingBox(int tileX, int tileY) const {
    return { tileX * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE };
}


bool Map::isBlocked(int x, int y, int w, int h) {

    if (x < -16 || y < -32 || x + w > SCREEN_WIDTH ) {
        return true;
    }

    int left = x / TILE_SIZE;
    int right = (x + w - 1) / TILE_SIZE;
    int top = y / TILE_SIZE;
    int bottom = (y + h - 1) / TILE_SIZE;

    for (int row = top; row <= bottom; ++row) {
        for (int col = left; col <= right; ++col) {
            if (row >= 0 && row < MAP_HEIGHT && col >= 0 && col < MAP_WIDTH) {
                if (tileMap[row][col] == 1) { // 1 là ground
                    SDL_Rect tileBox = getTileBoundingBox(col, row);
                    SDL_Rect playerBox = {x + 20, y + 16, w, h};
                    if (checkCollision(playerBox, tileBox)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

