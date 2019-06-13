#include <functional>
#include <iostream>
#include <vector>

#include "Game.hpp"
#include "solutions.hpp"

int main() {
  // Create game and set high speed
  Game game;
  game.step_delay(Game::seconds(0.1f));

  // Levels and their strategy functions
  std::vector<std ::pair<std::string, std::function<void(Bob&)>>> levels;
  levels.emplace_back("maps/level1.map", solutions::level1);
  levels.emplace_back("maps/level2.map", solutions::level2);
  levels.emplace_back("maps/level3.map", solutions::level3);
  levels.emplace_back("maps/level4.map", solutions::level4);
  levels.emplace_back("maps/level5.map", solutions::level5);
  levels.emplace_back("maps/level6.map", solutions::level6);
  levels.emplace_back("maps/level7.map", solutions::level7);

  // Load and run level after level
  for (auto& [map, strategy] : levels) {
    try {
      game.load_map(map);
      auto bob = game.get_bob();
      strategy(*bob);
    } catch (GameOver& e) {
      std::cout << "Game over on " + map + "!\n" << e.what() << std::endl;
    }
  }
}
