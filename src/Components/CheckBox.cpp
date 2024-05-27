#include "Components/CheckBox.hpp"

CheckBox::CheckBox(const uint32_t x, const uint32_t y, const bool checked, const std::string &label)
    : m_is_checked(checked), m_label(label)
{
  m_x = x;
  m_y = y;
}

void CheckBox::render()
{
  Renderer *renderer = WindowMgr::get_instace().get_renderer();

  renderer->render_texture((m_is_checked ? 10 : 9), m_x, m_y, 1, 16);
  renderer->draw_string(m_x + 20, m_y + 4, m_label, 0, 1);
}

void CheckBox::update()
{
  if (WindowMgr::get_instace().m_mouse1_pressed)
  {
    if (is_in_bounds(WindowMgr::get_instace().m_mouse_x, WindowMgr::get_instace().m_mouse_y))
    {
      m_is_checked = !m_is_checked;
      if (m_event_func)
      {
        m_event_func();
      }
    }
  }
}

void CheckBox::set_position(const uint32_t x, const uint32_t y)
{
  m_x = x;
  m_y = y;
}

void CheckBox::on_click(std::function<void()> event)
{
  m_event_func = event;
}

bool CheckBox::is_in_bounds(int x, int y)
{
  return (x > m_x && x < m_x + (int)m_width && y > m_y && y < m_y + (int)m_height);
}

int CheckBox::get_x()
{
  return m_x;
}

int CheckBox::get_y()
{
  return m_y;
}

bool CheckBox::is_enabled() const
{
  return m_is_checked;
}