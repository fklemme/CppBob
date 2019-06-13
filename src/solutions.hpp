#pragma once

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

}  // namespace solutions
