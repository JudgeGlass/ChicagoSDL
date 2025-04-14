#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include "../Compositor.hpp"
#include "../Renderer.hpp"
#include "Components/WindowComponent.hpp"

class ProgressBar : public WindowComponent
{
public:
public:
  ProgressBar(int x, int y, uint16_t width, uint16_t height);
  ~ProgressBar();

  void update() override;
  void render() override;

  float get_percentage() const;

  void step(float amount);

private:
  float percentage;
  uint16_t m_width;
  uint16_t m_height;

private:
};

#endif