#include "Components/Button.hpp"

Button::Button(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const std::string &text)
    : m_width(width), m_height(height), m_text(text)
{
  m_x = x;
  m_y = y;
}

void Button::render()
{
  Compositor::get_instace().draw_button_normal(m_x, m_y, m_width, m_height, m_text);
}

void Button::update()
{
  if (WindowMgr::get_instace().m_mouse1_pressed)
  {
    if (m_event_func && Component::is_in_bounds(WindowMgr::get_instace().m_mouse_x, WindowMgr::get_instace().m_mouse_y,
                            m_x, m_y, m_width, m_height))
      m_event_func();
  }
}

void Button::on_click(std::function<void()> event)
{
  m_event_func = event;
}