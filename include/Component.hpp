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

  int get_x() const
  {
    return m_x;
  }

  int get_y() const
  {
    return m_y;
  }

  int get_width() const
  {
    return m_width;
  }

  int get_height() const
  {
    return m_height;
  }

  void hide()
  {
    m_is_hidden = true;
  }

  void show()
  {
    m_is_hidden = false;
  }

protected:
  int m_x;
  int m_y;
  uint32_t m_width;
  uint32_t m_height;
  bool m_is_hidden{false};

private:
private:
};

#endif
