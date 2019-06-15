#pragma once

#include <cassert>
#include <cmath>
#include <map>
#include <queue>
#include <vector>

#include "Bob.hpp"

namespace solutions {

inline void level1(Bob& bob) {
  // Move to the right
  bob.turn_right();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  // Then move down
  bob.turn_right();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
}

inline void level2(Bob& bob) {
  // Move down first
  bob.turn_right();
  bob.turn_right();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  // Then move to the right
  bob.turn_left();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
}

inline void level3(Bob& bob) {
  // Face right direction
  bob.turn_right();
  // Forever...
  while (true) {
    // Turn right when facing wall
    if (bob.wall_in_front()) bob.turn_right();
    // And move on
    bob.move();
  }
}

inline void level4(Bob& bob) {
  // Face right direction
  bob.turn_right();
  // Forever...
  while (true) {
    if (bob.wall_in_front()) {
      // Walk around obstacle
      bob.turn_left();
      bob.move();
      bob.turn_right();
      bob.move();
      bob.move();
      bob.turn_right();
      bob.move();
      bob.turn_left();
    } else
      bob.move();
  }
}

inline void level5(Bob& bob) {
  // Face right direction
  bob.turn_right();

  // Helper function
  auto wall_to_the_right = [&]() {
    bob.turn_right();  // turn right for check
    bool wall = bob.wall_in_front();
    bob.turn_left();  // return to initial orientation
    return wall;
  };

  // Forever...
  while (true) {
    if (bob.wall_in_front()) {
      // Walk around obstacle
      bob.turn_left();
      bob.move();
      bob.turn_right();
      bob.move();
      while (wall_to_the_right()) bob.move();
      bob.turn_right();
      bob.move();
      bob.turn_left();
    } else
      bob.move();
  }
}

inline void level6(Bob& bob) {
  // Helpers
  auto try_move_left = [&]() {
    bob.turn_left();
    bob.move();
    if (bob.on_marked_tile())
      return true;  // success
    else {
      // recover
      bob.turn_right();
      bob.turn_right();
      bob.move();
      bob.turn_left();
      return false;  // no success
    }
  };
  auto try_move_front = [&]() {
    bob.move();
    if (bob.on_marked_tile())
      return true;  // success
    else {
      // recover
      bob.turn_right();
      bob.turn_right();
      bob.move();
      bob.turn_left();
      bob.turn_left();
      return false;  // no success
    }
  };
  auto try_move_right = [&]() {
    bob.turn_right();
    bob.move();
    if (bob.on_marked_tile())
      return true;  // success
    else {
      // recover
      bob.turn_left();
      bob.turn_left();
      bob.move();
      bob.turn_right();
      return false;  // no success
    }
  };

  while (true) {
    if (try_move_front()) {
      // nothing to do on success, we already moved
    } else if (try_move_left()) {
      // nothing to do on success, we already moved
    } else if (try_move_right()) {
      // nothing to do on success, we already moved
    } else
      return;  // give up
  }
}

inline void level7(Bob& bob) {
  // Helpers
  auto try_move_left = [&]() {
    bob.turn_left();
    if (bob.wall_in_front()) {
      bob.turn_right();  // recover
      return false;      // no success
    }
    bob.move();
    if (bob.on_marked_tile())
      return true;  // success
    else {
      // recover
      bob.turn_right();
      bob.turn_right();
      bob.move();
      bob.turn_left();
      return false;  // no success
    }
  };
  auto try_move_front = [&]() {
    if (bob.wall_in_front()) return false;  // no success
    bob.move();
    if (bob.on_marked_tile())
      return true;  // success
    else {
      // recover
      bob.turn_right();
      bob.turn_right();
      bob.move();
      bob.turn_left();
      bob.turn_left();
      return false;  // no success
    }
  };
  auto try_move_right = [&]() {
    bob.turn_right();
    if (bob.wall_in_front()) {
      bob.turn_left();  // recover
      return false;     // no success
    }
    bob.move();
    if (bob.on_marked_tile())
      return true;  // success
    else {
      // recover
      bob.turn_left();
      bob.turn_left();
      bob.move();
      bob.turn_right();
      return false;  // no success
    }
  };

  while (true) {
    if (try_move_front()) {
      // nothing to do on success, we already moved
    } else if (try_move_left()) {
      // nothing to do on success, we already moved
    } else if (try_move_right()) {
      // nothing to do on success, we already moved
    } else
      return;  // give up
  }
}

inline void level8(Bob& bob) {
  // Helpers
  auto try_move_left = [&]() {
    bob.turn_left();
    if (bob.wall_in_front()) {
      bob.turn_right();  // recover
      return false;      // no success
    }
    bob.move();
    return true;  // success
  };
  auto try_move_front = [&]() {
    if (bob.wall_in_front()) return false;  // no success
    bob.move();
    return true;  // success
  };
  auto try_move_right = [&]() {
    bob.turn_right();
    if (bob.wall_in_front()) {
      bob.turn_left();  // recover
      return false;     // no success
    }
    bob.move();
    return true;  // success
  };

  // Strategy: Almost choose the rightmost way
  while (true) {
    if (try_move_right() || try_move_front() || try_move_left()) {
      // nothing to do on success, we already moved
    } else {
      // turn around
      bob.turn_right();
      bob.turn_right();
    }
  }
}

// Helpers for level9
std::size_t distance(const Position& a, const Position& b) {
  std::size_t row_dist = a.row > b.row ? a.row - b.row : b.row - a.row;
  std::size_t col_dist = a.col > b.col ? a.col - b.col : b.col - a.col;
  return row_dist + col_dist;
}

bool operator<(const Position& a, const Position& b) {
  if (a.row != b.row) return a.row < b.row;
  if (a.row == b.row) return a.col < b.col;
}

inline void level9(Bob& bob) {
  auto& map = *bob.map();
  Position start = bob.position();
  Position destination{map.width(), map.height()};  // initial off map

  // Find destination "d"
  for (std::size_t row = 0; row < map.width(); ++row) {
    for (std::size_t col = 0; col < map.height(); ++col) {
      if (map.tile(row, col) == 'd') destination = {row, col};
    }
  }
  assert(destination.row < map.width() && destination.col < map.height());

  // --- Find path from start to destination ---
  // Compare function to get nearest Position to destination in priority queue
  auto dist_compare = [&destination](const Position& a, const Position& b) {
    return distance(a, destination) < distance(b, destination);
  };
  // Positions to check next
  std::priority_queue<Position, std::vector<Position>, decltype(dist_compare)> positions(
      dist_compare);
  // Checked positions, and how did we get there?
  std::map<Position, Position> predecessors;

  // Add start as first position to check
  positions.push(start);

  // Path finding algorithm
  while (!positions.empty()) {
    Position current = positions.top();
    positions.pop();

    if (current == destination) {
      // Reached destination
      // TODO
      break;
    }

    // Mark current position for visualization (debugging)
    const_cast<Map&>(map).tile(current, 'm');
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Add ajecent positions that are not already checked
    Position up{current.row, current.col - 1};
    Position down{current.row, current.col + 1};
    Position left{current.row - 1, current.col};
    Position right{current.row + 1, current.col};
    for (Position p : {up, down, left, right}) {
      // TODO: Add boundary checks
      if (map.tile(up) != 'w' && predecessors.count(up) == 0) {
        positions.push(up);
        predecessors.emplace(up, current);
      }
    }
  }
}

}  // namespace solutions
