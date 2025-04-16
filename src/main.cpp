#include "Button.hpp"
#include "CheckBox.hpp"
#include "Graphics.hpp"
#include "InputBuffer.hpp"
#include "Label.hpp"
#include "MinimizeBar.hpp"
#include "ProgressBar.hpp"
#include "TextBox.hpp"
#include "Window.hpp"
#include "WindowMgr.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <thread>

#define SDL_MAIN_HANDLED

float progress = 0.f;

void do_work()
{
  while (true)
  {
    for (int i = 0; i < 100; i++)
    {
      progress = i / 100.f;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
}

void build_window()
{
  WindowMgr *window_manager = &WindowMgr::get_instance();
  WindowMgr::get_instance().init(800 * 2, 480 * 2, "ChicagoSDL");

  MinimizeBar mb;
  window_manager->add_minimize_bar(&mb);

  Window w(0, 0, 800 * 2, 480 * 2, "ChicagoSDL Test - Copyright (c) Hunter Wilcox", true);
  window_manager->add_component(&w);
  w.on_minimize([]() { SDL_MinimizeWindow(WindowMgr::get_instance().get_sdl_window()); });

  w.on_close([&]() { window_manager->close(); });

  CheckBox ch(30, 30, false, "Enable Buffer");
  ch.on_click([&]() { window_manager->toggle_border(); });
  w.add_component(&ch);

  TextBox tb(30, 120, 20);
  // tb.disable();
  w.add_component(&tb);

  ProgressBar pb(30, 440, 1200, 32);
  pb.set_callback_function([&]() { pb.step(progress); });
  w.add_component(&pb);
  ProgressBar pb2(30, 480, 1200, 32);
  pb2.set_callback_function([&]() { pb2.step(progress); });
  w.add_component(&pb2);

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
  w1.on_minimize([&]() { w1.hide(); });
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
  for (int i = 0; i < 200; i++)
  {
    g.set_pixel(i, 30, 0xFFFFFF);
    g.set_pixel(i, 31, 0xFFFFFF);
    g.set_pixel(i, 32, 0xFFFFFF);
    g.set_pixel(i, 33, 0xFFFFFF);
    g.set_pixel(i, 34, 0xFFFFFF);
    g.set_pixel(i, sin(4 * i) * 20, 0x00FF00);
  }
  w.add_component(&g);

  std::thread work(do_work);
  work.detach();
  WindowMgr::get_instance().loop();
}

int main()
{
  build_window();
  std::cout << "(ChicagoSDL exit)" << std::endl;
  return 0;
}