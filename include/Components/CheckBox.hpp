#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "WindowComponent.hpp"
#include <functional>

class CheckBox : public WindowComponent
{
public:
public:
  CheckBox(const uint32_t x, const uint32_t y, const bool checked, const std::string &label);

  void update() override;
  void render() override;
  void set_position(const uint32_t x, const uint32_t y) override;
  int get_x() override;
  int get_y() override;

  bool is_enabled() const;

  void on_click(std::function<void()> func);

  bool is_in_bounds(int x, int y);

private:
private:
  bool m_is_checked{false};

  uint32_t m_width{16};
  uint32_t m_height{16};

  std::string m_label;
  // void (*m_event_func)(){nullptr};
  std::function<void()> m_event_func;
};

#endif