#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include "config.hpp"

namespace vertex {
  struct Vertex {
    float x;
    float y;
    size_t index;
  };
  void draw(sf::RenderWindow& window, const vertex::Vertex& vertex, const sf::Color& color = config::LINE_COLOR);
  void lineConnect(
    sf::RenderWindow& window,
    const Vertex& from,
    const Vertex& to,
    bool shift = false,
    bool dir = true,
    const sf::Color& color = config::LINE_COLOR
  );
    void lineConnect(
    sf::RenderWindow& window,
    const vertex::Vertex& from,
    const vertex::Vertex& to,
    const std::string& txt,
    bool shift = false,
    bool dir = true,
    const sf::Color& color = config::LINE_COLOR
  );
  void arcConnect(
    sf::RenderWindow& window,
    const Vertex& from,
    const Vertex& to,
    const std::string& txt,
    bool dir = true,
    const sf::Color& color = config::LINE_COLOR
  );
  void arcConnect(
    sf::RenderWindow& window,
    const Vertex& from,
    const Vertex& to,
    bool dir = true,
    const sf::Color& color = config::LINE_COLOR
  );
  void loop(
    sf::RenderWindow& window,
    const Vertex& vertex,
    bool dir = true,
    const sf::Color& color = config::LINE_COLOR
  );
  void loop(
    sf::RenderWindow& window,
    const Vertex& vertex,
    const std::string& txt,
    bool dir = true,
    const sf::Color& color = config::LINE_COLOR
  );
  std::function<Vertex(size_t)> getVertexClosure(
    size_t count,
    size_t sides = config::SIDES,
    int width = config::WIDTH
  );
  void drawText(
    sf::RenderWindow& window,
    const sf::Vector2f& posc,
    const std::string& txt,
    const sf::Color& color = config::LINE_COLOR
  );
}
