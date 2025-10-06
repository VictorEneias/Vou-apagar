// ========================================
// src/Music.cpp
// ========================================
#include "Music.h"
#include <iostream>


Music::Music() = default;
Music::Music(const std::string& file){ Open(file); }
Music::~Music(){ Stop(0); if (music){ Mix_FreeMusic(music); music=nullptr; } }


void Music::Open(const std::string& file){
if (music){ Mix_FreeMusic(music); music=nullptr; }
music = Mix_LoadMUS(file.c_str());
if (!music){ std::cerr << "Mix_LoadMUS falhou: " << Mix_GetError() << std::endl; }
}


void Music::Play(int times){ if (music) Mix_PlayMusic(music, times); }
void Music::Stop(int ms){ Mix_FadeOutMusic(ms); }