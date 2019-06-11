#pragma once

#include "Map.hpp"

enum Orientation { up, right, down, left };

class Game;

class Bob {
 public:
  Bob(Game* game_ptr, std::shared_ptr<Map> map, Position starting_position);

  // Movements
  void move();
  void turn_right();
  void turn_left();

  // Sensor checks
  bool wall_in_front() const;

  inline const Position& position() const { return m_position; }
  inline Orientation orientation() const { return m_orientation; }
  inline const sf::Sprite& sprite() const { return m_sprite; }

 private:
  Game* m_game_ptr;
  std::shared_ptr<Map> m_map;
  Position m_position;
  Orientation m_orientation;
  sf::Sprite m_sprite;
};
