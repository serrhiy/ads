#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <functional>
#include <string>
#include <iostream>
#include "draw.hpp"
#include "vertex.hpp"
#include "matrix.hpp"

using matrix::matrix_t;
using namespace std::placeholders;

const std::array colors{
  sf::Color(255, 154, 141), // Salmon
  sf::Color(255, 165, 0),   // Orange
  sf::Color::Yellow,        // Yellow
  sf::Color(188,169,225),  // Light Purple
  sf::Color::Green,         // Green
  sf::Color(231,236,163),   // Light Yellow
  sf::Color::Magenta,       // Magenta
  sf::Color(255, 110, 64),  // Red-orange
  sf::Color(24, 104, 174),  // Burnt sienna
  sf::Color(229, 33, 101),  // Pink
  sf::Color(157,225,154),   // Ligh Green
  sf::Color(178, 2, 56),    // Brick
  sf::Color(255, 193, 59),  // Mango
};

bool isNeighbours(size_t count, size_t i, size_t j) {
  if (i > j) std::swap(i, j);
  return i == j - 1 || (i == 0 && j == count - 1);
}

bool inOneLine(size_t count, size_t sides, size_t i, size_t j) {
  if (i > j) std::swap(i, j);
  const auto split{ static_cast<size_t>(ceil(static_cast<double>(count) / sides)) };
  const auto cnt{ count - 1 };
  const auto max{ split * sides - 1 };
  if (i == 0 && j > (max - split)) return true;
  const auto start{ i - i % split };
  const auto end{ start + split };
  return j >= start && j <= end;
}

void connectVertices(
  sf::RenderWindow& window,
  const matrix_t& matrix,
  size_t sides,
  const vertex::Vertex& from,
  const vertex::Vertex& to,
  const sf::Color& color,
  bool directed
) {
  const auto i{ from.index };
  const auto j{ to.index };
  const auto count{ matrix.size() };
  const std::string str{ std::to_string(matrix[i][j]) };
  if (i == j) vertex::loop(window, from);
  else if (!isNeighbours(count, i, j) && inOneLine(count, sides, i, j)) {
    vertex::arcConnect(window, from, to, str, directed, color);
  }
  else {
    const bool shift{ j < i && matrix[j][i] };
    vertex::lineConnect(window, from, to, str, shift, directed, color);
  }
}

void draw::drawGraph(sf::RenderWindow& window, const matrix_t& matrix, size_t sides, int size) {
  const auto count{ matrix.size() };
  const auto getVertex{ vertex::getVertexClosure(count, sides) };
  const auto connect{ 
    std::bind(connectVertices, _1, matrix, sides, _2, _3, config::LINE_COLOR, true)
  };
  for (size_t i{ 0 }; i < count; i++) {
    const auto vertex{ getVertex(i) };
    vertex::draw(window, vertex);
    for (size_t j{ 0 }; j < count; j++) {
      if (!matrix[i][j]) continue;
      const auto otherVertex{ getVertex(j) };
      connect(window, vertex, otherVertex);
    }
  }
}