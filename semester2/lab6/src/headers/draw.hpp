#pragma once
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "matrix.hpp"
#include "vertex.hpp"
#include <functional>
using matrix::matrix_t;

namespace draw {
  void drawGraph(sf::RenderWindow& window, const matrix_t& matrix, size_t sides, int size);
}


