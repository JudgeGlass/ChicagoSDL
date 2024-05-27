#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Components/Button.hpp"
#include "Compositor.hpp"
#include "WindowMgr.hpp"

#include <memory>
#include <vector>

class Window : public Component
{
public:
public:
  Window(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const std::string &title);
  // ~Window();

  void render() override;
  void update() override;

  void add_component(WindowComponent *component);

private:
private:
  uint32_t m_width;
  uint32_t m_height;
  std::string m_title;

  std::unique_ptr<Button> m_exit_btn;
  std::unique_ptr<Button> m_minimize_btn;

  std::vector<WindowComponent *> m_ui_components;
};

#endif