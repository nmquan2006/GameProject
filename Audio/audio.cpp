#include "audio.h"

Audio::Audio() : backgroundMusic(nullptr) {}

Audio::~Audio() {
    if (backgroundMusic) Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
}

bool Audio::loadMusic(const char* path) {
    backgroundMusic = Mix_LoadMUS(path);
    if (!backgroundMusic) {
        SDL_Log("Không thể tải nhạc: %s", Mix_GetError());
        return false;
    }
    return true;
}

void Audio::playMusic() {
    if (backgroundMusic) Mix_PlayMusic(backgroundMusic, -1); // Lặp vô hạn
}

void Audio::stopMusic() {
    Mix_HaltMusic();
}
