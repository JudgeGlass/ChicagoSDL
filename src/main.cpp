#include "Components/Button.hpp"
#include "Components/CheckBox.hpp"
#include "Components/Label.hpp"
#include "Window.hpp"
#include "WindowMgr.hpp"
#include <SDL2/SDL.h>
#include <iostream>

#define SDL_MAIN_HANDLED

void build_window()
{
  WindowMgr *window_manager = &WindowMgr::get_instace();

  Window w(0, 0, 800, 480, "ChicagoSDL Test - Copyright (c) Hunter Wilcox");
  window_manager->add_component(&w);

  CheckBox ch(30, 30, false, "Enable Buffer");
  ch.on_click([&]() { window_manager->toggle_border(); });
  w.add_component(&ch);

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
    std::cout << "Is check box enable?: " << ch.is_enabled() << std::endl;
  });
  // clang-format on
  w.add_component(&c);

  Label l(20, 100, "abcdefghijklmnopqrstuvwxyz", 0xFFFFFF);
  w.add_component(&l);

  WindowMgr::get_instace().init(800, 480, "ChicagoSDL");
  WindowMgr::get_instace().loop();
}

int main()
{
  build_window();
  std::cout << "(ChicagoSDL exit)" << std::endl;
  return 0;
}