// ========================================
// src/SpriteRenderer.cpp
// ========================================
#include "SpriteRenderer.h"
#include "GameObject.h"


SpriteRenderer::SpriteRenderer(GameObject& go) : Component(go), sprite() {}


SpriteRenderer::SpriteRenderer(GameObject& go, const std::string& file, int fcw, int fch)
: Component(go), sprite(file, fcw, fch) {
// Ajusta box do GO pelo tamanho do frame, se ainda não definido
if (associated.box.w == 0.f) associated.box.w = (float)sprite.GetWidth();
if (associated.box.h == 0.f) associated.box.h = (float)sprite.GetHeight();
sprite.SetFrame(0);
}


void SpriteRenderer::Open(const std::string& file){
sprite.Open(file);
if (associated.box.w == 0.f) associated.box.w = (float)sprite.GetWidth();
if (associated.box.h == 0.f) associated.box.h = (float)sprite.GetHeight();
}


void SpriteRenderer::SetFrameCount(int fcw, int fch){ sprite.SetFrameCount(fcw,fch); }
void SpriteRenderer::SetFrame(int frame){ sprite.SetFrame(frame); }
void SpriteRenderer::SetScale(float sx, float sy){ sprite.SetScale(sx, sy); }
void SpriteRenderer::SetFlip(bool flipH, bool flipV){ sprite.SetFlip(flipH, flipV); }
void SpriteRenderer::SetAngle(double angle){ sprite.SetAngle(angle); }


void SpriteRenderer::Update(float /*dt*/){ /* vazio */ }


void SpriteRenderer::Render(){
sprite.SetScale(associated.scale.x, associated.scale.y);
sprite.SetAngle(associated.angleDeg);
sprite.Render((int)associated.box.x, (int)associated.box.y, (int)associated.box.w, (int)associated.box.h);
}