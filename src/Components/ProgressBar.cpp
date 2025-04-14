#include "Components/ProgressBar.hpp"

ProgressBar::ProgressBar(int x, int y, uint16_t width, uint16_t height)
{
  m_x = x;
  m_y = y;

  m_width = width;
  m_height = height;
}
ProgressBar::~ProgressBar() {}

void ProgressBar::update() {}

void ProgressBar::render()
{
  int w = 100;
  int h = 32;
  int x = m_x;
  int y = m_y;
  float p = 0.0f;
  Compositor::get_instance().draw_progress_bar(x, y, w, h, p);
}

float ProgressBar::get_percentage() const {}

void ProgressBar::step(float amount) {}