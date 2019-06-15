#pragma once

#include <cstddef>

// Represents a position on the map.
struct Position {
  std::size_t row;
  std::size_t col;

  // Compare positions
  [[nodiscard]] bool operator==(const Position &that) const;
  [[nodiscard]] bool operator!=(const Position &that) const;

  // For ordered containers like map
  [[nodiscard]] bool operator<(const Position &that) const;
};

[[nodiscard]] std::size_t distance(const Position &a, const Position &b);
