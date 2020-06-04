#include <iostream>
#include "Constants.h"
#include "Game.h"


int main(int argc, char* args[]){

  Game game(WINDOW_WIDTH, WINDOW_HEIGHT);
  game.Start();

  while(game.IsRunning()){
    game.Update();
    game.Render();
  }

  return 0;
}
