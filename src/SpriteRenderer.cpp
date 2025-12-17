// ========================================
// src/SpriteRenderer.cpp
// ========================================
#include "SpriteRenderer.h"
#include "GameObject.h"


SpriteRenderer::SpriteRenderer(GameObject& go) : Component(go), sprite() {}


SpriteRenderer::SpriteRenderer(GameObject& go, const std::string& file, int fcw, int fch)
: Component(go), sprite(file, fcw, fch) {
// Ajusta box do GO pelo tamanho do frame
associated.box.w = (float)sprite.GetWidth();
associated.box.h = (float)sprite.GetHeight();
sprite.SetFrame(0);
}


void SpriteRenderer::Open(const std::string& file){
sprite.Open(file);
associated.box.w = (float)sprite.GetWidth();
associated.box.h = (float)sprite.GetHeight();
}


void SpriteRenderer::SetFrameCount(int fcw, int fch){ sprite.SetFrameCount(fcw,fch); }
void SpriteRenderer::SetFrame(int frame){ sprite.SetFrame(frame); }


void SpriteRenderer::Update(float /*dt*/){ /* vazio */ }


void SpriteRenderer::Render(){
sprite.Render((int)associated.box.x, (int)associated.box.y, (int)associated.box.w, (int)associated.box.h);
}