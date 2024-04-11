#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace matrix {
  using row_t = std::vector<int>;
  using matrix_t = std::vector<row_t>;

  matrix_t adjacencyMatrix(int size, int seed, float k);
  matrix_t toUndirected(const matrix_t& matrix);
}

std::ostream& operator<<(std::ostream& os, const matrix::matrix_t& matrix);
