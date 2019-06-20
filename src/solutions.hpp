#pragma once

#include <algorithm>
#include <cassert>
#include <map>
#include <set>
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

// ----- Level 9: Generic path finding with A* algorithm -----
// Visualize path finding algorithm with marks on the map
constexpr bool debug_visualize = true;
const auto debug_step_delay = std::chrono::milliseconds(250);

// Based on https://en.wikipedia.org/wiki/A*_search_algorithm#Pseudocode
std::vector<Position> reconstruct_path(const std::map<Position, Position>& cameFrom,
                                       Position current) {
  std::vector<Position> total_path = {current};
  while (cameFrom.count(current)) {
    current = cameFrom.at(current);
    total_path.push_back(current);
  }
  std::reverse(total_path.begin(), total_path.end());  // start to goal
  return total_path;
}

// Based on https://en.wikipedia.org/wiki/A*_search_algorithm#Pseudocode
std::vector<Position> A_Star(const Map& map, const Position& start, const Position& goal) {
  // Can be used as "Infinity"
  const int max_distance = map.height() * map.width();

  // The set of nodes already evaluated
  std::set<Position> closedSet;

  // The set of currently discovered nodes that are not evaluated yet.
  // Initially, only the start node is known.
  std::set<Position> openSet = {start};  // TODO: use priority queue

  // For each node, which node it can most efficiently be reached from.
  // If a node can be reached from many nodes, cameFrom will eventually
  // contain the most efficient previous step.
  std::map<Position, Position> cameFrom;

  // For each node, the cost of getting from the start node to that node.
  std::map<Position, int> gScore;  // default value of Infinity

  // The cost of going from start to start is zero.
  gScore[start] = 0;

  // For each node, the total cost of getting from the start node to the goal
  // by passing by that node. That value is partly known, partly heuristic.
  std::map<Position, int> fScore;  // default value of Infinity

  // For the first node, that value is completely heuristic.
  fScore[start] = distance(start, goal);

  // Helper to get "Infinity" as default when accessing a map
  auto get = [&max_distance](auto& map, const Position& p) {
    if (!map.count(p)) map.emplace(p, max_distance);
    return map[p];
  };

  while (!openSet.empty()) {
    // current := the node in openSet having the lowest fScore[] value
    auto current = *std::min_element(
        // openSet.begin(), openSet.end(), // breadth first
        openSet.rbegin(), openSet.rend(),  // depth first
        [&](const Position& a, const Position& b) { return get(fScore, a) < get(fScore, b); });

    if (current == goal) return reconstruct_path(cameFrom, current);

    if constexpr (debug_visualize) {
      // Mark current position for visualization (debugging)
      const_cast<Map&>(map).tile(current, 'm');
      std::this_thread::sleep_for(debug_step_delay);
    }

    openSet.erase(current);
    closedSet.insert(current);

    // Neighbors of current
    Position up{current.row - 1, current.col};
    Position down{current.row + 1, current.col};
    Position left{current.row, current.col - 1};
    Position right{current.row, current.col + 1};
    for (auto& neighbor : {up, down, left, right}) {
      if (map.tile(neighbor) == 'w') continue;  // Neighbor is wall and cannot be moved to

      if (closedSet.count(neighbor)) continue;  // Ignore the neighbor which is already evaluated

      // The distance from start to a neighbor
      const int tentative_gScore = get(gScore, current) + 1;

      if (!openSet.count(neighbor))  // Discover a new node
        openSet.insert(neighbor);
      else if (tentative_gScore >= get(gScore, neighbor))
        continue;

      // This path is the best until now. Record it!
      cameFrom[neighbor] = current;
      gScore[neighbor] = tentative_gScore;
      fScore[neighbor] = tentative_gScore + distance(neighbor, goal);
    }
  }

  return {};  // no path found
}

inline void level9(Bob& bob) {
  auto& map = *bob.map();
  Position start = bob.position();
  Position destination{map.height(), map.width()};  // initially off map

  // Find destination "d" on map
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

  // Use path finding algorithm to find best path to destination
  auto route = A_Star(map, start, destination);

  if constexpr (debug_visualize) {
    // Clear all marks, again
    for (std::size_t row = 0; row < map.height(); ++row) {
      for (std::size_t col = 0; col < map.width(); ++col) {
        if (map.tile(row, col) == 'm') const_cast<Map&>(map).tile(row, col, '_');
      }
    }

    // Visualize route with marks
    auto mark_route = route;
    mark_route.pop_back();  // don't override the destination itself
    for (auto& position : mark_route) const_cast<Map&>(map).tile(position, 'm');
  }

  // Follow the route to destination
  route.erase(route.begin());  // ignore first position: Bob is on that tile
  for (auto& postion : route) {
    // Figure out target direction
    Orientation target_direction;
    if (postion.row == bob.position().row - 1)
      target_direction = Orientation::up;
    else if (postion.row == bob.position().row + 1)
      target_direction = Orientation::down;
    else if (postion.col == bob.position().col - 1)
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
