#ifndef _DEFS__H
#define _DEFS__H

#include <iostream>
#include<vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

const int SCREEN_WIDTH = 1024 ;
const int SCREEN_HEIGHT = 608;
#define WINDOW_TITLE "Quan's window"


const int GUNDAM_CLIPS[][4] = {
    {0,0,64,64},
    {64,0,64,64},
    {128,0,64,64},
};

const int GUNDAM_FRAMES = sizeof(GUNDAM_CLIPS)/sizeof(int)/4;

const int GATE_CLIPS[][4] = {
    {0,0,32,32},
    {32,0,32,32},
    {64,0,32,32},
    {96,0,32,32},
    {128,0,32,32},
    {160,0,32,32},
    {192,0,32,32},
    {224,0,32,32},
};

const int GATE_FRAMES = sizeof(GATE_CLIPS)/sizeof(int)/4;
#endif
