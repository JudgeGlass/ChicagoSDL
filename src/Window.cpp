#include "Window.hpp"

Window::Window() {}

void Window::add_component(WindowComponent *component)
{
  m_ui_components.push_back(component);
}

void Window::render()
{
  Renderer *renderer = WindowMgr::get_instace().get_renderer();

  renderer->render_color(0, 0, 0);
  renderer->render_rect(15, 15, 100, 100);

  for (const auto &comp : m_ui_components)
  {
    comp->render();
  }
}

void Window::update() {}