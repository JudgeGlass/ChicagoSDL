#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Singleton.hpp"
#include <SDL2/SDL.h>
#include <iostream>

class Renderer
{
public:
public:
  Renderer(const SDL_Window *window, const SDL_Renderer *renderer);

  void render_color(const uint8_t r, const uint8_t g, const uint8_t b);
  void render_rect(const int x, const int y, const int w, const int h);

private:
  const SDL_Window *m_sdl_window;
  const SDL_Renderer *m_sdl_renderer;

private:
};

#endif