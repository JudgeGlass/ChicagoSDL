#ifndef MINIMIZE_BAR_HPP
#define MINIMIZE_BAR_HPP

#include <map>
#include <memory>

#include "Button.hpp"
#include "Compositor.hpp"
#include "Window.hpp"
#include "WindowComponent.hpp"

class Window;
class MinimizeBar : public WindowComponent
{
public:
public:
  MinimizeBar();

  void update() override;
  void render() override;

  void link_window(Window *window);
  void remove_window(Window *window);

private:
private:
  int m_window_width{0};

  std::map<std::shared_ptr<Button>, Window *> m_windows;
};

#endif