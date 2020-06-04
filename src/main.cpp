#include <functional>
#include <iostream>
#include <vector>

#include "Game.hpp"
#include "solutions.hpp"

int main() {
  // Create game and set high speed
  Game game;
  game.step_delay(Game::seconds(0.25f));

  // Levels and their strategy functions
  const bool use_respective_solution = true;
  std::vector<std ::pair<std::string, std::function<void(Bob&)>>> levels;
  if (use_respective_solution) {
    levels.emplace_back("resources/maps/level1.map", solutions::level1);
    levels.emplace_back("resources/maps/level2.map", solutions::level2);
    levels.emplace_back("resources/maps/level3.map", solutions::level3);
    levels.emplace_back("resources/maps/level4.map", solutions::level4);
    levels.emplace_back("resources/maps/level5.map", solutions::level5);
    levels.emplace_back("resources/maps/level6.map", solutions::level6);
    levels.emplace_back("resources/maps/level7.map", solutions::level7);
    levels.emplace_back("resources/maps/level8.map", solutions::level8);
    levels.emplace_back("resources/maps/level9.map", solutions::level9);
  } else /* always use generic solution for level 9 */ {
    levels.emplace_back("resources/maps/level1.map", solutions::level9);
    levels.emplace_back("resources/maps/level2.map", solutions::level9);
    levels.emplace_back("resources/maps/level3.map", solutions::level9);
    levels.emplace_back("resources/maps/level4.map", solutions::level9);
    levels.emplace_back("resources/maps/level5.map", solutions::level9);
    levels.emplace_back("resources/maps/level6.map", solutions::level9);
    levels.emplace_back("resources/maps/level7.map", solutions::level9);
    levels.emplace_back("resources/maps/level8.map", solutions::level9);
    levels.emplace_back("resources/maps/level9.map", solutions::level9);
  }

  // Load and run level after level
  for (auto& [map, strategy] : levels) {
    try {
      game.load_map(map);
      auto bob_ptr = game.place_bob();
      strategy(*bob_ptr);
    } catch (GameOver& e) {
      std::cout << "Game over on " + map + "!\n" << e.what() << std::endl;
    }
  }
}
