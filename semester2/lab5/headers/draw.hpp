#pragma once
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "matrix.hpp"
#include "graph.hpp"
#include "vertex.hpp"
#include <functional>
using matrix::matrix_t, graph::path_t;

namespace draw {
  void drawGraph(sf::RenderWindow& window, const matrix_t& matrix, size_t sides, int size);
  std::function<void(sf::RenderWindow&, bool)> drawRouteClosure(
    const matrix_t& matrix,
    const path_t& route,
    size_t sides = config::SIDES,
    int size = config::WIDTH
  );
}


