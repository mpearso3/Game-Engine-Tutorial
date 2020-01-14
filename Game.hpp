#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
//#include "SDL2/SDL_ttf.h"
//#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
  Game();
  ~Game();

  void init(const char* title, int x_position, int y_position, int width, int height, bool full_screen);
  /* Handle user inputs */
  void handle_events();
  void update();
  void render();
  /* memory management */
  void clean();

  bool running() { return is_running; }

  static void add_tile(int id, int x, int y);
  static SDL_Renderer* renderer;
  static SDL_Event event;
  static std::vector<ColliderComponent*> colliders;

private:
  int counter;
  bool is_running;
  SDL_Window *window;
};
