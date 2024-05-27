#include "WindowMgr.hpp"

void WindowMgr::init(const uint16_t window_width, const uint16_t window_height, const std::string &window_title)
{
  this->m_window_width = window_width;
  this->m_window_height = window_height;
  this->m_window_title = window_title;

  sdl_init();
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
    std::cerr << "Failed to init SDL!: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  m_sdl_window = SDL_CreateWindow(
      m_window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_window_width, m_window_height, 0);

  if (!m_sdl_window)
  {
    std::cerr << "Failed to create window!: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  m_sdl_renderer = SDL_CreateRenderer(m_sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!m_sdl_renderer)
  {
    std::cerr << "Failed to create renderer!: " << SDL_GetError() << std::endl;
    exit(-1);
  }

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
  }
}

void WindowMgr::update() {}

void WindowMgr::render() {}