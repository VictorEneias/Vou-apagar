#include "Resources.h"
#include "Game.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unordered_map>

namespace {
    std::unordered_map<std::string, SDL_Texture*> imageTable;
    std::unordered_map<std::string, Mix_Music*> musicTable;
    std::unordered_map<std::string, Mix_Chunk*> soundTable;
}

namespace Resources {

SDL_Texture* GetImage(const std::string& file) {
    auto it = imageTable.find(file);
    if (it != imageTable.end()) return it->second;

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
    if (!texture) {
        std::cerr << "[Resources] IMG_LoadTexture falhou para '" << file << "': " << SDL_GetError() << std::endl;
        return nullptr;
    }

    imageTable[file] = texture;
    return texture;
}

void ClearImages() {
    for (auto& entry : imageTable) {
        if (entry.second) {
            SDL_DestroyTexture(entry.second);
        }
    }
    imageTable.clear();
}

Mix_Music* GetMusic(const std::string& file) {
    auto it = musicTable.find(file);
    if (it != musicTable.end()) return it->second;

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (!music) {
        std::cerr << "[Resources] Mix_LoadMUS falhou para '" << file << "': " << Mix_GetError() << std::endl;
        return nullptr;
    }

    musicTable[file] = music;
    return music;
}

void ClearMusics() {
    for (auto& entry : musicTable) {
        if (entry.second) {
            Mix_FreeMusic(entry.second);
        }
    }
    musicTable.clear();
}

Mix_Chunk* GetSound(const std::string& file) {
    auto it = soundTable.find(file);
    if (it != soundTable.end()) return it->second;

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    if (!chunk) {
        std::cerr << "[Resources] Mix_LoadWAV falhou para '" << file << "': " << Mix_GetError() << std::endl;
        return nullptr;
    }

    soundTable[file] = chunk;
    return chunk;
}

void ClearSounds() {
    for (auto& entry : soundTable) {
        if (entry.second) {
            Mix_FreeChunk(entry.second);
        }
    }
    soundTable.clear();
}

} // namespace Resources