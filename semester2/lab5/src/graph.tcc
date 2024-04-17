#include <vector>
#include "graph.hpp"
#include "matrix.hpp"

using matrix::matrix_t, graph::search_t;

template<typename T>
std::vector<T> graph::getAllPaths(
  const matrix_t& matrix,
  size_t start,
  search_t<T> search
) {
  const size_t size{ matrix.size() };
  std::vector<bool> visited(size, false);
  std::vector<T> paths;
  paths.reserve(size - 1);
  bool hasUnvisited{ false };
  size_t startIndex{ start };
  do {
    hasUnvisited = false;
    search(matrix, startIndex, visited, paths);
    for (size_t i{ 0 }; i < size; i++) {
      if (visited[i]) continue;
      hasUnvisited = true;
      startIndex = i;
      break;
    }
    
  } while (hasUnvisited);
  return paths;
}