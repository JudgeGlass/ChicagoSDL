#include "Components/Button.hpp"
#include "Window.hpp"
#include "WindowMgr.hpp"
#include <iostream>

#define SDL_MAIN_HANDLED

void build_window()
{
  WindowMgr *window_manager = &WindowMgr::get_instace();

  Window w(0, 0, 800, 480, "ChicagoSDL Test - Copyright (c) Hunter Wilcox");
  window_manager->add_component(&w);

  Button b(60, 60, 50, 25, "EXIT");
  // clang-format off
  b.on_click([&]() 
  {
    window_manager->close();
  });
  // clang-format on
  w.add_component(&b);

  Button c(115, 60, 50, 25, "OK");
  // clang-format off
  c.on_click([&]() 
  {
    std::cout << "Pressed OK" << std::endl;
  });
  // clang-format on
  w.add_component(&c);

  WindowMgr::get_instace().init(800, 480, "ChicagoSDL");
  WindowMgr::get_instace().loop();
}

int main()
{
  build_window();
  std::cout << "(ChicagoSDL exit)" << std::endl;
  return 0;
}