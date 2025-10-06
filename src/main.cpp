// ========================================
// src/main.cpp
// ========================================
#include "Game.h"


int main(){
auto& game = Game::GetInstance();
game.Run();
return 0;
}