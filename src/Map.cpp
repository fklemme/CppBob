#include "Map.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>

#include "TextureCache.hpp"

namespace {
const std::vector<char> valid_chars = {'_', 's', 'd', 'w', 'm'};

const sf::Texture &char_to_texture(char c) {
  switch (c) {
    case '_':
      return TextureCache::instance().get(Texture::empty);
    case 's':
      return TextureCache::instance().get(Texture::start);
    case 'd':
      return TextureCache::instance().get(Texture::destination);
    case 'w':
      return TextureCache::instance().get(Texture::wall);
    case 'm':
      return TextureCache::instance().get(Texture::mark);
    default:
      throw std::logic_error(std::string("Unknow map char: ") + c);
  }
}
}  // namespace

char Map::tile(std::size_t row, std::size_t col) const {
  if (row >= height() || col >= width()) throw std::range_error("Position out of range!");

  return m_char_map[row][col];
}

char Map::tile(const Position &p) const { return tile(p.row, p.col); }

void Map::tile(std::size_t row, std::size_t col, char c) {
  if (row >= height() || col >= width()) throw std::range_error("Position out of range!");

  if (std::find(valid_chars.begin(), valid_chars.end(), c) == valid_chars.end())
    throw std::logic_error(std::string("Illegal character: ") + c);

  m_char_map[row][col] = c;
  m_sprite_map[row][col].setTexture(char_to_texture(c));
}

void Map::tile(const Position &p, char c) { tile(p.row, p.col, c); }

Position Map::starting_position() const {
  for (std::size_t row = 0; row < height(); ++row) {
    for (std::size_t col = 0; col < width(); ++col) {
      if (m_char_map[row][col] == 's') return {row, col};
    }
  }
  throw std::logic_error("No starting position in map!");
}

Map::Map(std::string title, std::vector<std::vector<char>> char_map)
    : m_title(std::move(title)), m_char_map(std::move(char_map)) {
  // Check minimal size
  if (m_char_map.empty()) throw std::logic_error("Empty map data!");

  // Check valid chars
  for (auto &char_line : m_char_map) {
    for (char c : char_line) {
      if (std::find(valid_chars.begin(), valid_chars.end(), c) == valid_chars.end())
        throw std::logic_error(std::string("Illegal character in map data: ") + c);
    }
  }

  // Check dimensions
  const auto row_length = m_char_map[0].size();
  for (auto &line : m_char_map) {
    if (line.size() != row_length) throw std::logic_error("Inconsistent line lengths in map data!");
  }

  // Create sprite map
  m_sprite_map.resize(m_char_map.size());
  for (std::size_t row = 0; row < m_char_map.size(); ++row) {
    auto &char_line = m_char_map[row];
    for (std::size_t col = 0; col < row_length; ++col) {
      sf::Sprite tile;
      tile.setTexture(char_to_texture(char_line[col]));
      tile.setPosition(tile_size_x * col, tile_size_y * row);
      m_sprite_map[row].push_back(std::move(tile));
    }
  }
}
