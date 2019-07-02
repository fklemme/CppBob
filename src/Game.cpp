#include "Game.hpp"

#include <filesystem>
#include <fstream>
#include <optional>
#include <stdexcept>

void window_handler(Game* game) {
  // Create window in thread
  sf::RenderWindow window(sf::VideoMode(640, 480), "CppBob");
  std::shared_ptr<Map> current_map = nullptr;

  while (game->m_running) {
    // Handle events
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) game->m_running = false;
    }

    // Update window and view on changed map
    if (current_map != game->m_map) {
      current_map = game->m_map;
      if (current_map != nullptr) {
        window.setTitle("CppBob - " + current_map->title());
        // Figure out suitable window size
        auto desktop = sf::VideoMode::getDesktopMode();
        const float max_width = desktop.width * 0.8f;
        const float max_height = desktop.height * 0.8f;
        float target_width = Map::tile_size_x * current_map->width();
        float target_height = Map::tile_size_y * current_map->height();
        float scale_ratio = std::min(max_width / target_width, max_height / target_height);
        if (scale_ratio < 1.0f) {
          // Scale down, keeping aspect ratio
          target_width = target_width * scale_ratio;
          target_height = target_height * scale_ratio;
        }
        // Update size and position
        window.setSize(sf::Vector2u(target_width, target_height));
        window.setPosition(
            sf::Vector2i((desktop.width - target_width) / 2, (desktop.height - target_height) / 2));
        // Update view
        sf::View view(sf::FloatRect(0.0f, 0.0f, Map::tile_size_x * current_map->width(),
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

void Game::load_map(const std::string& file_path) {
  if (!std::filesystem::exists(file_path)) throw std::logic_error("File not found: " + file_path);

  // Load map data from file
  std::ifstream in(file_path);
  std::optional<std::string> title;
  std::vector<std::vector<char>> map_data;
  for (std::string line; std::getline(in, line);) {
    if (line.empty()) continue;
    if (line.substr(0, 2) == "//" && !title) {
      std::size_t start = 2;
      while (start < line.size() && line[start] == ' ') ++start;
      if (start < line.size()) title = line.substr(start);
    } else
      map_data.emplace_back(line.begin(), line.end());
  }

  // Throw away old bob, if any
  m_bob.reset();

  // Create new map
  m_map = std::make_shared<Map>(title ? *title : file_path, map_data);
}

std::shared_ptr<Bob> Game::place_bob() {
  if (m_bob == nullptr) {
    Position start_pos = m_map->starting_position();
    m_bob = std::make_shared<Bob>(this, m_map, start_pos);
  }
  return m_bob;
}

void Game::check_state() {
  if (!m_running) throw GameOver("Game has been stopped!");

  if (m_bob != nullptr) {
    if (m_map->tile(m_bob->position()) == 'd')
      throw GameOver("Bob reached the destination! Good job! :)");
  }
}

Game::Game() {
  m_thread = std::make_unique<std::thread>(window_handler, this);
  m_context = std::make_unique<sf::Context>();
}

Game::~Game() {
  // m_running = false;
  m_thread->join();
}
