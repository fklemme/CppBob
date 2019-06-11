#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Position {
  std::size_t row;
  std::size_t col;
};

class Map {
 public:
  inline static const float tile_size_x = 64;
  inline static const float tile_size_y = 64;

 public:
  Map(const std::vector<std::vector<char>> &char_map);

  inline std::size_t height() const { return m_sprite_map.size(); }
  inline std::size_t width() const { return m_sprite_map[0].size(); }
  inline const auto &char_map() const { return m_char_map; }
  inline const auto &sprite_map() const { return m_sprite_map; }

  Position starting_position() const;
  inline char char_at(Position p) const { return m_char_map[p.row][p.col]; }

 private:
  std::vector<std::vector<char>> m_char_map;
  std::vector<std::vector<sf::Sprite>> m_sprite_map;
};
