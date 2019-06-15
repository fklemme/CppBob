#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <exception>
#include <memory>
#include <string>
#include <thread>

#include "Bob.hpp"
#include "Map.hpp"

class Game {
 public:
  // Loads a new map. The game will discard previous Bob instances.
  void load_map(const std::string &file_path);

  // Places Bob on the map and returns a shared pointer.
  [[nodiscard]] std::shared_ptr<Bob> place_bob();

  using seconds = std::chrono::duration<float>;  // float seconds

  // Get step delay. This is the amount of time Bob needs to take an action.
  [[nodiscard]] inline seconds step_delay() const { return m_step_delay; }

  // Set step delay. This is the amount of time Bob needs to take an action.
  inline void step_delay(seconds s) {
    if (s > seconds(0.0f)) m_step_delay = s;
  }

  // This function is called by Bob instances.
  // Checks the current game state and throws GameOver on certain conditions.
  void check_state();

  // Thread management in constructor / destructor
  Game();
  ~Game();
  // Disallow copying a Game instance
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;
  // Moving should be fine
  Game(Game &&) = default;
  Game &operator=(Game &&) = default;

 private:
  // Handle drawing the window in an own thread.
  friend void window_handler(Game *game);
  std::unique_ptr<std::thread> m_thread;
  // Have a GL context created in the main thread initially.
  // This is just a workaround for a Windows specific problem as described here:
  // https://en.sfml-dev.org/forums/index.php?topic=22131.msg156596#msg156596
  std::unique_ptr<sf::Context> m_context;
  // Game state members:
  bool m_running = true;
  seconds m_step_delay{1.0f};
  std::shared_ptr<Map> m_map;
  std::shared_ptr<Bob> m_bob;
};

class GameOver : public std::exception {
 public:
  inline GameOver(std::string msg) : m_msg(std::move(msg)) {}
  [[nodiscard]] inline const char *what() const noexcept override { return m_msg.c_str(); }

 private:
  std::string m_msg;
};
