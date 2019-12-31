#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent: public Component
{
public:
  Vector2D position;
  Vector2D velocity;
  int speed = 3;
  int height = 32;
  int width = 32;
  int scale = 1;

  TransformComponent()
  {
    position.x = 0.0f;
    position.y = 0.0f;
  }
  TransformComponent(int s)
  {
    position.x = 0.0f;
    position.y = 0.0f;
    scale = s;
  }
  TransformComponent(float x, float y)
  {
    position.x = x;
    position.y = y;
  }
  TransformComponent(float x, float y, int w, int h, int s)
  {
    position.x = x;
    position.y = y;
    width = w;
    height = h;
    scale = s;
  }

  void init() override
  {
    velocity.x = 0;
    velocity.y = 0;
  }
  void update() override
  {
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
  }
};
