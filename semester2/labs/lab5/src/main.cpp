#include <SFML/Graphics.hpp>
#include <iostream>
#include "config.hpp"
#include "utils.hpp"
#include "vertex.hpp"
#include "matrix.hpp"
#include "draw.hpp"
#include "graph.hpp"

using namespace std::placeholders;
using utils::events_t, graph::dfs_item, graph::bfs_item;

void drawGraph(sf::RenderWindow& window, const matrix_t& matrix) {
  utils::clearWindow(window, config::BACKGROUND_COLOR);
  draw::drawGraph(window, matrix, config::SIDES, config::WIDTH);
  window.display();
}

int main(int argc, char* const argv[]) {
  sf::RenderWindow window;
  utils::manageWindow(window, config::WIDTH, config::HEIGHT, config::TITLE);
  utils::clearWindow(window, config::BACKGROUND_COLOR);

  const auto directed{ matrix::adjacencyMatrix(config::VERTICES_COUNT, config::SEED, config::k) };
  std::cout << "Adjacency Matrix:\n" << directed << std::endl;

  const auto start{ utils::getFistOutVertex(directed) };
  if (start == SIZE_MAX) {
    std::cout << "All vertices are unconnected" << std::endl;
    drawGraph(window, directed);
    utils::pollEvents(window);
    return 0;
  }

  const auto [dfs, dfsMatrix]{ graph::getAllPaths<dfs_item>(directed, start, graph::dfs) };
  const auto [bfs, bfsMatrix]{ graph::getAllPaths<bfs_item>(directed, start, graph::bfs) };

  std::cout << "DFS Matrix:\n" << dfsMatrix << std::endl;
  std::cout << "BFS Matrix:\n" << bfsMatrix << std::endl;

  std::cout << "Dfs:\n" << dfs << std::endl;
  std::cout << "Bfs:\n" << bfs << std::endl;

  std::cout << "DFS new numbering:\n";
  utils::printNewVertexNumberingDFS(dfs);
  std::cout << "BFS new numbering:\n";
  utils::printNewVertexNumberingBFS(bfs);

  const events_t myEvents{
    std::make_tuple(
      utils::onKeyDown(sf::Keyboard::Space),
      draw::drawDFSRouteClosure(directed, dfs),
      "DFS"
    ),
    std::make_tuple(
      utils::onKeyDown(sf::Keyboard::Space),
      draw::drawBFSRouteClosure(directed, bfs),
      "BFS"
    ),
  };
  utils::pollEvents(window, myEvents, std::bind(drawGraph, _1, directed));
  return 0;
}
