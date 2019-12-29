#pragma once

#include "ECS.h"

class PositionComponent : public Component
{
private:
  int x_position;
  int y_position;

public:
  int x() { return x_position; }
  int y() { return y_position; }  

  void init() override
  {
    x_position = 0;
    y_position = 0;
  }
  void update() override
  {
    x_position++;
    y_position++;
  }
  void set_position(int x, int y)
  {
    x_position = x;
    y_position = y;
  }
};
