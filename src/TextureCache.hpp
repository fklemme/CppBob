#pragma once

#include <SFML/Graphics.hpp>
#include <map>

enum class Texture { bob, empty, start, destination, wall };

class TextureCache {
 public:
  [[nodiscard]] static TextureCache &instance();
  [[nodiscard]] inline const sf::Texture &get(Texture t) const {
    return m_textures.at(t);
  }

 private:
  TextureCache();
  ~TextureCache() = default;

 public:
  TextureCache(const TextureCache &) = delete;
  TextureCache &operator=(const TextureCache &) = delete;
  TextureCache(TextureCache &&) = delete;
  TextureCache &operator=(TextureCache &&) = delete;

 private:
  std::map<Texture, sf::Texture> m_textures;
};
