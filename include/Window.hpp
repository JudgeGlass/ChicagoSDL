#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Component.hpp"
#include "Components/WindowComponent.hpp"
#include "WindowMgr.hpp"

#include <vector>

class Window : public Component
{
public:
public:
  Window(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const std::string &title);

  void render() override;
  void update() override;

  void add_component(WindowComponent *component);

private:
private:
  uint32_t m_width;
  uint32_t m_height;
  std::string m_title;

  std::vector<WindowComponent *> m_ui_components;
};

#endif