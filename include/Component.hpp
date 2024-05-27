#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "WindowMgr.hpp"

class Component
{
public:
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