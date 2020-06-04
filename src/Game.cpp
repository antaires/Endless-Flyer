#include "Game.h"
#include "Constants.h"
#include "Shape.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

Game::Game(int w, int h) : isRunning(false), width(w), height(h)
{
  // TODO: use smart pointer instead
  board = new Board();
  graphics = new Graphics(width, height);
  ticksLastFrame;
  score = 0;

  random = new Random();
}

Game::~Game()
{
  // TODO: cleanup
}

void Game::Start()
{
  isRunning = true;
}

void Game::Update()
{
  // wait until FRAME_TARGET_TIME reached since last frame
  while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
  float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
  deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
  ticksLastFrame = SDL_GetTicks();

  if ( random->GetRand(0, 31) < 3 )
  {
    board->SpawnShape(random);
  }

  // process ProcessInput
  int x = -1, y = -1;
  if (!graphics->ProcessInput(x, y)){isRunning = false;}
  if (x > 0 && y > 0)
  {
    board->FireBullet(x, y);
  }

  board->CheckCollisions();

  /* TODO: handle score by time / destroying asteroids / pickups
  if ( board->CheckRows() )
  {
    score++; // TODO: display score / UI
    std::cout<<"\nscore: "<<score;
  }*/

  board->Update(deltaTime);

  // set game state
  // can increase speed etc based on score or time ...
}

void Game::Render() const
{
  graphics->Render(board);
}

bool Game::IsRunning() const
{
  return isRunning;
}
