#include "Components/Button.hpp"

void Button::render()
{
  Renderer *renderer = WindowMgr::get_instace().get_renderer();

  renderer->render_color(0xFF, 0, 0);
  renderer->render_rect(50, 50, 100, 100);
}

void Button::update() {}