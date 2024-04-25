#pragma once
#include <vector>
#include "matrix.hpp"

using matrix::matrix_t;

namespace graph {
  using mst_t = std::vector<std::pair<size_t, size_t>>;
  std::tuple<matrix_t, mst_t, size_t> kruskal(const matrix_t& weighted);
}
