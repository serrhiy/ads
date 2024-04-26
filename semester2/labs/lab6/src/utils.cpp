#include <SFML/Graphics.hpp>
#include <functional>
#include "config.hpp"
#include "utils.hpp"

using utils::events_t;

sf::RenderWindow& utils::manageWindow(
  sf::RenderWindow& window, unsigned width, unsigned height, const char* title
) {
  sf::ContextSettings settings;
  settings.antialiasingLevel = config::SMOOTHING;
  window.create(
    sf::VideoMode{ width, height },
    title,
    sf::Style::Default,
    settings
  );
  window.setKeyRepeatEnabled(false);
  return window;
}

size_t utils::getFistOutVertex(const matrix_t& matrix) {
  const size_t size{ matrix.size() };
  for (size_t i{ 0 }; i < size; i++) {
    for (size_t j{ 0 }; j < size; j++) {
      if (matrix[i][j] && i != j) return i;
    }
  }
  return SIZE_MAX;
}

std::function<bool(const sf::Event&)> utils::onKeyDown(const sf::Keyboard::Key& key) {
  return [&key](const sf::Event& event) {
    return (
      event.type == sf::Event::KeyPressed &&
      event.key.code == key
    );
  };
}

void utils::clearWindow(sf::RenderWindow& window, const sf::Color& color) {
  window.clear(config::BACKGROUND_COLOR);
  window.display();
}

sf::Font utils::getFont(const std::string& path) {
  static sf::Font font;
  static bool isDefined = false;
  if (isDefined) return font;
  if (!font.loadFromFile(path)) {
    throw std::runtime_error{ "Cannot load font!" };
  }
  isDefined = true;
  return font;
}

const std::vector globalEvents {
  std::make_pair(
    [](const sf::Event& event) {
      const bool first{ event.type == sf::Event::Closed };
      const bool second{
        event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape
      };
      return first || second;
    },
    [](sf::RenderWindow& window){
      window.close();
    }
  ),
};

void leftCornerText(sf::RenderWindow& window, const std::string& txt) {
  const sf::Font font{ utils::getFont() };
  sf::Text text{ txt, font, config::TEXT_SIZE };
  text.setFillColor(config::LINE_COLOR);
  const sf::Vector2f pos{ 5.f, 5.f };
  text.setPosition(pos - text.getGlobalBounds().getPosition());
  window.draw(text);
  window.display();
}

void utils::pollEvents(
  sf::RenderWindow& window,
  const std::function<bool(const sf::Event&)> triger,
  const std::function<void(sf::RenderWindow&)> callback
) {
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      for (const auto &[triger, callback] : globalEvents) {
        if (triger(event)) callback(window);
      }
      if (triger(event)) callback(window);
    }
  }
}
