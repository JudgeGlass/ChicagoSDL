#include "Window.hpp"

Window::Window(
    const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const std::string &title)
    : m_width(width), m_height(height), m_title(title)
{
  m_x = x;
  m_y = y;
}

void Window::add_component(WindowComponent *component)
{
  m_ui_components.push_back(component);
}

void Window::render()
{
  Renderer *renderer = WindowMgr::get_instace().get_renderer();

  renderer->render_color(0, 0, 0);
  renderer->render_rect(m_x, m_y, m_width, m_height);

  for (const auto &comp : m_ui_components)
  {
    comp->render();
  }
}

void Window::update()
{
  for (const auto &comp : m_ui_components)
  {
    comp->update();
  }
}