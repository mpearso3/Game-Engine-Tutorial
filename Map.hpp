#pragma once

#include "Game.hpp"

class Map
{
public:
  Map();
  ~Map();

  void load_map(int arr[20][25]);
  void draw_map();

private:
  SDL_Rect source, destination;

  SDL_Texture* dirt;
  SDL_Texture* grass;
  SDL_Texture* water;

  int map[20][25];
};
