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
  using search_t = std::function<std::pair<std::vector<T>, matrix_t>(const matrix_t&, size_t, std::vector<bool>&, std::vector<T>&, matrix_t&)>;
  std::pair<dfs_path, matrix_t> dfs(
    const matrix_t& matrix,
    size_t start,
    std::vector<bool>& visited,
    dfs_path& path,
    matrix_t& bfsMatrix
  );
  std::pair<bfs_path, matrix_t> bfs(
    const matrix_t& matrix,
    size_t start,
    std::vector<bool>& visited,
    bfs_path& paths,
    matrix_t& bfsMatrix
  );
  template<typename T>
  std::pair<std::vector<T>, matrix_t> getAllPaths(
    const matrix_t& matrix,
    size_t start,
    search_t<T> search
  );
}

#include "graph.tcc"

std::ostream& operator<<(std::ostream& os, const graph::dfs_path& path);
std::ostream& operator<<(std::ostream& os, const graph::bfs_path& path);
