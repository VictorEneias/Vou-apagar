// ========================================
// src/Game.cpp
// ========================================
#include "Game.h"
#include "State.h"
#include "Resources.h"
#include "InputManager.h"
#include "Camera.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdexcept>
#include <iostream>


static constexpr const char* kWindowTitle = "Victor Enéias - 221038364";
static constexpr int kWindowWidth = 1200;
static constexpr int kWindowHeight = 900;


Game* Game::instance = nullptr;


static void sdlFail(const char* where){
std::cerr << "[SDL ERROR] " << where << ": " << SDL_GetError() << std::endl;
throw std::runtime_error("SDL failure");
}


Game& Game::GetInstance(){
if (!instance) instance = new Game(kWindowTitle, kWindowWidth, kWindowHeight);
return *instance;
}


Game::Game(const char* title, int width, int height){
if (instance) throw std::runtime_error("Game já instanciado");
instance = this;


if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) sdlFail("SDL_Init");
int imgFlags = IMG_INIT_PNG|IMG_INIT_JPG|IMG_INIT_TIF; if ((IMG_Init(imgFlags)&imgFlags)!=imgFlags) sdlFail("IMG_Init");
int mixFlags = MIX_INIT_FLAC|MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_MOD; if ((Mix_Init(mixFlags)&mixFlags)==0) sdlFail("Mix_Init");
if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)!=0) sdlFail("Mix_OpenAudio");
Mix_AllocateChannels(32);


window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
if (!window) sdlFail("SDL_CreateWindow");
renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
if (!renderer) sdlFail("SDL_CreateRenderer");


state = new State();
}


Game::~Game(){
delete state; state=nullptr;
Mix_CloseAudio(); Mix_Quit(); IMG_Quit();
if (renderer){ SDL_DestroyRenderer(renderer); renderer=nullptr; }
if (window) { SDL_DestroyWindow(window); window=nullptr; }
SDL_Quit();
}


void Game::Run(){
    Uint32 last = SDL_GetTicks();
    state->Start();
    while (!state->QuitRequested()){
        Uint32 now = SDL_GetTicks();
        float dt = (now - last) / 1000.f;
        last = now;

        InputManager::GetInstance().Update();
        if (InputManager::GetInstance().QuitRequested()) break;

        Camera::Update(dt);

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        state->Update(dt);
        state->Render();

        SDL_RenderPresent(renderer);
        // SDL_Delay(1); // opcional
    }
}


SDL_Renderer* Game::GetRenderer() const { return renderer; }
State& Game::GetState(){ return *state; }