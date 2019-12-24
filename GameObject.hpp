#pragma once
#include "Game.hpp" // this is to include the sdl library files, change how this is done

class GameObject
{
public:
  GameObject(const char* texture_sheet, SDL_Renderer* renderer, int x, int y);
  ~GameObject();

  void Update();
  void Render();

private:
  int x_position;
  int y_position;
  SDL_Texture* object_texture;
  SDL_Rect source_rectangle, destination_rectangle;
  SDL_Renderer* renderer;
};
