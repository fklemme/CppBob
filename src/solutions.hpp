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
  // Move down
  bob.turn_right();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
}

inline void level2(Bob& bob) {
  // Move down
  bob.turn_right();
  bob.turn_right();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  // Move to the right
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

}  // namespace solutions
