#include <Button.hpp>
#include <Label.hpp>
#include <TextBox.hpp>
#include <Window.hpp>
#include <WindowMgr.hpp>
#include <memory>

WindowMgr *wm;

std::unique_ptr<Window> main_window;
std::unique_ptr<TextBox> text_box;
std::unique_ptr<Button> button;
std::unique_ptr<Label> label;

int main()
{
  wm = &WindowMgr::get_instance();
  wm->init(800, 600, "Test Window");

  main_window = std::make_unique<Window>(0, 0, 800, 600, "Window1", true);
  main_window->on_close([&]() { wm->close(); });
  wm->add_component(main_window.get());

  button = std::make_unique<Button>(800 / 2 - 64, 600 / 2 - 32, 64, 32, "Button");
  button->on_click([&]() { text_box->set_text("Clicked!"); });
  main_window->add_component(button.get());

  text_box = std::make_unique<TextBox>(800 / 2 - 76, 600 / 2 + 5, 10);
  main_window->add_component(text_box.get());

  label = std::make_unique<Label>(800 / 2 - 180, 600 / 2 + 10, "Text Box! -->", 0x000000);
  main_window->add_component(label.get());

  wm->loop();

  return 0;
}