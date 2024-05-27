#ifndef WINDOWCOMPONENT_HPP
#define WINDOWCOMPONENT_HPP

#include "../Component.hpp"

class WindowComponent : public Component
{
public:
  virtual void set_position(const uint32_t x, const uint32_t y)
  {
    m_x = x;
    m_y = y;
  }
  virtual int get_x()
  {
    return m_x;
  };
  virtual int get_y()
  {
    return m_y;
  };
  virtual void add_event(void *func) {}
};

#endif