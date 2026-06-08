#ifndef SCROLLAREA_HPP
#define SCROLLAREA_HPP

#include "Compositor.hpp"
#include "Renderer.hpp"
#include "WindowComponent.hpp"
#include <sstream>
#include <SDL2/SDL_image.h>

class ScrollArea : public WindowComponent
{
public:
public:
  ScrollArea(int x, int y, uint16_t width, uint16_t height);
  ~ScrollArea();

  void update() override;
  void render() override;

  void add_component(WindowComponent *component);

private:

  uint16_t m_texture_width{0};
  uint16_t m_texture_height{0};

  SDL_Texture *m_texture{nullptr};

  std::vector<WindowComponent *> m_ui_components;

private:

};

#endif