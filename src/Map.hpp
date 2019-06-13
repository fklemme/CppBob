#pragma once

#include <SFML/Graphics.hpp>
#include <string>
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
  Map(std::string title, std::vector<std::vector<char>> char_map);

  [[nodiscard]] inline const std::string &title() const { return m_title; }
  [[nodiscard]] inline std::size_t height() const {
    return m_sprite_map.size();
  }
  [[nodiscard]] inline std::size_t width() const {
    return m_sprite_map[0].size();
  }
  [[nodiscard]] inline const auto &char_map() const { return m_char_map; }
  [[nodiscard]] inline const auto &sprite_map() const { return m_sprite_map; }

  [[nodiscard]] Position starting_position() const;
  [[nodiscard]] char tile(Position p) const;
  void tile(Position p, char c);

 private:
  std::string m_title;
  std::vector<std::vector<char>> m_char_map;
  std::vector<std::vector<sf::Sprite>> m_sprite_map;
};
