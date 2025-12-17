#pragma once
#include <string>
#include "SDL_include.h"
#include "Vec2.h"

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

    void SetScale(float sx, float sy);
    Vec2 GetScale() const { return scale; }
    void SetFlip(bool flipH, bool flipV = false);
    void SetAngle(double angle);
    double GetAngle() const { return angleDeg; }

    int  GetWidth()  const; // largura de um frame
    int  GetHeight() const; // altura de um frame
    bool IsOpen()    const { return texture != nullptr; }

private:
    SDL_Texture* texture{nullptr};
    int texW{0}, texH{0};
    int frameCountW{1}, frameCountH{1};
    SDL_Rect clipRect{0,0,0,0};
    Vec2 scale{1.f, 1.f};
    double angleDeg{0.0};
    SDL_RendererFlip flip{SDL_FLIP_NONE};
};
