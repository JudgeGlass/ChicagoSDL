#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include "Compositor.hpp"
#include "Renderer.hpp"
#include "WindowComponent.hpp"

#include <functional>
#include <thread>

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

  void set_callback_function(std::function<void()> funct);

private:
  float m_percentage;
  uint16_t m_width;
  uint16_t m_height;

  std::function<void()> m_callback = nullptr;

private:
};

#endif