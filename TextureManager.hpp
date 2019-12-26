#pragma once
#include "Game.hpp" // this is to include the sdl library files, change how this is done

class TextureManager
{
public:
  static SDL_Texture* LoadTexture(const char* filename);
  static void Draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination);
};
