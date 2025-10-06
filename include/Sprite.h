#pragma once
#include <string>
#include "SDL_include.h"

class Sprite {
public:
    Sprite();
    explicit Sprite(const std::string& file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(const std::string& file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y, int w, int h) const;

    void SetFrame(int frame);
    void SetFrameCount(int fcw, int fch);

    int  GetWidth()  const; // largura de um frame
    int  GetHeight() const; // altura de um frame
    bool IsOpen()    const { return texture != nullptr; }

private:
    SDL_Texture* texture{nullptr};
    int texW{0}, texH{0};
    int frameCountW{1}, frameCountH{1};
    SDL_Rect clipRect{0,0,0,0};
};
