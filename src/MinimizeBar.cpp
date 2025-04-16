#include "MinimizeBar.hpp"

MinimizeBar::MinimizeBar()
{
  m_x = 0;
  m_y = WindowMgr::get_instance().m_window_height - 32;
  m_window_width = WindowMgr::get_instance().m_window_width;
}

void MinimizeBar::update()
{
  for (const auto &[b, _] : m_windows)
  {
    b->update();
  }
}

void MinimizeBar::render()
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();

  renderer->render_color(0xFF0000);
  renderer->render_rect(m_x, m_y, m_window_width, 32, true);

  for (const auto &[b, _] : m_windows)
  {
    b->render();
  }
}

void MinimizeBar::link_window(Window *window)
{
  int num_windows = m_windows.size();

  std::shared_ptr<Button> b =
      std::make_shared<Button>(num_windows * 32 + 5, m_y + 3, 32, 32, std::to_string(num_windows));
  b->on_click([window]() { window->show(); });
  m_windows.insert({b, window});
}

void MinimizeBar::remove_window(Window *window)
{
  for (auto it = m_windows.begin(); it != m_windows.end(); it++)
  {
    if (it->second == window)
    {
      m_windows.erase(it);
      return;
    }
  }
}