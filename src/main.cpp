#include "WindowMgr.hpp"
#include <iostream>

#define SDL_MAIN_HANDLED

int main()
{
  WindowMgr::get_instace().init(800, 480, "ChicagoSDL");
  WindowMgr::get_instace().loop();
  std::cout << "(ChicagoSDL exit)" << std::endl;
  return 0;
}