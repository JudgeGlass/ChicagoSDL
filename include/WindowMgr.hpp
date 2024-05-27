#ifndef WINDOWMGR_HPP
#define WINDOWMGR_HPP

#include <SDL2/SDL.h>
#include <inttypes.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Component.hpp"
#include "Renderer.hpp"
#include "Singleton.hpp"

class Component;
class WindowMgr : public Singleton<WindowMgr>
{
  friend class Singleton<WindowMgr>;

public:
  bool m_mouse1_pressed{false};
  int m_mouse_x{0};
  int m_mouse_y{0};

public:
  ~WindowMgr();

  void init(const uint16_t window_width, const uint16_t window_height, const std::string &window_title);
  void loop();
  void log(const std::string &msg, bool _exit);
  void close();
  void add_component(Component *component);

  Renderer *get_renderer();

private:
  uint16_t m_window_width{800};
  uint16_t m_window_height{480};

  std::string m_window_title;

  bool m_loop{false};

  SDL_Window *m_sdl_window;
  SDL_Renderer *m_sdl_renderer;

  std::unique_ptr<Renderer> m_renderer;

  std::vector<Component *> m_components;

private:
  void sdl_init();
  void sdl_event();
  void render();
  void update();
};

#endif