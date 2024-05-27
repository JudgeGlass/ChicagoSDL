#include "Components/Button.hpp"

Button::Button(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const std::string &text)
    : m_width(width), m_height(height), m_text(text)
{
  m_x = x;
  m_y = y;
}

void Button::render()
{
  Renderer *renderer = WindowMgr::get_instace().get_renderer();

  renderer->render_color(0xFF, 0, 0);
  renderer->render_rect(m_x, m_y, m_width, m_height);
}

void Button::update()
{
  if (WindowMgr::get_instace().m_mouse1_pressed)
  {
    if (m_event_func && is_in_bounds(WindowMgr::get_instace().m_mouse_x, WindowMgr::get_instace().m_mouse_y))
      m_event_func();
  }
}

void Button::set_position(const uint32_t x, const uint32_t y)
{
  m_x = x;
  m_y = y;
}

void Button::on_click(std::function<void()> event)
{
  m_event_func = event;
}

bool Button::is_in_bounds(int x, int y)
{
  return (x > m_x && x < m_x + (int)m_width && y > m_y && y < m_y + (int)m_height);
}