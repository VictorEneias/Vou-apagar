// ========================================
// src/Music.cpp
// ========================================
#include "Music.h"
#include "Resources.h"
#include <iostream>


Music::Music() = default;
Music::Music(const std::string& file){ Open(file); }
Music::~Music(){ Stop(0); music=nullptr; }


void Music::Open(const std::string& file){
    music = Resources::GetMusic(file);
    if (!music){
        std::cerr << "[Music] Falha ao carregar '" << file << "'" << std::endl;
    }
}


void Music::Play(int times){ if (music) Mix_PlayMusic(music, times); }
void Music::Stop(int ms){ Mix_FadeOutMusic(ms); }