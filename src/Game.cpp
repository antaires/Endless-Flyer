#include "Game.h"
#include "Constants.h"
#include "Shape.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

Game::Game(int w, int h) : isRunning(false), width(w), height(h)
{
  // TODO: use smart pointer instead
  random = new Random();

  board = new Board(random);
  graphics = new Graphics(width, height);
  ticksLastFrame;
  score = 0;
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
    board->SpawnShape();
  }

  // process ProcessInput
  int playerX = 0, playerY = 0;
  bool fired = false;
  if (!graphics->ProcessInput(mouseX, mouseY, fired, playerX, playerY)){isRunning = false;}
  if (fired)
  {
    board->FireBullet(mouseX, mouseY);
  }
  board->MoveShip(playerX, playerY);
  board->CheckCollisions();
  //TODO: handle score by time / destroying asteroids / pickups
  board->Update(deltaTime);
  // set game state
  // can increase speed etc based on score or time ...
}

void Game::Render() const
{
  graphics->Render(board, mouseX, mouseY);
}

bool Game::IsRunning() const
{
  return isRunning;
}
