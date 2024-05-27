#ifndef WINDOWCOMPONENT_HPP
#define WINDOWCOMPONENT_HPP

#include "../Component.hpp"

class WindowComponent : public Component
{
public:
  virtual void set_position(const uint32_t x, const uint32_t y) {}
  virtual void add_event(void *func) {}
};

#endif