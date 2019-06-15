#pragma once

#include <memory>

#include "Map.hpp"

// Directions Bob can look to
enum Orientation { up, right, down, left };

class Game;  // forward declaration

// Bob, the game entity to program. :)
class Bob {
 public:
  // --- Actions ---

  // Moves Bob one tile in the facing direction.
  void move();

  // Turns Bob right in a 90° angle.
  void turn_right();

  // Turns Bob left in a 90° angle.
  void turn_left();

  // Marks the tile at Bob's current location.
  void set_mark();

  // Removes mark from the tile Bob's standing on.
  void remove_mark();

  // --- Sensors ---

  // Returns true if Bob is facing a wall.
  [[nodiscard]] bool wall_in_front() const;

  // Returns true if Bob is standing on a marked tile.
  [[nodiscard]] bool on_marked_tile() const;

  // --- Other information ---

  // Gets a shared pointer to the map Bob is placed on.
  [[nodiscard]] inline std::shared_ptr<const Map> map() const { return m_map; }

  // Returns Bobs current position.
  [[nodiscard]] inline const Position &position() const { return m_position; }

  // Returns Bobs current orientation (facing direction).
  [[nodiscard]] inline Orientation orientation() const { return m_orientation; }

  // Returns Bobs sprite. Used by Game for visualization.
  [[nodiscard]] inline const sf::Sprite &sprite() const { return m_sprite; }

  // Constructors, copy and move operations
  Bob(Game *game, std::shared_ptr<Map> map, Position starting_position);
  ~Bob() = default;
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
