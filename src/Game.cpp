#include "Game.hpp"

#include <fstream>

void window_handler(Game* game) {
  // Create window in thread
  sf::RenderWindow window(sf::VideoMode(640, 640), "CppBob");
  std::shared_ptr<Map> current_map = nullptr;

  while (game->m_running) {
    // Handle events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) game->m_running = false;
    }

    // Update view on changed map
    if (current_map != game->m_map) {
      current_map = game->m_map;
      if (current_map != nullptr) {
        sf::View view(sf::FloatRect(0.0f, 0.0f,
                                    Map::tile_size_x * current_map->width(),
                                    Map::tile_size_y * current_map->height()));
        window.setView(view);
      }
    }

    // --- Draw ---
    window.clear(sf::Color::White);

    // Draw map
    if (current_map != nullptr) {
      const auto& map = *current_map;
      for (std::size_t row = 0; row < map.height(); ++row) {
        for (std::size_t col = 0; col < map.width(); ++col) {
          window.draw(map.sprite_map()[row][col]);
        }
      }
    }

    // Draw Bob
    if (game->m_bob != nullptr) window.draw(game->m_bob->sprite());

    window.display();
  }

  window.close();
}

Game::Game() : m_running(true) {
  m_thread = std::make_unique<std::thread>(window_handler, this);
}

Game::~Game() {
  // m_running = false;
  m_thread->join();
}

void Game::load_map(const std::string& file_path) {
  // Throw away old bob, if any
  m_bob.reset();

  // Load map data
  std::ifstream in(file_path);
  std::vector<std::vector<char>> map_data;
  for (std::string line; std::getline(in, line);) {
    if (line.empty()) continue;
    if (line.substr(0, 2) == "//") continue;

    map_data.emplace_back(line.begin(), line.end());
  }

  // Create new map
  m_map = std::make_shared<Map>(map_data);
}

std::shared_ptr<Bob> Game::make_bob() {
  if (m_bob == nullptr) {
    Position start_pos = m_map->starting_position();
    m_bob = std::make_shared<Bob>(this, m_map, start_pos);
  }
  return m_bob;
}

void Game::check_state() {
  if (m_bob != nullptr) {
    const char pos_char = m_map->char_at(m_bob->position());
    if (pos_char == 'd') throw GameOver("You won! :)");
  }
}