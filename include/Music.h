// ========================================
// include/Music.h
// ========================================
#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>


class Music {
public:
Music();
explicit Music(const std::string& file);
~Music();


void Play(int times=-1);
void Stop(int msToStop=1500);


void Open(const std::string& file);
bool IsOpen() const { return music!=nullptr; }


private:
Mix_Music* music{nullptr};
};