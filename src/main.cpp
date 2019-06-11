#include <iostream>

#include "Game.hpp"

// Guide Bob to the destination!
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
  game.load_map("maps/level1.map");
  // Place Bob at starting location, returns a pointer
  auto bob = game.get_bob();

  // Speed up game for bigger maps (smaller = faster)
  // game.step_delay(Game::seconds(0.25f));

  try {
    // Execute strategy that guides Bob to the destination
    strategy(*bob);

    std::cout << "Strategy ended without reaching destination. :(" << std::endl;
  } catch (GameOver& e) {
    std::cout << "Game over!\n" << e.what() << std::endl;
  }
}
