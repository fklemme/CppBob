#include "Bob.hpp"

#include "Game.hpp"
#include "TextureCache.hpp"

Bob::Bob(Game* game_ptr, std::shared_ptr<Map> map, Position starting_position)
    : m_game_ptr(game_ptr),
      m_map(map),
      m_position(starting_position),
      m_orientation(Orientation::up) {
  m_sprite.setTexture(TextureCache::instance().get(Texture::bob));
  m_sprite.setOrigin(Map::tile_size_x / 2, Map::tile_size_y / 2);
  m_sprite.setPosition((m_position.col + 0.5f) * Map::tile_size_x,
                       (m_position.row + 0.5f) * Map::tile_size_y);
}

void Bob::move() {
  std::this_thread::sleep_for(std::chrono::seconds(1));

  if (wall_in_front()) return;  // don't move

  if (m_orientation == Orientation::up && m_position.row > 0) {
    --m_position.row;
    m_sprite.move(0.0f, -Map::tile_size_y);
  } else if (m_orientation == Orientation::down &&
             m_position.row < m_map->height() - 1) {
    ++m_position.row;
    m_sprite.move(0.0f, Map::tile_size_y);
  } else if (m_orientation == Orientation::left && m_position.col > 0) {
    --m_position.col;
    m_sprite.move(-Map::tile_size_x, 0.0f);
  } else if (m_orientation == Orientation::right &&
             m_position.col < m_map->width() - 1) {
    ++m_position.col;
    m_sprite.move(Map::tile_size_x, 0.0f);
  }

  m_game_ptr->check_state();
}

void Bob::turn_right() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  m_orientation = (Orientation)((m_orientation + 1) % 4);
  m_sprite.setRotation(90.0f * m_orientation);
}

void Bob::turn_left() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  m_orientation = (Orientation)((m_orientation + 3) % 4);
  m_sprite.setRotation(90.0f * m_orientation);
}

bool Bob::wall_in_front() const {
  auto target_position = m_position;
  if (m_orientation == Orientation::up) {
    --target_position.row;
  } else if (m_orientation == Orientation::down) {
    ++target_position.row;
  } else if (m_orientation == Orientation::left) {
    --target_position.col;
  } else /* m_orientation == Orientation::right */ {
    ++target_position.col;
  }

  return m_map->char_at(target_position) == 'w';
}