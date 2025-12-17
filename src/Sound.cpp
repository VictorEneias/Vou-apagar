#include "Sound.h"
#include "Resources.h"
#include <iostream>

Sound::Sound() = default;

Sound::Sound(const std::string& file) {
    Open(file);
}

Sound::~Sound() {
    Stop();
    chunk = nullptr;
}

void Sound::Open(const std::string& file) {
    chunk = Resources::GetSound(file);
    if (!chunk) {
        std::cerr << "[Sound] Falha ao carregar '" << file << "'" << std::endl;
    }
}

void Sound::Play(int times) {
    if (!chunk) return;
    channel = Mix_PlayChannel(-1, chunk, times - 1);
    if (channel < 0) {
        std::cerr << "[Sound] Mix_PlayChannel falhou: " << Mix_GetError() << std::endl;
    }
}

void Sound::Stop() {
    if (channel >= 0) {
        Mix_HaltChannel(channel);
        channel = -1;
    }
}