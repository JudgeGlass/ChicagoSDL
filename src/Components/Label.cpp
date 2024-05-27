#include "Components/Label.hpp"

Label::Label(const uint32_t x, const uint32_t y, const std::string &label, const uint32_t color)
    : m_label(label), m_color(color)
{
  m_x = x;
  m_y = y;
}

void Label::render()
{
  Renderer *renderer = WindowMgr::get_instace().get_renderer();
  renderer->draw_string(m_x, m_y, m_label, m_color, 1);
}

void Label::update() {}

void Label::set_position(const uint32_t x, const uint32_t y)
{
  m_x = x;
  m_y = y;
}

int Label::get_x()
{
  return m_x;
}

int Label::get_y()
{
  return m_y;
}