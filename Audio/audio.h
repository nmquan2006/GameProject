#ifndef AUDIO_H
#define AUDIO_H

#include "../defs.h"

class Audio {
public:
    Audio();
    ~Audio();

    bool loadMusic(const char* path);
    void playMusic();
    void stopMusic();

private:
    Mix_Music* backgroundMusic;
};

#endif // AUDIO_H
