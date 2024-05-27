#include "WindowMgr.hpp"

void WindowMgr::init(const uint16_t window_width, const uint16_t window_height, const std::string &window_title)
{
  this->m_window_width = window_width;
  this->m_window_height = window_height;
  this->m_window_title = window_title;

  sdl_init();
  m_renderer = std::make_unique<Renderer>(m_sdl_window, m_sdl_renderer);
}

WindowMgr::~WindowMgr()
{
  SDL_DestroyWindow(m_sdl_window);
  SDL_DestroyRenderer(m_sdl_renderer);
}

void WindowMgr::sdl_init()
{
  auto sdl_init_status = SDL_Init(SDL_INIT_EVERYTHING);
  if (sdl_init_status < 0)
  {
    log("Failed to init SDL!: " + std::string(SDL_GetError()), true);
  }

  m_sdl_window = SDL_CreateWindow(
      m_window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_window_width, m_window_height, 0);

  if (!m_sdl_window)
  {
    log("Failed to create window!: " + std::string(SDL_GetError()), true);
  }

  m_sdl_renderer = SDL_CreateRenderer(m_sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!m_sdl_renderer)
  {
    log("Failed to create renderer!: " + std::string(SDL_GetError()), true);
  }

  SDL_SetWindowBordered(m_sdl_window, SDL_FALSE);
  SDL_StartTextInput();
  SDL_SetWindowFullscreen(m_sdl_window, SDL_WINDOW_FULLSCREEN);

  m_loop = true;
}

void WindowMgr::loop()
{
  while (m_loop)
  {
    sdl_event();
    update();
    render();

    m_mouse1_pressed = false;
    m_char_removed = false;
    m_right_arrow = false;
    m_left_arrow = false;
    m_up_arrow = false;
    m_down_arrow = false;
  }
}

void WindowMgr::sdl_event()
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
    {
      m_loop = false;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
      if (e.button.button == SDL_BUTTON_LEFT)
      {
        m_mouse1_pressed = true;
      }
    }
    else if (e.type == SDL_TEXTINPUT)
    {
      m_text_input = std::string(e.text.text);
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE)
    {
      m_char_removed = true;
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP)
    {
      m_up_arrow = true;
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN)
    {
      m_down_arrow = true;
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
    {
      m_left_arrow = true;
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
    {
      m_right_arrow = true;
    }
  }
}

void WindowMgr::update()
{
  SDL_GetMouseState(&m_mouse_x, &m_mouse_y);
  for (const auto &comp : m_components)
  {
    if (comp == m_current_focus.top())
    {
      comp->update();
    }
  }
}

void WindowMgr::render()
{
  SDL_SetRenderDrawColor(m_sdl_renderer, 0x00, 0x80, 0x80, 0);
  SDL_RenderClear(m_sdl_renderer);
  for (const auto &comp : m_components)
  {
    comp->render();
  }
  SDL_RenderPresent(m_sdl_renderer);
}

Renderer *WindowMgr::get_renderer()
{
  return m_renderer.get();
}

void WindowMgr::add_component(Component *component)
{
  m_components.push_back(component);
}

void WindowMgr::remove_component(Component *component)
{
  if (m_current_focus.top() == component)
  {
    m_current_focus.pop();
  }
  m_components.erase(std::remove(m_components.begin(), m_components.end(), component), m_components.end());
}

void WindowMgr::log(const std::string &msg, bool _exit)
{
  std::cout << msg << std::endl;
  if (_exit)
  {
    exit(-1);
  }
}

void WindowMgr::close()
{
  m_loop = false;
}

void WindowMgr::toggle_border()
{
  if (m_show_border)
  {
    SDL_SetWindowBordered(m_sdl_window, SDL_TRUE);
  }
  else
  {
    SDL_SetWindowBordered(m_sdl_window, SDL_FALSE);
  }

  m_show_border = !m_show_border;
}

void WindowMgr::set_focus(Component *component)
{
  m_current_focus.push(component);
}

char WindowMgr::pop_key_buffer()
{
  char key = m_key_buffer.back();
  m_key_buffer.pop_back();
  return key;
}

std::string WindowMgr::get_text_input()
{
  std::string text = m_text_input;
  m_text_input.clear();
  return text;
}

bool WindowMgr::backspace_pressed()
{
  return m_char_removed;
}