#pragma once
#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace Resources {
    SDL_Texture* GetImage(const std::string& file);
    void ClearImages();

    Mix_Music*   GetMusic(const std::string& file);
    void ClearMusics();

    Mix_Chunk*   GetSound(const std::string& file);
    void ClearSounds();
}