#pragma once
#include "SDL2/SDL.h"

class Collision
{
public:
  static bool AABB(const SDL_Rect& rectangle_a, const SDL_Rect& rectangle_b); // axis aligned bounding box
};
