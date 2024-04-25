#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include "matrix.hpp"
#include "graph.hpp"

using matrix::matrix_t, matrix::row_t;
using return_type = std::tuple<matrix_t, std::vector<std::pair<size_t, size_t>>, size_t>;

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

bool hasLoop(const matrix_t& matrix) {
  const size_t start{ 0 };
  const auto size{ matrix.size() };
  std::vector<bool> visited(size, false);
  std::stack<size_t> stack{  };
  visited[start] = true;
  stack.push(start);
  bool returns{ false };
  label: while (!stack.empty()) {
    const auto vertex{ stack.top() };
    for (size_t i{ 0 }; i < size; i++) {
      const auto connect{ matrix[vertex][i] };
      const auto visit{ visited[i] };
      if (!returns && connect && visit) return true;
      if (!connect || visit) continue;
      visited[i] = true;
      stack.push(i);
      returns = false;
      goto label;
    }
    returns = true;
    stack.pop();
  }
  return false;
}

std::pair<matrix_t, size_t> graph::kruskal(const matrix_t& weighted) {
  const auto size{ weighted.size() };
  matrix_t matrix{ weighted };
  matrix_t graph(size);
  std::generate(graph.begin(), graph.end(), [size]() { return row_t(size); });
  std::vector<bool> visited(size, false);
  size_t weight{ 0 };
  while (std::find(visited.begin(), visited.end(), false) != visited.end()) {
    const auto [min, row, col]{ minEdge(matrix) };
    matrix[row][col] = matrix[col][row] = 0;
    visited[row] = visited[col] = true;
    graph[row][col] = min;
    weight += min;
    if (!hasLoop(graph)) continue;
    graph[row][col] = 0;
    weight -= min;
  }
  return { graph, weight };
}