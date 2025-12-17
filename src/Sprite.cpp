#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
#include <iostream>

Sprite::Sprite() = default;

Sprite::Sprite(const std::string& file, int fcw, int fch)
: frameCountW(fcw), frameCountH(fch) {
    Open(file);
}

Sprite::~Sprite() {
    texture = nullptr;
}

void Sprite::Open(const std::string& file) {
    SDL_Texture* newTexture = Resources::GetImage(file);
    if (!newTexture) {
        std::cerr << "[Sprite] Falha ao abrir textura '" << file << "'" << std::endl;
        texture = nullptr;
        texW = texH = 0;
        clipRect = {0,0,0,0};
        return;
    }

    texture = newTexture;
    SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);

    if (frameCountW < 1) frameCountW = 1;
    if (frameCountH < 1) frameCountH = 1;

    const int fw = texW / frameCountW;
    const int fh = texH / frameCountH;
    SetClip(0, 0, fw, fh);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = { x, y, w, h };
}

void Sprite::Render(int x, int y, int w, int h) const {
    if (!texture) return;
    SDL_Rect dst{ x - (int)Camera::posX, y - (int)Camera::posY, w, h };
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst);
}

void Sprite::SetFrame(int frame) {
    if (!texture) return;

    if (frameCountW < 1) frameCountW = 1;
    if (frameCountH < 1) frameCountH = 1;

    const int totalW = texW;
    const int totalH = texH;
    const int fw = totalW / frameCountW;
    const int fh = totalH / frameCountH;

    const int row = frame / frameCountW;
    const int col = frame % frameCountW;
    int x = col * fw;
    int y = row * fh;

    if (x + fw > totalW) x = totalW - fw;
    if (y + fh > totalH) y = totalH - fh;

    SetClip(x, y, fw, fh);
}

void Sprite::SetFrameCount(int fcw, int fch) {
    frameCountW = (fcw > 0 ? fcw : 1);
    frameCountH = (fch > 0 ? fch : 1);
    SetFrame(0);
}

int Sprite::GetWidth() const {
    return (frameCountW > 0 ? texW / frameCountW : texW);
}

int Sprite::GetHeight() const {
    return (frameCountH > 0 ? texH / frameCountH : texH);
}