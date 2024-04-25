#pragma once
#include "matrix.hpp"
using matrix::matrix_t;

namespace graph {
  std::pair<matrix_t, size_t> kruskal(const matrix_t& weighted);
}
