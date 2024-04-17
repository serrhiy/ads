#include <iostream>
#include <queue>
#include <stack>
#include "matrix.hpp"
#include "graph.hpp"

using matrix::matrix_t, matrix::row_t, graph::dfs_path, graph::bfs_path, graph::search_t;

dfs_path dfsRecursive(const matrix_t& matrix, size_t start, std::vector<bool>& visited, dfs_path& path) {
  visited[start] = true;
  const size_t size{ matrix.size() };
  for (size_t i{ 0 }; i < size; i++) {
    if (!matrix[start][i] || visited[i]) continue;
    path.push_back(std::make_pair(start, true));
    dfsRecursive(matrix, i, visited, path);
    path.push_back(std::make_pair(i, false));
  }
  return path;
}

dfs_path graph::dfs(const matrix_t& matrix, size_t start, std::vector<bool>& visited, dfs_path& path) {
  dfsRecursive(matrix, start, visited, path);
  path.push_back(std::make_pair(start, 0));
  return path;
}

bfs_path graph::bfs(const matrix_t& matrix, size_t start, std::vector<bool>& visited, bfs_path& path) {
  const size_t size{ matrix.size() };
  std::queue<size_t> q;
  visited[start] = true;
  q.push(start);
  while (!q.empty()) {
    const size_t vertex{ q.front() };
    q.pop();
    std::vector<size_t> neighbours;
    for (size_t i{ 0 }; i < size; i++) {
      if (!matrix[vertex][i] || visited[i]) continue;
      neighbours.push_back(i);
      visited[i] = true;
      q.push(i);
    }
    path.push_back(std::make_pair(vertex, neighbours));
  }
  return path;
}

std::ostream& operator<<(std::ostream& os, const graph::dfs_path& path) {
  const auto size{ path.size() };
  for (size_t i{ 0 }; i < size - 1; i++) {
    os << path[i].first << " --> ";
  }
  os << path[size - 1].first;
  return os;
}

std::ostream& operator<<(std::ostream& os, const graph::bfs_path& path) {
  for (const auto &[from, neighbours]: path) {
    const auto size{ neighbours.size() };
    os << from << " --> ";
    if (size >= 1) {
      for (size_t i{ 0 }; i < size - 1; i++) {
        os << neighbours[i] << ", ";
      }
      os << neighbours[size - 1];
    }
    os << std::endl;
  }
  return os;
}