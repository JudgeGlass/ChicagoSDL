#include "Components/Button.hpp"
#include "Window.hpp"
#include "WindowMgr.hpp"
#include <iostream>

#define SDL_MAIN_HANDLED

void build_window()
{
  WindowMgr *window_manager = &WindowMgr::get_instace();

  Window w(5, 5, 600, 400, "Window 1");
  window_manager->add_component(&w);

  Button b(60, 60, 100, 25, "OK");
  // clang-format off
  b.on_click([&]() 
  {
    window_manager->close();
  });
  // clang-format on
  w.add_component(&b);

  WindowMgr::get_instace().init(800, 480, "ChicagoSDL");
  WindowMgr::get_instace().loop();
}

int main()
{
  build_window();
  std::cout << "(ChicagoSDL exit)" << std::endl;
  return 0;
}