// ========================================
// include/SpriteRenderer.h
// ========================================
#pragma once
#include <string>
#include "Component.h"
#include "Sprite.h"


class SpriteRenderer : public Component {
public:
    explicit SpriteRenderer(GameObject& go);
    SpriteRenderer(GameObject& go, const std::string& file, int fcw=1, int fch=1);


    void Open(const std::string& file);
    void SetFrameCount(int fcw, int fch);
    void SetFrame(int frame);
    void SetScale(float sx, float sy);
    void SetFlip(bool flipH, bool flipV=false);
    void SetAngle(double angle);


void Update(float dt) override;
void Render() override;


private:
    Sprite sprite;
};