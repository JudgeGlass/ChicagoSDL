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

  m_loop = true;
}

void WindowMgr::loop()
{
  while (m_loop)
  {
    sdl_event();
    update();
    render();
  }
}

void WindowMgr::sdl_event()
{
  m_mouse1_pressed = false;
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      m_loop = false;
    }

    if (e.key.keysym.sym == SDLK_ESCAPE)
    {
      m_loop = false;
    }

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
      if (e.button.button == SDL_BUTTON_LEFT)
      {
        m_mouse1_pressed = true;
      }
    }
  }
}

void WindowMgr::update()
{
  SDL_GetMouseState(&m_mouse_x, &m_mouse_y);
  for (const auto &comp : m_components)
  {
    comp->update();
  }
}

void WindowMgr::render()
{
  SDL_SetRenderDrawColor(m_sdl_renderer, 0xFF, 0xFF, 0xFF, 0);
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

void WindowMgr::log(const std::string &msg, bool _exit)
{
  std::cout << msg << std::endl;
  if (_exit)
  {
    exit(-1);
  }
}