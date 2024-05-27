#include "Renderer.hpp"

Renderer::Renderer(const SDL_Window *window, const SDL_Renderer *renderer)
    : m_sdl_window(window), m_sdl_renderer(renderer)
{
}

void Renderer::render_color(const uint8_t r, const uint8_t g, const uint8_t b)
{
  SDL_SetRenderDrawColor((SDL_Renderer *)m_sdl_renderer, r, g, b, 0);
}

void Renderer::render_rect(const int x, const int y, const int w, const int h)
{
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderDrawRect((SDL_Renderer *)m_sdl_renderer, &rect);
}