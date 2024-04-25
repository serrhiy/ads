#include <SFML/Graphics.hpp>
#include <iostream>
#include "config.hpp"
#include "utils.hpp"
#include "vertex.hpp"
#include "matrix.hpp"
#include "draw.hpp"
#include "graph.hpp"

using matrix::matrix_t;

// const matrix_t matrix{
//   {0,  10, 0,  30, 45, 0 },
//   {10, 0,  50, 0,  40, 25},
//   {0,  50, 0,  0,  35, 15},
//   {30, 0,  0,  0,  0,  20},
//   {45, 40, 35, 0,  0,  55},
//   {0,  25, 15, 20, 55, 0 },
// };

void drawGraph(sf::RenderWindow& window, const matrix_t& matrix) {
  utils::clearWindow(window, config::BACKGROUND_COLOR);
  draw::drawGraph(window, matrix, config::SIDES, config::WIDTH);
  window.display();
}

int main(int argc, const char* argv[]) {
  sf::RenderWindow window;
  utils::manageWindow(window, config::WIDTH, config::HEIGHT, config::TITLE);
  utils::clearWindow(window, config::BACKGROUND_COLOR);

  const auto directed{ matrix::adjacencyMatrix(config::VERTICES_COUNT, config::SEED, config::k) };
  const auto undirected{ matrix::toUndirected(directed) };
  const auto w{ matrix::weightedMatrix(undirected, config::SEED) };
  drawGraph(window, w);

  const auto [graph, weight]{ graph::kruskal(w) };
  std::cout << graph << std::endl;
  std::cout << weight << std::endl;

  utils::pollEvents(window);
  return 0;
}