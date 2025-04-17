#include "TextBox.hpp"

TextBox::TextBox(int x, int y, uint16_t cols) : m_cols(cols)
{
  m_x = x;
  m_y = y;

  m_width = (cols * 8) + 10;
  m_height = (1 * 8) + 10;

  m_start_index = 0;
  m_end_index = cols;
}

TextBox::~TextBox() {}

void TextBox::update()
{
  check_focus();
  if (!m_is_primary || !m_enabled)
  {
    return;
  }
  std::string key = WindowMgr::get_instance().get_text_input();
  bool backspace = WindowMgr::get_instance().backspace_pressed();
  // bool left = WindowMgr::get_instance().is_key_pressed(SDLK_LEFT);
  // bool right = WindowMgr::get_instance().is_key_pressed(SDLK_RIGHT);
  if (!key.empty())
  {
    m_text.append(key);
    if (m_text.size() > m_cols)
    {
      m_cursor_pos = m_cols;
      m_end_index++;
      m_start_index++;
    }
    else
    {
      m_cursor_pos++;
    }
  }

  if (backspace && !m_text.empty())
  {
    m_text.pop_back();
    if (m_text.size() > m_cols)
    {
      m_start_index--;
      m_end_index--;
    }
    else
    {
      m_cursor_pos--;
    }
  }
}
void TextBox::render()
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();
  Compositor::get_instance().draw_input_buffer(m_x, m_y, m_cols, 1);
  if (m_text.size() > m_cols)
  {
    renderer->draw_string(m_x + 5, m_y + 5, m_text.substr(m_start_index, m_end_index - 1), 0, 1);
  }
  else
  {
    renderer->draw_string(m_x + 5, m_y + 5, m_text, 0, 1);
  }

  renderer->render_color(0, 0, 0);
  renderer->render_rect((m_cursor_pos + 1) * 8 + m_x + 5, m_y + 13, 8, 2, true);

  if (!m_enabled)
  {
    renderer->render_backdrop(m_x, m_y, m_width, m_height);
  }
}

void TextBox::check_focus()
{
  int mouse_x = WindowMgr::get_instance().get_mouse_pos().first;
  int mouse_y = WindowMgr::get_instance().get_mouse_pos().second;
  if (WindowMgr::get_instance().m_mouse1_pressed &&
      Component::is_in_bounds(mouse_x, mouse_y, m_x, m_y, m_width, m_height))
  {
    m_is_primary = true;
  }
  if (WindowMgr::get_instance().m_mouse1_pressed &&
      !Component::is_in_bounds(mouse_x, mouse_y, m_x, m_y, m_width, m_height))
  {
    m_is_primary = false;
  }
}

std::string TextBox::get_text() const
{
  return m_text;
}

void TextBox::set_text(std::string text)
{
  m_text = text;
}