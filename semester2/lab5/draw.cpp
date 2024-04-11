#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <functional>
#include "draw.hpp"
#include "graph.hpp"
#include "vertex.hpp"
#include "matrix.hpp"

using matrix::matrix_t, graph::path_t;
using namespace std::placeholders;

const std::array colors{
  sf::Color(255, 154, 141), // Salmon
  sf::Color(255, 165, 0),   // Orange
  sf::Color::Yellow,        // Yellow
  sf::Color	(188,169,225),  // Light Purple
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
  const auto last{ cnt - cnt % split };
  if (i == 0 && j >= last && j < cnt) return true;
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
  if (!isNeighbours(count, i, j) && inOneLine(count, sides, i, j)) {
    vertex::arcConnect(window, from, to, directed, color);
    return;
  }
  const bool shift{ j < i && matrix[j][i] };
  vertex::lineConnect(window, from, to, shift, directed, color);
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
      if (i == j) vertex::loop(window, vertex);
      else connect(window, vertex, otherVertex);
    }
  }
}

std::function<void(sf::RenderWindow&, bool)> draw::drawRouteClosure(
  const matrix_t& matrix,
  const path_t& route,
  size_t sides,
  int size
) {
  const auto getVertex{ vertex::getVertexClosure(matrix.size(), sides, size) };
  const auto connect{ std::bind(connectVertices, _1, matrix, sides, _2, _3, _4, true) };
  const auto stepP{ std::make_shared<size_t>(0) };
  const auto routeSize{ route.size() };
  const auto drawRoute { 
    [getVertex, connect, &route](sf::RenderWindow& window, size_t step) {
      const auto colorSize{ colors.size() };
      if (step == 0) {
        const auto vertex{ getVertex(std::get<0>(route[step])) };
        vertex::draw(window, vertex, config::ACTIVE_VERTEX_COLOR);
        return;
      }
      if (step > 1) {
        const auto [i, j, needConnect]{ route[step - 2] };
        const auto from{ getVertex(i) };
        const auto to{ getVertex(j) };
        const auto color{ colors[to.index % colorSize] };
        if (needConnect) connect(window, from, to, color);
        vertex::draw(window, to, color);
      }
      if (step > route.size()) return;
      const auto [i, j, needConnect]{ route[step - 1] };
      const auto from{ getVertex(i) };
      const auto to{ getVertex(j) };
      if (step == 1) {
        vertex::draw(window, from, colors[from.index % colorSize]);
        vertex::draw(window, to, config::ACTIVE_VERTEX_COLOR);
      }
      vertex::draw(window, to, config::ACTIVE_VERTEX_COLOR);
      if (needConnect) connect(window, from, to, config::ACTIVE_VERTEX_COLOR);
    }
  };
  return [drawRoute, stepP, routeSize](sf::RenderWindow& window, bool end) {
    const auto step { *stepP };
    if (end) {
      *stepP = 0;
      return;
    }
    if (step > routeSize + 1) return;
    drawRoute(window, step);
    *stepP += 1;
    window.display();
  };
}