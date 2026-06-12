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

uint32_t ScrollArea::get_largest_component_distance_y(){
  uint32_t max_distance = 0;
  for (const auto &comp : m_ui_components) {
    uint32_t distance = comp->get_y();
    if (distance > max_distance) {
      max_distance = distance;
    }
  }
  return max_distance;
}

uint32_t ScrollArea::get_largest_component_distance_x(){
  uint32_t max_distance = 0;
  for (const auto &comp : m_ui_components) {
    uint32_t distance = comp->get_x();
    if (distance > max_distance) {
      max_distance = distance;
    }
  }
  return max_distance;
}

void ScrollArea::add_component(WindowComponent *component)
{
  int x = component->get_x();
  int y = component->get_y();
  //component->set_position(x - m_x, y - m_y);
  std::cout << "Old component position: (" << x << ", " << y << ") -- new component position: (" << component->get_x() << ", " << component->get_y() << ")" << std::endl;
  m_ui_components.push_back(component);

  if (m_texture != nullptr)
  {
    SDL_DestroyTexture(m_texture);
  }

  m_texture_width = std::max(get_largest_component_distance_x() + 10, m_width);
  m_texture_height = std::max(get_largest_component_distance_y() + 10, m_height);
  std::cout << "Calculated texture size: " << m_texture_width << "x" << m_texture_height << std::endl;

  m_texture = SDL_CreateTexture((SDL_Renderer *)WindowMgr::get_instance().get_renderer()->get_sdl_renderer(), SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, m_texture_width, m_texture_height);
  if (m_texture == nullptr)
  {
    std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
    exit(-1);
  }
  std::cout << "Created texture: " << m_texture << " with size: " << m_texture_width << "x" << m_texture_height << std::endl;
}

int scroll_speed = 2;
void ScrollArea::update()
{
  for (const auto &comp : m_ui_components)
  {
    comp->update();
  }

  m_scroll_offset += scroll_speed;
  if (m_scroll_offset > m_texture_height - m_height)
  {    scroll_speed = -2;
  }
  else if (m_scroll_offset <= 0)
  {
    scroll_speed = 2;
  }
}

void ScrollArea::render()
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();

  renderer->render_color(0, 0, 0);
  renderer->render_rect(m_x, m_y, m_width, m_height, false);
  SDL_SetRenderTarget((SDL_Renderer *)renderer->get_sdl_renderer(), m_texture);

  SDL_RenderClear((SDL_Renderer *)renderer->get_sdl_renderer());
  
  renderer->render_color(255, 255, 255);
  renderer->render_rect(0, 0, m_texture_width, m_texture_height, true);

  renderer->render_color(0, 0, 0);
  renderer->render_rect(2, 2, 8, 8, true);

  for (const auto &comp : m_ui_components)
  {
    comp->render();
  }
  // std::cout << "0 - m_texture: " << m_texture << " -- current target: " << SDL_GetRenderTarget((SDL_Renderer *)renderer->get_sdl_renderer()) << std::endl;

  SDL_SetRenderTarget((SDL_Renderer *)renderer->get_sdl_renderer(), NULL);

  
  
  SDL_Rect viewport;
  viewport.x = 0;
  viewport.y = m_scroll_offset;
  viewport.w = std::min((int)m_width, (int)m_texture_width);
  viewport.h = std::min((int)m_height, (int)m_texture_height);

  SDL_Rect dst;
  dst.x = m_x;
  dst.y = m_y;
  dst.w = m_width;
  dst.h = m_height;

  // std::cout << "1 - m_texture: " << m_texture << " -- current target: " << SDL_GetRenderTarget((SDL_Renderer *)renderer) << std::endl;
  
  
  SDL_RenderCopy((SDL_Renderer *)renderer->get_sdl_renderer(), m_texture, &viewport, &dst);
}