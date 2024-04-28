#include <SFML/Graphics.hpp>
#include <iostream>
#include "config.hpp"
#include "utils.hpp"
#include "vertex.hpp"
#include "matrix.hpp"
#include "draw.hpp"
#include "graph.hpp"

using matrix::matrix_t;

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
  const auto weighted{ matrix::weightedMatrix(undirected, config::SEED) };

  drawGraph(window, weighted);

  const auto [mst, path, weight]{ graph::kruskal(weighted) };

  std::cout << "Directed:\n" << directed << std::endl;
  std::cout << "Weighted:\n" << weighted << std::endl;
  std::cout << "Minimum spanning tree:\n" << mst << std::endl;
  std::cout << "Sum of the weights of the minimum spanning tree: " << weight << std::endl;

  const auto triger{ utils::onKeyDown(sf::Keyboard::Space) };
  const auto event{ draw::skeletonClosure(weighted, path, config::SIDES, config::WIDTH) };
  utils::pollEvents(window, triger, event);
  
  return 0;
}
