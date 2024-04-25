#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace matrix {
  using row_t = std::vector<int>;
  using matrix_t = std::vector<row_t>;
  using float_row = std::vector<float>;
  using floatMatrix = std::vector<float_row>;

  matrix_t adjacencyMatrix(int size, int seed, float k);
  matrix_t toUndirected(const matrix_t& matrix);
  matrix_t weightedMatrix(const matrix_t& a, int seed);
}

std::ostream& operator<<(std::ostream& os, const matrix::matrix_t& matrix);
