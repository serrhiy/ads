#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "config.hpp"
#include "draw.hpp"
#include <functional>

namespace utils {
  using events_t = std::vector<
    std::tuple<
      std::function<bool(const sf::Event&)>,
      std::function<void(sf::RenderWindow&, bool)>,
      std::string
    >
  >;
  sf::RenderWindow& manageWindow(
    sf::RenderWindow& window,
    unsigned width,
    unsigned height,
    const char* title
  );
  void pollEvents(
    sf::RenderWindow& window,
    const std::function<bool(const sf::Event&)> triger,
    const std::function<void(sf::RenderWindow&)> callback
  );
  sf::Font getFont(const std::string& path = config::FONT_PATH);
  std::function<bool(const sf::Event&)> onKeyDown(const sf::Keyboard::Key& key);
  void clearWindow(sf::RenderWindow& window, const sf::Color& color);
  size_t getFistOutVertex(const matrix_t& matrix);
}
