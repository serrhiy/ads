#pragma once
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "matrix.hpp"
#include "vertex.hpp"
#include "graph.hpp"
#include <functional>
using matrix::matrix_t, graph::mst_t;

namespace draw {
  void drawGraph(sf::RenderWindow& window, const matrix_t& matrix, size_t sides, int size);
  std::function<void(sf::RenderWindow&)> skeletonClosure(
    const matrix_t& matrix,
    const mst_t& path,
    size_t sides,
    int size
  );
}


