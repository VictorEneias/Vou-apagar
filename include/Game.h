// ========================================
// include/Game.h
// ========================================
#pragma once
#include "SDL_include.h"
class State;


class Game {
public:
static Game& GetInstance();
void Run();


SDL_Renderer* GetRenderer() const;
State& GetState();
~Game();


private:
Game(const char* title, int width, int height);
Game(const Game&) = delete; Game& operator=(const Game&) = delete;


static Game* instance;
SDL_Window* window{nullptr};
SDL_Renderer* renderer{nullptr};
State* state{nullptr};
};