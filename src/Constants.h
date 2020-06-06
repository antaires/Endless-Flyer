#pragma once

#include <assert.h>
#include <iostream>

// window
const unsigned int WINDOW_WIDTH = 1000;
const unsigned int WINDOW_HEIGHT = 500;

const float BULLET_SPEED = 600.0f;
const float SHIP_SPEED   = 500.0f;

const unsigned int PLAYER_SIZE = 20;
const unsigned int BRICK_SIZE = 20;
const unsigned int GRACE = 1;
const unsigned int BULLET_SIZE = 5;

const unsigned int FRAME_TARGET_TIME = 60;

static int Clamp(int num)
{
  // get closet mult of BRICK_SIZE
  if (num == 0){return num;}
  int remainder = num % BRICK_SIZE;
  if (remainder == 0){return num;}
  if (remainder >= BRICK_SIZE / 2)
  { // round up
      return num + BRICK_SIZE - remainder;
  } // round down
  return num - remainder;
}
