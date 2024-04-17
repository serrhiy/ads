#pragma once

#include <vector>
#include <functional>
#include "matrix.hpp"

using matrix::matrix_t;

namespace graph {
  using dfs_item = std::pair<size_t, bool>;
  using bfs_item = std::pair<size_t, std::vector<size_t>>;
  using dfs_path = std::vector<dfs_item>;
  using bfs_path = std::vector<bfs_item>;
  template<typename T>
  using search_t = std::function<std::vector<T>(const matrix_t&, size_t, std::vector<bool>&, std::vector<T>&)>;
  dfs_path dfs(const matrix_t& matrix, size_t start, std::vector<bool>& visited, dfs_path& paths);
  bfs_path bfs(const matrix_t& matrix, size_t start, std::vector<bool>& visited, bfs_path& paths);
  template<typename T>
  std::vector<T> getAllPaths(
    const matrix_t& matrix,
    size_t start,
    search_t<T> search
  );
}

#include "graph.tcc"

std::ostream& operator<<(std::ostream& os, const graph::dfs_path& path);
std::ostream& operator<<(std::ostream& os, const graph::bfs_path& path);
