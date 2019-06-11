#include <iostream>

#include "Game.hpp"

// Steuere Bob zum Ziel!
void strategy(Bob& bob) {
  // Nach rechts laufen
  bob.turn_right();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  // Dann nach unten laufen
  bob.turn_right();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
  bob.move();
}

int main() {
  // Erstelle Spiel (zeichnet das Level)
  Game game;
  // Lade Karte
  game.load_map("maps/level1.map");
  // Platziere Bob
  auto bob = game.get_bob();

  try {
    // Strategie ausführen
    strategy(*bob);
  } catch (GameOver& e) {
    std::cout << "Game over!\n" << e.what() << std::endl;
  }
}
