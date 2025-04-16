#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Button.hpp"
#include "Compositor.hpp"
#include "MinimizeBar.hpp"
#include "WindowMgr.hpp"

#include <functional>
#include <memory>
#include <vector>

class Window : public Component
{
public:
public:
  Window(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const std::string &title,
      const bool is_main_window = false);
  ~Window();

  void render() override;
  void update() override;

  void add_component(WindowComponent *component);
  void on_close(std::function<void()> event);
  void on_minimize(std::function<void()> event);
  void close();

  void enable_minimize_button();
  void disable_minimize_button();
  void set_main_window();

  bool is_main_window() const;

  std::string get_title() const
  {
    return m_title;
  }

private:
  uint32_t m_width;
  uint32_t m_height;
  std::string m_title;

  std::unique_ptr<Button> m_exit_btn;
  std::unique_ptr<Button> m_minimize_btn;

  std::vector<WindowComponent *> m_ui_components;

  std::function<void()> m_on_close;
  std::function<void()> m_on_minimize;

  bool m_window_grabbed{false};
  int m_window_prev_x{0};
  int m_window_prev_y{0};

  bool m_main_window{false};

  int m_clicked_x{0};
  int m_clicked_y{0};

  int m_animation_sx{0};
  int m_animation_sy{0};
  int m_animation_w{0};
  int m_animation_h{0};

private:
  void move();
  void minimize_animation();
};

#endif