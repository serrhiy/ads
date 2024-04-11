#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "utils.hpp"
#include "vertex.hpp"
#include "matrix.hpp"
#include "draw.hpp"
#include "graph.hpp"
#include <iostream>

using namespace std::placeholders;
using utils::events_t;

void drawGraph(sf::RenderWindow& window, const matrix_t& matrix) {
  utils::clearWindow(window, config::BACKGROUND_COLOR);
  draw::drawGraph(window, matrix, config::SIDES, config::WIDTH);
  window.display();
}

int main(int argc, char* argv[]) {
  sf::RenderWindow window;
  utils::manageWindow(window, config::WIDTH, config::HEIGHT, config::TITLE);
  utils::clearWindow(window, config::BACKGROUND_COLOR);

  const auto directed{ matrix::adjacencyMatrix(config::VERTICES_COUNT, config::SEED, config::k) };
  std::cout << directed << std::endl;

  const size_t start{ utils::getFistOutVertex(directed) };
  if (start == SIZE_MAX) {
    std::cout << "All vertices are unconnected" << std::endl;
    drawGraph(window, directed);
    utils::pollEvents(window);
    return 0;
  }
  
  const auto dfs{ graph::getAllPaths(directed, start, graph::dfs) };
  const auto bfs{ graph::getAllPaths(directed, start, graph::bfs) };

  std::cout << "Dfs:\n" << dfs << std::endl;
  std::cout << "Bfs:\n" << bfs << std::endl;

  const events_t myEvents {
    std::make_tuple(
      utils::onKeyDown(sf::Keyboard::Space),
      draw::drawRouteClosure(directed, bfs),
      "BFS"
    ),
    std::make_tuple(
      utils::onKeyDown(sf::Keyboard::Space),
      draw::drawRouteClosure(directed, dfs),
      "DFS"
    )
  };
  utils::pollEvents(window, myEvents, std::bind(drawGraph, _1, directed));
  return 0;
}