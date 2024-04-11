#include <iostream>
#include <queue>
#include <stack>
#include "matrix.hpp"
#include "graph.hpp"

using matrix::matrix_t, matrix::row_t, graph::path_t, graph::searchFn_t;

path_t graph::dfs(
  const matrix_t& matrix,
  size_t start,
  std::vector<bool>& visited,
  path_t& path
) {
  visited[start] = true;
  const size_t size{ matrix.size() };
  for (size_t i{ 0 }; i < size; i++) {
    if (!matrix[start][i] || visited[i]) continue;
    path.push_back(std::make_tuple(start, i, true));
    dfs(matrix, i, visited, path);
    path.push_back(std::make_tuple(i, start, false));
  }
  return path;
}

path_t graph::bfs(
  const matrix_t& matrix,
  size_t start,
  std::vector<bool>& visited,
  path_t& path
) {
  const size_t size{ matrix.size() };
  std::queue<size_t> q;
  visited[start] = true;
  q.push(start);
  while (!q.empty()) {
    const size_t vertex{ q.front() };
    q.pop();
    for (size_t i{ 0 }; i < size; i++) {
      if (!matrix[vertex][i] || visited[i]) continue;
      path.push_back(std::make_tuple(vertex, i, true));
      visited[i] = true;
      q.push(i);
    }
  }
  return path;
}

path_t graph::getAllPaths(const matrix_t& matrix, size_t start, const searchFn_t& search) {
  const size_t size{ matrix.size() };
  std::vector<bool> visited(size, false);
  path_t paths;
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

std::ostream& operator<<(std::ostream& os, const graph::path_t& paths) {
  for (const auto& path: paths) {
    const auto from{ std::get<0>(path) };
    const auto to{ std::get<1>(path) };
    os << from << " --> " << to << std::endl;
  }
  return os;
}