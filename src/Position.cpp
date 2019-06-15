#include "Position.hpp"

bool Position::operator==(const Position &that) const { return row == that.row && col == that.col; }

bool Position::operator!=(const Position &that) const { return row != that.row || col != that.col; }

bool Position::operator<(const Position &that) const {
  if (row != that.row) return row < that.row;
  return col < that.col;
}

std::size_t distance(const Position &a, const Position &b) {
  std::size_t row_dist = a.row > b.row ? a.row - b.row : b.row - a.row;
  std::size_t col_dist = a.col > b.col ? a.col - b.col : b.col - a.col;
  return row_dist + col_dist;
}
