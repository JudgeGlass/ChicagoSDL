#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "WindowMgr.hpp"

class Component
{
public:
  static bool is_in_bounds(int x, int y, int sx, int sy, int width, int height)
  {
    return (x > sx && x < sx + width && y > sy && y < sy + height);
  }

public:
  virtual void render() {};
  virtual void update() {};

protected:
  int m_x;
  int m_y;

private:
private:
};

#endif