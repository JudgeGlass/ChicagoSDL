#include "Components/Button.hpp"
#include "Components/CheckBox.hpp"
#include "Components/Graphics.hpp"
#include "Components/InputBuffer.hpp"
#include "Components/Label.hpp"
#include "Components/TextBox.hpp"
#include "Window.hpp"
#include "WindowMgr.hpp"
#include <SDL2/SDL.h>
#include <iostream>

#define SDL_MAIN_HANDLED

void build_window()
{
  WindowMgr *window_manager = &WindowMgr::get_instance();
  WindowMgr::get_instance().init(800 * 2, 480 * 2, "ChicagoSDL");

  Window w(0, 0, 800 * 2, 480 * 2, "ChicagoSDL Test - Copyright (c) Hunter Wilcox");
  window_manager->add_component(&w);

  w.on_close([&]() { window_manager->close(); });

  CheckBox ch(30, 30, false, "Enable Buffer");
  ch.on_click([&]() { window_manager->toggle_border(); });
  w.add_component(&ch);

  TextBox tb(30, 120, 20);
  tb.disable();
  w.add_component(&tb);

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

  InputBuffer buff(260, 60, 25, 12);
  w.add_component(&buff);

  Window w1(150, 50, 250, 150, "Dialog");
  w1.on_close([&]() { window_manager->remove_component(&w1); });
  w1.enable_minimize_button();
  window_manager->add_component(&w1);
  Label dialog(8, 70, "This is a dialog example!", 0);
  w1.add_component(&dialog);
  Button ok(250 - 5 - 70, 150 - 30, 70, 25, "OK");
  ok.on_click([&]() { w1.close(); });
  w1.add_component(&ok);

  Label l2(20, 190, "Graphics Buffer:", 0);
  w.add_component(&l2);
  Graphics g(20, 200, 200, 200);
  for (int i = 0; i < 60; i++)
  {
    g.set_pixel(i, i, 0xFFFFFF - i * sin(i));
  }
  w.add_component(&g);

  WindowMgr::get_instance().loop();
}

int main()
{
  build_window();
  std::cout << "(ChicagoSDL exit)" << std::endl;
  return 0;
}