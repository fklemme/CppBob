#include <iostream>

#include "Game.hpp"

// Choose the map to be loaded
const std::string map = "resources/maps/level1.map";

// Guide Bob to the destination!
// Have a look at Bob.hpp for some documentation.
void strategy(Bob& bob) {
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

int main() {
  // Create game and load map
  Game game;
  game.load_map(map);

  // Place Bob at starting location, returns a shared pointer
  auto bob_ptr = game.place_bob();

  // Speed up game for bigger maps (smaller = faster)
  // game.step_delay(Game::seconds(0.25f));

  try {
    // Execute strategy that guides Bob to the destination
    strategy(*bob_ptr);

    std::cout << "Strategy ended without reaching destination. :(" << std::endl;
  } catch (GameOver& e) {
    std::cout << "Game over!\n" << e.what() << std::endl;
  }
}
