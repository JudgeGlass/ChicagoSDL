#include "Components/Button.hpp"
#include "Components/CheckBox.hpp"
#include "Components/InputBuffer.hpp"
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

  w.on_close([&]() { window_manager->close(); });

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

  InputBuffer buff(260, 60, 25, 1);
  w.add_component(&buff);

  Window w1(150, 50, 250, 150, "Dialog");
  w1.on_close([&]() { window_manager->remove_component(&w1); });
  window_manager->add_component(&w1);
  Label dialog(8, 70, "This is a dialog example!", 0);
  w1.add_component(&dialog);
  Button ok(250 - 5 - 70, 150 - 30, 70, 25, "OK");
  ok.on_click([&]() { w1.close(); });
  w1.add_component(&ok);

  WindowMgr::get_instace().init(800, 480, "ChicagoSDL");
  WindowMgr::get_instace().loop();
}

int main()
{
  build_window();
  std::cout << "(ChicagoSDL exit)" << std::endl;
  return 0;
}