#include "Components/Button.hpp"
#include "Window.hpp"
#include "WindowMgr.hpp"
#include <iostream>

#define SDL_MAIN_HANDLED

int main()
{
  WindowMgr::get_instace().init(800, 480, "ChicagoSDL");

  Window w;
  WindowMgr::get_instace().add_component(&w);

  Button b;
  w.add_component(&b);

  WindowMgr::get_instace().loop();

  std::cout << "(ChicagoSDL exit)" << std::endl;
  return 0;
}