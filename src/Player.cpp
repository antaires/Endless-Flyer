#include "Player.h"

Player::Player()
{
  position.x = WINDOW_WIDTH / 2;
  position.y = WINDOW_HEIGHT / 2;
  velocity.x = 0; velocity.y = 0;
  size = PLAYER_SIZE;
}

void Player::SetVelocity(int x, int y)
{
  velocity.x = x;
  velocity.y = y;
}

void Player::UpdatePosition(int x, int y)
{
  position.x += x * 10;
  position.y += y * 10;
}

void Player::Update(float deltaTime)
{
  position.x = (position.x + (velocity.x * SHIP_SPEED) * deltaTime);
  position.y = (position.y + (velocity.y * SHIP_SPEED) * deltaTime);

  velocity.x = 0;
  velocity.y = 0;
}

void Player::Kill()
{
    isActive = false;
}

bool Player::IsActive() const
{
  return isActive;
}
