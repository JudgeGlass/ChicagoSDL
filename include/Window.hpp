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
  Window();

  void render() override;
  void update() override;

  void add_component(WindowComponent *component);

private:
private:
  std::vector<WindowComponent *> m_ui_components;
};

#endif