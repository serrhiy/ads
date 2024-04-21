#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "config.hpp"
#include "matrix.hpp"
#include "graph.hpp"
#include "vertex.hpp"

using matrix::matrix_t, graph::dfs_path, graph::bfs_path;

namespace draw {
  void drawGraph(sf::RenderWindow& window, const matrix_t& matrix, size_t sides, int size);
  std::function<void(sf::RenderWindow&, bool)> drawDFSRouteClosure(
    const matrix_t& matrix,
    const dfs_path& route,
    size_t sides = config::SIDES,
    int size = config::WIDTH
  );
  std::function<void(sf::RenderWindow&, bool)> drawBFSRouteClosure(
    const matrix_t& matrix,
    const bfs_path& route,
    size_t sides = config::SIDES,
    int size = config::WIDTH
  );
}
