#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <memory>
#include <string>
#include <thread>

#include "Bob.hpp"
#include "Map.hpp"

class Game {
 public:
  // Thread management in constructor / destructor
  Game();
  ~Game();

  // Disallow copying a Game instance
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;
  // Moving should be fine
  Game(Game &&) = default;
  Game &operator=(Game &&) = default;

  void load_map(const std::string &file_path);
  [[nodiscard]] std::shared_ptr<Bob> get_bob();
  void check_state();

  using seconds = std::chrono::duration<float>;  // float seconds
  [[nodiscard]] inline seconds step_delay() const { return m_step_delay; }
  inline void step_delay(seconds s) {
    if (s > seconds(0.0f)) m_step_delay = s;
  }

 private:
  // Handle drawing window in an own thread.
  friend void window_handler(Game *game);
  std::unique_ptr<std::thread> m_thread;
  // Have a GL context created in the main thread initially.
  // This is just a workaround for a Windows specific problem as described here:
  // https://en.sfml-dev.org/forums/index.php?topic=22131.msg156596#msg156596
  std::unique_ptr<sf::Context> m_context;
  bool m_running = true;
  seconds m_step_delay{1.0f};
  std::shared_ptr<Map> m_map;
  std::shared_ptr<Bob> m_bob;
};

class GameOver : public std::exception {
 public:
  inline GameOver(std::string msg) : m_msg(std::move(msg)) {}
  [[nodiscard]] inline const char *what() const noexcept override {
    return m_msg.c_str();
  }

 private:
  std::string m_msg;
};
