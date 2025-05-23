#include "Renderer.hpp"

Renderer::Renderer(const SDL_Window *window, const SDL_Renderer *renderer)
    : m_sdl_window(window), m_sdl_renderer(renderer)
{
  m_ui_textures = std::make_unique<Texture>("./res/uiAtlas.png", 16, 16);
  m_ui_textures->load((SDL_Renderer *)m_sdl_renderer);

  m_ui_font_textures = std::make_unique<Texture>("./res/fontAtlas.png", 8, 8);
  m_ui_font_textures->load((SDL_Renderer *)m_sdl_renderer);
}

void Renderer::render_color(const uint8_t r, const uint8_t g, const uint8_t b)
{
  SDL_SetRenderDrawColor((SDL_Renderer *)m_sdl_renderer, r, g, b, 255);
}

void Renderer::render_color(int color)
{
  int r = (color & 0xFF0000) >> 16;
  int g = (color & 0xFF00) >> 8;
  int b = (color & 0xFF);

  render_color(r, g, b);
}

void Renderer::render_backdrop(const int x, const int y, const int w, const int h)
{
  SDL_SetRenderDrawBlendMode((SDL_Renderer *)m_sdl_renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor((SDL_Renderer *)m_sdl_renderer, 0, 0, 0, 160);
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderFillRect((SDL_Renderer *)m_sdl_renderer, &rect);
}

void Renderer::render_rect(const int x, const int y, const int w, const int h, bool filled)
{
  SDL_Rect rect = {x, y, w, h};
  if (filled)
  {
    SDL_RenderFillRect((SDL_Renderer *)m_sdl_renderer, &rect);
  }
  SDL_RenderDrawRect((SDL_Renderer *)m_sdl_renderer, &rect);
}

void Renderer::render_texture(const int index, const int x, const int y, const int scale, const int rowa)
{
  m_ui_textures->render((SDL_Renderer *)m_sdl_renderer, index, x, y, scale, rowa);
}

void Renderer::draw_string(int x, int y, std::string text, int color, int scale)
{
  int r = (color & 0xFF0000) >> 16;
  int g = (color & 0xFF00) >> 8;
  int b = (color & 0xFF);

  SDL_SetTextureColorMod(m_ui_font_textures->texture, r, g, b);

  // std::transform(text.begin(), text.end(), text.begin(), ::toupper);
  for (int i = 0; i < (int)text.length(); i++)
  {
    int index = font_chars.find((char)text[i]);
    if (index >= 0)
    {
      int y_offset = 0;
      if (text[i] == 'p' || text[i] == 'g' || text[i] == 'y' || text[i] == 'q')
      {
        y_offset = 1;
      }
      m_ui_font_textures->render(
          (SDL_Renderer *)m_sdl_renderer, index, x + i * (m_ui_font_textures->pw * scale), y + y_offset, scale, 32);
    }
  }
}

void Renderer::draw_string_shadowed(int x, int y, std::string text, int color, int scale)
{
  draw_string(x + scale, y + scale, text, 0x000000, scale);
  draw_string(x, y, text, color, scale);
}

const SDL_Renderer *Renderer::get_sdl_renderer() const
{
  return m_sdl_renderer;
}