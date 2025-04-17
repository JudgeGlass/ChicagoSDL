#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "Compositor.hpp"
#include "Renderer.hpp"
#include "WindowComponent.hpp"

class TextBox : public WindowComponent
{
public:
public:
  TextBox(int x, int y, uint16_t cols);
  ~TextBox();

  void update() override;
  void render() override;

  void set_text(std::string text);
  std::string get_text() const;

private:
  uint16_t m_cols;
  uint16_t m_width;
  uint16_t m_height;

  uint16_t m_start_index;
  uint16_t m_end_index;
  uint16_t m_cursor_pos;

  std::string m_text;

private:
  void check_focus();
};

#endif