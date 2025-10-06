#include "Sprite.h"
#include "Game.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Sprite::Sprite() = default;

Sprite::Sprite(const std::string& file, int fcw, int fch)
: frameCountW(fcw), frameCountH(fch) {
    Open(file);
}

Sprite::~Sprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Sprite::Open(const std::string& file) {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Renderer* r = Game::GetInstance().GetRenderer();
    texture = IMG_LoadTexture(r, file.c_str());
    if (!texture) {
        std::cerr << "IMG_LoadTexture falhou: " << SDL_GetError() << std::endl;
        texW = texH = 0;
        clipRect = {0,0,0,0};
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);

    // frame grid mínimo = 1x1
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
    SDL_Rect dst{ x, y, w, h };
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

    // clamp defensivo
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
