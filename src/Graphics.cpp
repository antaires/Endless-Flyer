#include "Graphics.h"
#include "Shape.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <math.h>
#include "../lib/glm/glm.hpp"

SDL_Renderer* Graphics::renderer;
SDL_Event Graphics::event;
SDL_Window* window;

Graphics::Graphics(int w, int h): width(w), height(h)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cerr<< "Error Initializing SDL" << std::endl;
    return;
  }
  window = SDL_CreateWindow(
    NULL
    , SDL_WINDOWPOS_CENTERED
    , SDL_WINDOWPOS_CENTERED
    , width
    , height
    , SDL_WINDOW_BORDERLESS
  );
  if (!window){
    std::cerr<<"Error Creating SDL Window" << std::endl;
    return;
  }
  renderer = SDL_CreateRenderer(window, -1 , 0);
  if (!renderer){
    std::cerr<<"Error Creating SDL Renderer" << std::endl;
    return;
  }

  // init SDL_ttf
  if (TTF_Init() != 0){
    std::cerr<<"Error Initializing TTF" <<std::endl;
    return;
  }
  //font = LoadFont();
  // load textures for asteroids and ship
  shipTexture = LoadTexture("./assets/images/ship.png");
  asteroidTexture = LoadTexture("./assets/images/asteroid_fire.png");
}

Graphics::~Graphics()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}

bool Graphics::ProcessInput(int& mouseX, int& mouseY, bool& fired, int& playerX, int& playerY){

  int x_; int y_;
  SDL_GetMouseState(&x_, &y_);
  mouseX = x_; mouseY = y_;

  SDL_PollEvent(&event);
  switch(event.type)
  {
    case SDL_QUIT:
    { // clicking 'x button' on window
      return false;
    }
    case SDL_KEYDOWN:
    {
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        return false;
      }
      // move player
      if (event.key.keysym.sym == SDLK_UP)
      {
        //if (playerY > 0){playerY == 0;}
        playerY-=1;
      }
      if (event.key.keysym.sym == SDLK_DOWN)
      {
        //if (playerY < 0){playerY == 0;}
        playerY+=1;
      }
      if (event.key.keysym.sym == SDLK_LEFT)
      {
        //if (playerX > 0){playerX == 0;}
        playerX-=1;
      }
      if (event.key.keysym.sym == SDLK_RIGHT)
      {
        //if (playerX < 0){playerX == 0;}
        playerX+=1;
      }
    }
    /*
    case SDL_KEYUP:
    {
      // move player
      if (event.key.keysym.sym == SDLK_UP)
      {
        if (playerY < 0){playerY == 0;}
      }
      if (event.key.keysym.sym == SDLK_DOWN)
      {
        if (playerY > 0){playerY == 0;}
      }
      if (event.key.keysym.sym == SDLK_LEFT)
      {
        if (playerX < 0){playerX == 0;}
      }
      if (event.key.keysym.sym == SDLK_RIGHT)
      {
        if (playerX > 0){playerX == 0;}
      }
    }*/


    case SDL_MOUSEBUTTONDOWN:
    {
      fired = true;
    }
    default: {break;}
  }

  return true;

  /*
      // control game state from user input
      if (event.key.keysym.sym == SDLK_RETURN){
        switch(gameState){
          case START:
            board->Playing();
            break;
          case PLAYING:
            break;
          default:
            board->Reset();
            break;
        }
      }
  */
}

void Graphics::Render(Board* board, int mouseX, int mouseY) const {
  SDL_SetRenderDrawColor(renderer, 65, 112, 100, 255);
  // clear back buffer
  SDL_RenderClear(renderer);

  /*
  switch(gameState){
    case START:
      Graphics::RenderStartScreen();
      break;
    case PLAYING:
      Graphics::RenderBoard(board);
      break;
    case GAME_OVER
      Graphics::RenderEndScreen(board, gameState);
      break;
    default:
      break;
  } */
  RenderBoard(board, mouseX, mouseY);

  // swap buffers and render
  SDL_RenderPresent(renderer);
}

void Graphics::RenderBoard(Board* board, int mouseX, int mouseY) const {

  // TODO to draw textures use:
  // SDL_RenderCopyEx(renderer, texture, &sourceRectangle, &destinationRectangle, 0.0, NULL, flip);

  // background
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = WINDOW_WIDTH;
  rect.h = WINDOW_HEIGHT;
  SDL_SetRenderDrawColor(renderer, 65, 112, 100, 255);
  SDL_RenderFillRect(renderer, &rect);

  SDL_Rect source;
  source.x = 0;
  source.y = 0;
  source.w = 400;
  source.h = 400;

  // draw asteroids
  auto shapes = board->GetShapes();
  for(auto itShapes = shapes.begin(); itShapes != shapes.end(); itShapes++)
  {
    Shape* shape = itShapes->first;
    // todo check if active

    SDL_Rect destination;
    destination.x = shape->position.x;
    destination.y = shape->position.y;
    destination.w = shape->width;
    destination.h = shape->height;
    //SDL_SetRenderDrawColor(renderer, shape->red, shape->green, shape->blue, 255);
    //SDL_RenderFill Rect(renderer, &s);

    // use texture
    SDL_RenderCopyEx(renderer, asteroidTexture, &source, &destination, 0.0, NULL, SDL_FLIP_NONE);
  }

  //draw bullets
  auto bullets = board->GetBullets();
  for(auto it = bullets.begin(); it != bullets.end(); ++it)
  {
    Bullet* b = it->first;
    if (b->IsActive())
    {
      SDL_Rect bullet;
      bullet.x = b->position.x;
      bullet.y = b->position.y;
      bullet.w = b->size;
      bullet.h = b->size;
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRect(renderer, &bullet);
    }
  }

  // draw player
  Player* player = board->GetPlayer();
  SDL_Rect destination;
  destination.x = player->position.x;
  destination.y = player->position.y;
  destination.w = player->size;
  destination.h = player->size;
  // rotate ship towards mouse
  double deltaY = player->position.y - mouseY;
  double deltaX = player->position.x - mouseX;
  double angle  = atan2(deltaY, deltaX) * 180 / PI + 180;
  SDL_RenderCopyEx(renderer, shipTexture, &source, &destination, angle, NULL, SDL_FLIP_NONE);
}

