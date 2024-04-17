#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <functional>
#include "draw.hpp"
#include "graph.hpp"
#include "vertex.hpp"
#include "matrix.hpp"

using matrix::matrix_t, graph::dfs_path, graph::bfs_path;
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

std::function<void(sf::RenderWindow&, bool)> draw::drawDFSRouteClosure(
  const matrix_t& matrix,
  const dfs_path& route,
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
      if (step == route.size()) {
        const auto i{ route[step - 1].first };
        const auto [j, needConnect]{ route[step - 2] };
        const auto from{ getVertex(j) };
        const auto to{ getVertex(i) };
        const auto active{ getVertex(i) };
        const auto color{ colors[i % colorSize] };
        if (needConnect) connect(window, from, to, color);
        vertex::draw(window, to, color);
        return; 
      }
      const auto i{ route[step].first };
      const auto active{ getVertex(i) };
      vertex::draw(window, active, config::ACTIVE_VERTEX_COLOR);
      if (step == 0) return;
      const auto [j, needConnect]{ route[step - 1] };
      const auto prevActive{ getVertex(j) };
      const auto color{ colors[j % colorSize] };
      if (needConnect) connect(window, prevActive, active, config::ACTIVE_VERTEX_COLOR);
      vertex::draw(window, prevActive, color);
      if (step >= 2) {
        const auto [k, needPrevConnect]{ route[step - 2] };
        const auto ppActive{ getVertex(k) };
        const auto color{ colors[k % colorSize] };
        if (needPrevConnect) connect(window, ppActive, prevActive, color);
      }
    }
  };
  return [drawRoute, stepP, routeSize](sf::RenderWindow& window, bool end) {
    const auto step { *stepP };
    if (end) {
      *stepP = 0;
      return;
    }
    if (step > routeSize) return;
    drawRoute(window, step);
    *stepP += 1;
    window.display();
  };
}

std::pair<size_t, size_t> getNextBFSPair(const graph::bfs_path& path, size_t step) {
  const auto size{ path.size() };
  size_t count{ 0 };
  for (size_t i{ 0 }; i < size; i++) {
    const auto [active, neighbours] { path[i] };
    const auto nsize{ neighbours.size() };
    if (step == count) return std::make_pair(active, SIZE_MAX);
    if (count < step && step <= count + nsize) {
      return std::make_pair(active, neighbours[step - count - 1]);
    }
    count += nsize + 1;
  }
  return std::make_pair(SIZE_MAX, SIZE_MAX);
}

size_t totalBFSSteps(const graph::bfs_path& path) {
  size_t count{ 0 };
  const auto size{ path.size() };
  for (size_t i{ 0 }; i < size; i++) {
    count += path[i].second.size() + 1;
  }
  return count;
}

#include <iostream>
std::function<void(sf::RenderWindow&, bool)> draw::drawBFSRouteClosure(
  const matrix_t& matrix,
  const bfs_path& route,
  size_t sides,
  int size
) {
  const auto getVertex{ vertex::getVertexClosure(matrix.size(), sides, size) };
  const auto connect{ std::bind(connectVertices, _1, matrix, sides, _2, _3, _4, true) };
  const auto stepP{ std::make_shared<size_t>(0) };
  const auto steps{ totalBFSSteps(route) };
  const auto drawRoute{
    [getVertex, connect, &route, steps](sf::RenderWindow& window, size_t step) {
      const auto colorSize{ colors.size() };
      if (step != 0) {
        const auto [active, neighbour]{ getNextBFSPair(route, step - 1) };
        const auto from{ getVertex(active) };
        const auto color{ colors[active % colorSize] };
        vertex::draw(window, from, color);
        if (neighbour != SIZE_MAX) {
          const auto to{ getVertex(neighbour) };
          connect(window, from, to, color);
        }
        if (step == steps) return;
      }
      const auto [active, neighbour]{ getNextBFSPair(route, step) };
      const auto from{ getVertex(active) };
      vertex::draw(window, from, config::ACTIVE_VERTEX_COLOR);
      if (neighbour == SIZE_MAX) return;
      const auto to{ getVertex(neighbour) };
      vertex::draw(window, to, colors[neighbour % colorSize]);
      connect(window, from, to, config::ACTIVE_VERTEX_COLOR);
    }
  };
  return [drawRoute, stepP, steps](sf::RenderWindow& window, bool end) {
    const auto step { *stepP };
    if (end) {
      *stepP = 0;
      return;
    }
    if (step > steps) return;
    drawRoute(window, step);
    *stepP += 1;
    window.display();
  };
}