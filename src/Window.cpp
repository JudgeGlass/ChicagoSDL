#include "Window.hpp"

Window::Window(
    const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const std::string &title)
    : m_width(width), m_height(height), m_title(title)
{
  m_x = x;
  m_y = y;

  m_exit_btn = std::make_unique<Button>((m_x + m_width) - 5 - 16, m_y + 5, 16, 16, "X");
  m_minimize_btn = std::make_unique<Button>((m_x + m_width) - 5 - 16 - 16 - 5, m_y + 5, 16, 16, "_");

  m_exit_btn->on_click([]() { WindowMgr::get_instace().close(); });
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

  m_exit_btn->render();
  m_minimize_btn->render();

  for (const auto &comp : m_ui_components)
  {
    comp->render();
  }
}

void Window::update()
{
  m_exit_btn->update();
  m_minimize_btn->update();

  for (const auto &comp : m_ui_components)
  {
    comp->update();
  }
}