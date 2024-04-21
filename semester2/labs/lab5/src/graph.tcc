#include <vector>
#include "graph.hpp"
#include "matrix.hpp"

using matrix::matrix_t, graph::search_t;

template<typename T>
std::pair<std::vector<T>, matrix_t> graph::getAllPaths(
  const matrix_t& matrix,
  size_t start,
  search_t<T> search
) {
  const auto size{ matrix.size() };
  auto visited{ std::vector<bool>(size, false) };
  auto paths{ std::vector<T>{  } };
  paths.reserve(size - 1);
  auto traversalTree{ matrix::initMatrix(size) };
  auto hasUnvisited{ false };
  auto startIndex{ start };
  do {
    hasUnvisited = false;
    search(matrix, startIndex, visited, paths, traversalTree);
    for (size_t i{ 0 }; i < size; i++) {
      if (visited[i]) continue;
      hasUnvisited = true;
      startIndex = i;
      break;
    }
    
  } while (hasUnvisited);
  return std::make_pair(paths, traversalTree);
}