SDL_Texture* Graphics::LoadTexture(const char* fileName)
{ // old school C string type, not C++ strings for filePath
  // TODO - rename fileName to filePath?
  SDL_Surface* surface = IMG_Load(fileName);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}

/*
void Graphics::RenderStartScreen() const {
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = WINDOW_WIDTH;
  rect.h = WINDOW_HEIGHT;
  SDL_SetRenderDrawColor(renderer, 65, 112, 100, 255);
  SDL_RenderFillRect(renderer, &rect);
  Graphics::RenderText(std::string("Tic").c_str(), WINDOW_WIDTH / 5, 0);
  Graphics::RenderText(std::string("Tac").c_str(), WINDOW_WIDTH / 5, WINDOW_HEIGHT / 3);
  Graphics::RenderText(std::string("Toe").c_str(), WINDOW_WIDTH / 5, (WINDOW_HEIGHT / 3) *2);
}

void Graphics::RenderCell(char cell, int x, int y, int w, int h) const {
  unsigned int r;
  unsigned int g;
  unsigned int b;
  std::string text;

  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  switch(cell){
    case 'X':
      r = 52;
      g = 235;
      b = 219;
      text = "X";
      break;
    case 'O':
      r = 235;
      g = 171;
      b = 52;
      text = "O";
      break;
    default:
      r = 84;
      g = 84;
      b = 84;
      text = "";
  }

  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderFillRect(renderer, &rect);
  Graphics::RenderText(text.c_str(), (x + X_OFFSET), (y + Y_OFFSET));
}

void Graphics::RenderLines() const {
  Graphics::RenderLine(WINDOW_WIDTH / 3, 0, 10, WINDOW_HEIGHT);
  Graphics::RenderLine((WINDOW_WIDTH / 3 )* 2, 0, 10, WINDOW_HEIGHT);
  Graphics::RenderLine(0, WINDOW_HEIGHT /3, WINDOW_WIDTH, 10);
  Graphics::RenderLine(0, (WINDOW_HEIGHT / 3 )* 2, WINDOW_WIDTH, 10);
}

void Graphics::RenderLine(int x, int y, int w, int h) const {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void Graphics::RenderText(const char* text, int x, int y) const {
  if (!text || !font){
    std::cerr<<"\nCannot render text";
    return;
  }
  int textW = 0;
  int textH = 0;
  SDL_Color White = {255, 255, 255};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, White);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  SDL_QueryTexture(Message, NULL, NULL, &textW, &textH);
  SDL_Rect pos;
  pos.x = x;
  pos.y = y;
  pos.w = textW;
  pos.h = textH;
  SDL_RenderCopy(renderer, Message, NULL, &pos);

  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
}

TTF_Font* Graphics::LoadFont(){
  TTF_Font* f = TTF_OpenFont(std::string("./assets/fonts/arial.ttf").c_str(), 100);
  if (!f){
    std::cout<<TTF_GetError();
    std::cerr<<"\nCannot load font";
  }
  return f;
}

void Graphics::RenderEndScreen(Board* board, unsigned int gameState) const {
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = WINDOW_WIDTH;
  rect.h = WINDOW_HEIGHT;
  SDL_SetRenderDrawColor(renderer, 65, 112, 100, 255);
  SDL_RenderFillRect(renderer, &rect);

  switch(gameState){
    case X_WIN:
      Graphics::RenderText(std::string("X").c_str(), WINDOW_WIDTH / 3, 0);
      Graphics::RenderText(std::string("Wins").c_str(), WINDOW_WIDTH / 6, WINDOW_HEIGHT / 3);
      break;
    case O_WIN:
    Graphics::RenderText(std::string("O").c_str(), WINDOW_WIDTH / 3, 0);
    Graphics::RenderText(std::string("Wins").c_str(), WINDOW_WIDTH / 7, WINDOW_HEIGHT / 3);
      break;
    default:
    Graphics::RenderText(std::string("Draw").c_str(), WINDOW_WIDTH / 7, WINDOW_HEIGHT / 3);
      break;
  }
}
*/
