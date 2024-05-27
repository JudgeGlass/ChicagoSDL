#ifndef WINDOWMGR_HPP
#define WINDOWMGR_HPP

#include <SDL2/SDL.h>
#include <inttypes.h>
#include <iostream>
#include <memory>
#include <string>

#include "Singleton.hpp"

class WindowMgr : public Singleton<WindowMgr>
{
public:
public:
  ~WindowMgr();
  void init(const uint16_t window_width, const uint16_t window_height, const std::string &window_title);
  void loop();

private:
  uint16_t m_window_width{800};
  uint16_t m_window_height{480};

  std::string m_window_title;

  bool m_loop{false};

  SDL_Window *m_sdl_window;
  SDL_Renderer *m_sdl_renderer;

private:
  void sdl_init();
  void sdl_event();
  void render();
  void update();
};

#endif