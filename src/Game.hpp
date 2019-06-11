#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <thread>

#include "Bob.hpp"
#include "Map.hpp"

class Game {
 public:
  Game();
  ~Game();

  void load_map(const std::string& file_path);
  std::shared_ptr<Bob> get_bob();
  void check_state();

 private:
  friend void window_handler(Game*);
  std::unique_ptr<std::thread> m_thread;
  bool m_running;
  std::shared_ptr<Map> m_map;
  std::shared_ptr<Bob> m_bob;
};

class GameOver : public std::exception {
 public:
  inline GameOver(std::string msg) : m_msg(std::move(msg)) {}
  inline const char* what() const noexcept override { return m_msg.c_str(); }

  private:
  std::string m_msg;
};
