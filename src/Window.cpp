#include "Window.hpp"

Window::Window(
    const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const std::string &title)
    : m_width(width), m_height(height), m_title(title)
{
  m_x = x;
  m_y = y;

  m_exit_btn = std::make_unique<Button>((m_x + m_width) - 8 - 16, m_y + 8, 16, 16, "X");
  m_minimize_btn = std::make_unique<Button>((m_x + m_width) - 12 - 16 - 16, m_y + 8, 16, 16, "_");

  m_exit_btn->on_click([]() { WindowMgr::get_instace().close(); });
}

void Window::add_component(WindowComponent *component)
{
  m_ui_components.push_back(component);
}

void Window::render()
{
  Renderer *renderer = WindowMgr::get_instace().get_renderer();

  Compositor::get_instace().draw_window_frame(m_x, m_y, m_width, m_height);

  renderer->draw_string_shadowed(m_x + 8, m_y + 12, m_title, 0xFFFFFF, 1);

  m_exit_btn->render();
  renderer->render_texture(0, m_exit_btn->get_x(), m_exit_btn->get_y(), 1, 16);

  m_minimize_btn->render();
  renderer->render_texture(2, m_minimize_btn->get_x(), m_minimize_btn->get_y(), 1, 16);

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