#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Board.h"

#include <cmath>
#include <cstdlib>
#include <string>

class Graphics {
  private:
    int width;
    int height;
    TTF_Font* font;
    TTF_Font* LoadFont();
    void RenderBoard(Board* board) const;
  public:
    Graphics(int width, int height);
    ~Graphics();
    static SDL_Renderer *renderer;
    static SDL_Event event;
    SDL_Window *window;

    bool ProcessInput(int& mouseX, int& mouseY, int& playerX, int&playerY );
    void Render(Board* board) const;
};
