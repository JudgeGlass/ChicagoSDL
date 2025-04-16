#include "ProgressBar.hpp"

ProgressBar::ProgressBar(int x, int y, uint16_t width, uint16_t height)
{
  m_x = x;
  m_y = y;

  m_width = width;
  m_height = height;
}
ProgressBar::~ProgressBar() {}

void ProgressBar::update()
{
  if (m_callback)
  {
    m_callback();
  }
}

void ProgressBar::render()
{
  Compositor::get_instance().draw_progress_bar(m_x, m_y, m_width, m_height, m_percentage);
}

float ProgressBar::get_percentage() const
{
  return m_percentage;
}

void ProgressBar::step(float amount)
{
  m_percentage = amount;
}

void ProgressBar::set_callback_function(std::function<void()> funct)
{
  m_callback = funct;
}