#ifndef LABEL_HPP
#define LABEL_HPP

#include "Components/WindowComponent.hpp"

class Label : public WindowComponent
{
public:
public:
  Label(const uint32_t x, const uint32_t y, const std::string &label, const uint32_t color);

  void update() override;
  void render() override;
  void set_position(const uint32_t x, const uint32_t y) override;
  int get_x() override;
  int get_y() override;

  bool is_enabled() const;

  bool is_in_bounds(int x, int y);

private:
private:
  std::string m_label;

  uint32_t m_color{0};
};

#endif