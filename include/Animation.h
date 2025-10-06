// ========================================
// include/Animation.h
// ========================================
#pragma once


struct Animation {
int frameStart{0};
int frameEnd{0};
float frameTime{0.f};


Animation() = default;
Animation(int fs, int fe, float ft) : frameStart(fs), frameEnd(fe), frameTime(ft) {}
};