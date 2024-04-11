#pragma once

#include <vector>
#include <functional>
#include "matrix.hpp"

using matrix::matrix_t;

namespace graph {
  using path_t = std::vector<std::tuple<size_t, size_t, bool>>;
  using searchFn_t = std::function<path_t(const matrix_t&, size_t, std::vector<bool>&, path_t&)>;
  path_t dfs(const matrix_t& matrix, size_t start, std::vector<bool>& visited, path_t& paths);
  path_t bfs(const matrix_t& matrix, size_t start, std::vector<bool>& visited, path_t& paths);
  path_t getAllPaths(const matrix_t& matrix, size_t start, const searchFn_t& search);
}

std::ostream& operator<<(std::ostream& os, const graph::path_t& path);