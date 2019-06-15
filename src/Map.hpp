#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Position.hpp"

// The game map
class Map {
 public:
  inline static const float tile_size_x = 64;
  inline static const float tile_size_y = 64;

 public:
  // Get character that represents tile at given row and column.
  [[nodiscard]] char tile(std::size_t row, std::size_t col) const;

  // Get character that represents tile at given Position.
  [[nodiscard]] char tile(const Position &p) const;

  // Set character at given row and column.
  void tile(std::size_t row, std::size_t col, char c);

  // Set character at given Position.
  void tile(const Position &p, char c);

  // Get map title
  [[nodiscard]] inline const std::string &title() const { return m_title; }

  // Get map height (in number of tiles)
  [[nodiscard]] inline std::size_t height() const { return m_sprite_map.size(); }

  // Get map width (in number of tiles)
  [[nodiscard]] inline std::size_t width() const { return m_sprite_map[0].size(); }

  // Get character map. Each character represents one type of tile.
  [[nodiscard]] inline const auto &char_map() const { return m_char_map; }

  // Get sprite map. Used by Game to visualize the map.
  [[nodiscard]] inline const auto &sprite_map() const { return m_sprite_map; }

  // Get starting position "s". Used by Game to place Bob.
  [[nodiscard]] Position starting_position() const;

  // Contructor, called by Game::load_map
  Map(std::string title, std::vector<std::vector<char>> char_map);

 private:
  std::string m_title;
  std::vector<std::vector<char>> m_char_map;
  std::vector<std::vector<sf::Sprite>> m_sprite_map;
};
