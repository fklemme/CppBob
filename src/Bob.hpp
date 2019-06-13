#pragma once

#include <memory>

#include "Map.hpp"

enum Orientation { up, right, down, left };

class Game;

class Bob {
 public:
  // Move instructions
  void move();
  void turn_right();
  void turn_left();

  // Sensor checks
  [[nodiscard]] bool wall_in_front() const;

  // Other information
  [[nodiscard]] inline const Position &position() const { return m_position; }
  [[nodiscard]] inline Orientation orientation() const { return m_orientation; }
  [[nodiscard]] inline const sf::Sprite &sprite() const { return m_sprite; }

  // Constructor, copy and move operations
  Bob(Game *game, std::shared_ptr<Map> map, Position starting_position);
  // Disallow copying
  Bob(const Bob &) = delete;
  Bob &operator=(const Bob &) = delete;
  // Disallow moving, as Game holds a pointer to instance
  Bob(Bob &&) = delete;
  Bob &operator=(Bob &&) = delete;

 private:
  Game *m_game;
  std::shared_ptr<Map> m_map;
  Position m_position;
  Orientation m_orientation;
  sf::Sprite m_sprite;
};
