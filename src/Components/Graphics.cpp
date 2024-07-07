#include "Components/Graphics.hpp"

Graphics::Graphics(const uint32_t x, const uint32_t y, const uint32_t bitmap_width, const uint32_t bitmap_height)
    : m_width(bitmap_width), m_height(bitmap_height)
{
  m_x = x;
  m_y = y;

  m_bitmap = new uint8_t[m_width * m_height];

  m_bitmap_texture = SDL_CreateTexture((SDL_Renderer *)WindowMgr::get_instance().get_renderer()->get_sdl_renderer(),
      SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

  clear_buffer();
}

Graphics::~Graphics()
{
  delete[] m_bitmap;
}

void Graphics::update() {}

void Graphics::render()
{
  auto renderer = (SDL_Renderer *)WindowMgr::get_instance().get_renderer()->get_sdl_renderer();

  SDL_Rect dst;
  dst.x = m_x;
  dst.y = m_y;
  dst.w = m_width;
  dst.h = m_height;

  SDL_RenderCopy(renderer, m_bitmap_texture, NULL, &dst);
}

void Graphics::set_pixel(int x, int y, int color)
{
  if (x >= 0 && x < m_width && y >= 0 && y < m_height)
  {
    m_bitmap[x + y * m_width] = color;
  }

  int texture_pitch = 0;
  void *texture_pixels = NULL;
  SDL_LockTexture(m_bitmap_texture, NULL, &texture_pixels, &texture_pitch);
  memcpy(texture_pixels, m_bitmap, m_width * m_height);
  SDL_UnlockTexture(m_bitmap_texture);
}

bool Graphics::is_enabled() const {}

void Graphics::on_click(std::function<void()> func) {}

void Graphics::clear_buffer()
{
  for (int i = 0; i < m_width * m_height; i++)
  {
    m_bitmap[i] = 0;
  }
}
