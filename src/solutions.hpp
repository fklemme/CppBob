#pragma once

#include <algorithm>
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

inline void level9(Bob& bob) {
  // Visualize path finding algorithm with marks on the map
  constexpr bool debug_visualize = false;

  auto& map = *bob.map();
  Position start = bob.position();
  Position destination{map.height(), map.width()};  // initially off map

  // Find destination "d"
  for (std::size_t row = 0; row < map.height(); ++row) {
    for (std::size_t col = 0; col < map.width(); ++col) {
      if (map.tile(row, col) == 'd') destination = {row, col};
    }
  }
  assert(destination.row < map.height() && destination.col < map.width());

  if constexpr (debug_visualize) {
    // Clear all marks that are initially on the map
    for (std::size_t row = 0; row < map.height(); ++row) {
      for (std::size_t col = 0; col < map.width(); ++col) {
        if (map.tile(row, col) == 'm') const_cast<Map&>(map).tile(row, col, '_');
      }
    }
  }

  // --- Find path from start to destination ---
  // Compare function to get nearest Position to destination in priority queue
  auto dist_compare = [&destination](const Position& a, const Position& b) {
    return distance(a, destination) > distance(b, destination);
  };
  // Positions to check next
  std::priority_queue<Position, std::vector<Position>, decltype(dist_compare)> positions(
      dist_compare);
  // Checked positions, and how did we get there?
  std::map<Position, Position> predecessors;
  predecessors.emplace(start, start);  // let start be its own predecessor, used later

  // Add start as first position to check
  positions.push(start);

  // Route to destination
  std::vector<Position> dest_route;

  // Path finding algorithm
  while (!positions.empty()) {
    // Check next position in queue
    Position current = positions.top();
    positions.pop();

    // If we reached the destination...
    if (current == destination) {
      // Build route backwards from destination to start
      Position p = current;
      // Only for start, its predecessor will be itself
      while (p != predecessors[p]) {
        dest_route.push_back(p);
        p = predecessors[p];
      }
      // Reverse order: Now from start to destination (start itself is not in route)
      std::reverse(dest_route.begin(), dest_route.end());
      // End path finding!
      break;
    }

    if constexpr (debug_visualize) {
      // Mark current position for visualization (debugging)
      const_cast<Map&>(map).tile(current, 'm');
      std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    // Add ajecent positions that are not already checked
    Position up{current.row - 1, current.col};
    Position down{current.row + 1, current.col};
    Position left{current.row, current.col - 1};
    Position right{current.row, current.col + 1};
    for (auto& p : {up, down, left, right}) {
      // TODO: Add boundary checks
      if (map.tile(p) != 'w' && predecessors.count(p) == 0) {
        positions.push(p);
        predecessors.emplace(p, current);
      }
    }
  }  // end of path finding

  if constexpr (debug_visualize) {
    // Clear all marks, again
    for (std::size_t row = 0; row < map.height(); ++row) {
      for (std::size_t col = 0; col < map.width(); ++col) {
        if (map.tile(row, col) == 'm') const_cast<Map&>(map).tile(row, col, '_');
      }
    }

    // Visualize route with marks
    auto mark_route = dest_route;
    mark_route.pop_back();  // don't override the destination itself
    for (auto& p : mark_route) const_cast<Map&>(map).tile(p, 'm');
  }

  // Follow the route to destination
  for (auto& p : dest_route) {
    // Figure out target direction
    Orientation target_direction;
    if (p.row == bob.position().row - 1)
      target_direction = Orientation::up;
    else if (p.row == bob.position().row + 1)
      target_direction = Orientation::down;
    else if (p.col == bob.position().col - 1)
      target_direction = Orientation::left;
    else
      target_direction = Orientation::right;

    // Rotate Bob accordingly
    while (bob.orientation() != target_direction) {
      if ((bob.orientation() + 1) % 4 == target_direction)
        bob.turn_right();
      else
        bob.turn_left();
    }

    // Move one step
    bob.move();
  }
}

}  // namespace solutions
