#pragma once
#include <string>
#include <SDL2/SDL_mixer.h>

class Sound {
public:
    Sound();
    explicit Sound(const std::string& file);
    ~Sound();
    void Play(int times = 1);
    void Stop();
    void Open(const std::string& file);
    bool IsOpen() const { return chunk != nullptr; }
private:
    Mix_Chunk* chunk{nullptr};
    int channel{-1};
};