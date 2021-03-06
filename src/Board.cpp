#include "Board.h"

#include "../lib/glm/glm.hpp"

#include <iostream>
#include <cmath>

Board::Board(Random* r)
{
  random = r;
  lastShapeSpawnPositionX = 0;
  lastShapeSpawnPositionY = 0;
  player = new Player();
}

Board::~Board(){}

void Board::Update(float deltaTime)
{
  for(auto it = shapes.begin(); it != shapes.end(); ++it)
  {
    // TODO: active check here
    Shape* shape = it->first;
    shape->Update(deltaTime);
  }

  for(auto it = bullets.begin(); it != bullets.end(); ++it)
  {
    Bullet* b = it->first;
    if (b->IsActive())
    {
      b->Update(deltaTime);
    }
  }

  player->Update(deltaTime);
}

void Board::FireBullet(int x, int y)
{
  Bullet* bullet = new Bullet(x, y, player->position.x, player->position.y, BULLET_SIZE);
  bullets[bullet] = bullet;
}

void Board::MoveShip(int x, int y)
{
  // set velocity here, and move ship on update
  //player->SetVelocity(x, y);
  player->UpdatePosition(x, y);
}


Shape* Board::SpawnShape()
{
  // TODO add shape to list of active SHAPES
  int size = random->GetRand(30, 100);

  glm::vec2 pos;
  bool side = (int) random->GetRand(0, 4);
  if (side == 0)
  {
    pos.x = WINDOW_WIDTH - size;
    pos.y = random->GetRand(0, WINDOW_HEIGHT - size);
  } else if (side == 1){
    pos.x = 0;
    pos.y = random->GetRand(0, WINDOW_HEIGHT - size);
  } else if (side == 2){
    pos.x = random->GetRand(0, WINDOW_WIDTH - size);
    pos.y = WINDOW_HEIGHT - size;
  } else {
    pos.x = random->GetRand(0, WINDOW_WIDTH - size);
    pos.y = 0;
  }

  Shape* shape = new Shape(size, pos, player->position);
  lastShapeSpawnPositionX = shape->position.x;
  lastShapeSpawnPositionY = shape->position.y;
  shapes[shape] = shape;
  return shape;
}


Shape* Board::SpawnShapeExplosion(int size, glm::vec2& pos, glm::vec2& target)
{
  Shape* shapeExplosion = new Shape(size, pos, target);
  shapes[shapeExplosion] = shapeExplosion;
  return shapeExplosion;
}

void Board::CheckCollisions()
{
  // todo need to account for velocity (might pass through a shape too quickly)
  for(auto itShapes = shapes.begin(); itShapes != shapes.end(); itShapes++)
  {
    Shape* shape = itShapes->first;

    // TODO COLLISION: PLAYER - ASTEROID


    // COLLISION SHAPE - BULLET
    Bullet* deadBullet = nullptr;
    for(auto itBullets = bullets.begin(); itBullets != bullets.end(); itBullets++)
    {
      Bullet* bullet = itBullets->first;
      if(bullet->IsActive())
      {
          // todo -> need to SORT shapes by distance to bullet and kill closest 1st
          if (CollisionShape(shape, bullet))
          {
            // TODO : KILL SHAPE
            bullet->Kill();
            deadBullet = bullet;

            shape->Kill();
            // spawn explosion pieces
            if (shape->width > 20)
            {
              for(int i = 0; i < 4; i++)
              {
                int size = (int) shape->width/4;
                glm::vec2 target;
                target.x = (int) random->GetRand(0, WINDOW_WIDTH);
                target.y = (int) random->GetRand(0, WINDOW_HEIGHT);
                SpawnShapeExplosion(size, shape->position, target);
              }
            }

            shapesToRemove[shape] = shape;
            continue; // TODO or break?
          }

          // TODO Kill bullets offscreen
      }
      else
      {
        bulletsToRemove[bullet] = bullet;
      }
    }
    // remove dead bullet for next shape
    if (deadBullet)
    {
      bullets.erase(deadBullet);
      delete deadBullet;
    }
    // remove offscreen bullets
    RemoveDeadBullets();
  }
  // TODO make removeDeadShapes
  RemoveDeadShapes();
}

// TODO: make template
bool Board::CollisionShape(Shape* shape, Bullet* bullet) const
{
  if (shape->position.x < bullet->position.x + bullet->size &&
      shape->position.x + shape->width > bullet->position.x &&
      shape->position.y < bullet->position.y + bullet->size &&
      shape->position.y + shape->height > bullet->position.y)
      {
        return true;
      }
  return false;
}

void Board::RemoveDeadBullets()
{
  for(auto it = bulletsToRemove.begin(); it != bulletsToRemove.end(); it++)
  {
    Bullet* bullet = it->first;
    bullets.erase(bullet);
    // todo delete bullet here
  }
  bulletsToRemove.clear();
}

void Board::RemoveDeadShapes()
{
  for(auto it = shapesToRemove.begin(); it != shapesToRemove.end(); it++)
  {
    Shape* shape = it->first;
    shapes.erase(shape);
  }
  shapesToRemove.clear();
}

std::unordered_map<Shape*, Shape*>  Board::GetShapes() const
{
  return shapes;
}

std::unordered_map<Bullet*, Bullet*> Board::GetBullets() const
{
  return bullets;
}

Player* Board::GetPlayer() const
{
  return player;
}
