#include "TextureCache.hpp"

TextureCache& TextureCache::instance() {
  static TextureCache tc;
  return tc;
}

TextureCache::TextureCache() {
  // Load all textures upfront so that pointers will not get invalidated later on.
  m_textures[Texture::bob].loadFromFile("resources/images/bob.png");
  m_textures[Texture::empty].loadFromFile("resources/images/empty.png");
  m_textures[Texture::start].loadFromFile("resources/images/start.png");
  m_textures[Texture::destination].loadFromFile("resources/images/destination.png");
  m_textures[Texture::wall].loadFromFile("resources/images/wall.png");
  m_textures[Texture::mark].loadFromFile("resources/images/mark.png");
}
