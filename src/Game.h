#pragma once

#include "Graphics.h"
#include "Random.h"

class Game {
  private:
    bool isRunning;
    Graphics* graphics;
    Board* board;
    int width;
    int height;
    float ticksLastFrame;
    int score;
    Random* random;
  public:
    Game(int w, int h);
    ~Game();
    void Start();
    void Update();
    void Render() const;
    bool IsRunning() const;
};
