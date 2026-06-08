#include "ScrollArea.hpp"

#include <SDL2/SDL_render.h>

ScrollArea::ScrollArea(int x, int y, uint16_t width, uint16_t height)
{
  m_x = x;
  m_y = y;

  m_width = width;
  m_height = height;

  m_texture = nullptr;
}

ScrollArea::~ScrollArea()
{
  SDL_DestroyTexture(m_texture);
}

void ScrollArea::add_component(WindowComponent *component)
{
  int x = component->get_x();
  int y = component->get_y();
  component->set_position(x + m_x, y + m_y);
  m_ui_components.push_back(component);

  if (m_texture != nullptr)
  {
    SDL_DestroyTexture(m_texture);
  }

  if(component->get_width() > m_texture_width)
  {
    m_texture_width = component->get_width();
  }
  m_texture_height += component->get_height();

  m_texture = SDL_CreateTexture((SDL_Renderer *)WindowMgr::get_instance().get_renderer()->get_sdl_renderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, m_texture_width, m_texture_height);
  if (m_texture == nullptr)
  {
    std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
    exit(-1);
  }
  std::cout << "Created texture: " << m_texture << " with size: " << m_texture_width << "x" << m_texture_height << std::endl;
}

void ScrollArea::update()
{
  for (const auto &comp : m_ui_components)
  {
    comp->update();
  }
}

void ScrollArea::render()
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();

  renderer->render_color(0, 0, 0);
  renderer->render_rect(m_x, m_y, m_width, m_height, false);
  SDL_SetRenderTarget((SDL_Renderer *)renderer, m_texture);

  SDL_RenderClear((SDL_Renderer *)renderer);

  renderer->render_color(0, 0, 0);
  renderer->render_rect(m_x, m_y, m_texture_width, m_texture_height, true);

  // for (const auto &comp : m_ui_components)
  // {
  //   comp->render();
  // }
  std::cout << "0 - m_texture: " << m_texture << " -- current target: " << SDL_GetRenderTarget((SDL_Renderer *)renderer) << std::endl;

  SDL_SetRenderTarget((SDL_Renderer *)renderer, NULL);

  
  
  SDL_Rect viewport;
  viewport.x = 0;
  viewport.y = 0;
  viewport.w = m_texture_width;
  viewport.h = m_texture_height;
  
  SDL_Rect dst;
  dst.x = m_x;
  dst.y = m_y;
  dst.w = m_width;
  dst.h = m_height;

  std::cout << "1 - m_texture: " << m_texture << " -- current target: " << SDL_GetRenderTarget((SDL_Renderer *)renderer) << std::endl;
  
  
  SDL_RenderCopy((SDL_Renderer *)renderer, m_texture, &viewport, &dst);
}