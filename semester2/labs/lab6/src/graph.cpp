#include <algorithm>
#include <vector>
#include <queue>
#include "matrix.hpp"
#include "graph.hpp"

using matrix::matrix_t, matrix::row_t, graph::mst_t;

auto minEdge(const matrix_t& matrix) {
  const auto size{ matrix.size() };
  size_t min{ SIZE_MAX };
  size_t row{ SIZE_MAX };
  size_t col{ SIZE_MAX };
  for (size_t i{ 0 }; i < size; i++) {
    for (size_t j{ 0 }; j < size; j++) {
      const auto item{ matrix[i][j] };
      if (item == 0 || min <= item) continue;
      min = item;
      row = i;
      col = j;
    }
  }
  return std::make_tuple(min, row, col);
}

bool hasLoop(const matrix_t& matrix, size_t start) {
  const auto size{ matrix.size() };
  auto visited{ std::vector<bool>(size, false) };
  auto queue{ std::queue<std::pair<size_t, size_t>>{  } };
  visited[start] = true;
  queue.push({ SIZE_MAX, start });
  while (!queue.empty()) {
    const auto [from, vertex]{ queue.front() };
    queue.pop();
    for (size_t i{ 0 }; i < size; i++) {
      if (from == i) continue;
      if (matrix[vertex][i] && visited[i]) return true;
      if (!matrix[vertex][i] || visited[i]) continue;
      visited[i] = true;
      queue.push({vertex, i});
    }
  }
  return false;
}

std::tuple<matrix_t, mst_t, size_t> graph::kruskal(const matrix_t& weighted) {
  const auto size{ weighted.size() };
  matrix_t matrix{ weighted };
  mst_t path{  };
  path.reserve(size - 1);
  matrix_t graph(size);
  std::generate(graph.begin(), graph.end(), [size]() { return row_t(size); });
  std::vector<bool> visited(size, false);
  size_t weight{ 0 };
  while (std::find(visited.begin(), visited.end(), false) != visited.end()) {
    const auto [min, row, col]{ minEdge(matrix) };
    matrix[row][col] = matrix[col][row] = 0;
    visited[row] = visited[col] = true;
    graph[row][col] = graph[col][row] = min;
    if (hasLoop(graph, row) || hasLoop(graph, col)) {
      graph[row][col] = graph[col][row] = 0;
      continue;
    }
    weight += min;
    path.push_back({ row, col });
  }
  return { graph, path, weight };
}