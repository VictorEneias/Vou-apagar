#include "Camera.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"
#include <SDL2/SDL.h>

float Camera::posX{0.f};
float Camera::posY{0.f};
GameObject* Camera::focus{nullptr};

void Camera::Follow(GameObject* go){ focus = go; }
void Camera::Unfollow(){ focus = nullptr; }

void Camera::Update(float dt){
  if(focus){
    int rw=0,rh=0;
    SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &rw, &rh);
    float cx = focus->box.x + focus->box.w*0.5f;
    float cy = focus->box.y + focus->box.h*0.5f;
    posX = cx - rw*0.5f; posY = cy - rh*0.5f;
  }else{
    auto& in = InputManager::GetInstance();
    const float spd=300.f;
    if(in.IsKeyDown(SDL_SCANCODE_W) || in.IsKeyDown(SDL_SCANCODE_UP))    posY -= spd*dt;
    if(in.IsKeyDown(SDL_SCANCODE_S) || in.IsKeyDown(SDL_SCANCODE_DOWN))  posY += spd*dt;
    if(in.IsKeyDown(SDL_SCANCODE_A) || in.IsKeyDown(SDL_SCANCODE_LEFT))  posX -= spd*dt;
    if(in.IsKeyDown(SDL_SCANCODE_D) || in.IsKeyDown(SDL_SCANCODE_RIGHT)) posX += spd*dt;
  }
}
