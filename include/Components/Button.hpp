#ifndef BuTTON_HPP
#define BUTTON_HPP

#include "../Renderer.hpp"
#include "WindowComponent.hpp"

class Button : public WindowComponent
{
public:
  void update() override;
  void render() override;
};

#endif