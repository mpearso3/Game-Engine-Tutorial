#pragma once

#include "Components.h"

class PositionComponent: public Component
{
private:
  int x_position;
  int y_position;
public:
  PositionComponent()
  {
    x_position = 0;
    y_position = 0;
  }
  PositionComponent(int x, int y)
  {
    x_position = x;
    y_position = y;
  }
  void update() override
  {
    x_position++;
    y_position++;
  }
  int x() { return x_position; }
  void x(int x) { x_position = x; }
  int y() { return y_position; }
  void y(int y) { y_position = y; }
  void set_position(int x, int y)
  {
    x_position = x;
    y_position = y;
  }
};
