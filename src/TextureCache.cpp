#include "TextureCache.hpp"

TextureCache& TextureCache::instance() {
  static TextureCache tc;
  return tc;
}

TextureCache::TextureCache() {
  // Load all textures upfront so that pointers
  // will not get invalidated later on.
  m_textures[Texture::bob].loadFromFile("images/bob.png");
  m_textures[Texture::empty].loadFromFile("images/empty.png");
  m_textures[Texture::start].loadFromFile("images/start.png");
  m_textures[Texture::destination].loadFromFile("images/destination.png");
  m_textures[Texture::wall].loadFromFile("images/wall.png");
  m_textures[Texture::mark].loadFromFile("images/mark.png");
}
