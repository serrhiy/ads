#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include "matrix.hpp"
#include "graph.hpp"
#include "list.hpp"

using matrix::matrix_t, matrix::row_t, graph::mst_t;

template<typename T>
void sort(List<T>& list, const std::function<bool(const T&, const T&)>& comparator) {
  for (auto head{ list.getTop() }; head != nullptr; head = head->next) {
    for (auto start{ head->next }; start != nullptr; start = start->next) {
      if (!comparator(head->value, start->value)) continue;
      std::swap(start->value, head->value);
    }
  }
}

auto sortMatrix(const matrix_t& matrix) {
  const auto size{ matrix.size() };
  List<std::tuple<size_t, size_t, int>> result{  };
  for (size_t i{ 0 }; i < size; i++) {
    for (size_t j{ 0 }; j <= i; j++) {
      const auto weight{ matrix[i][j] };
      if (weight != 0) result.push({ i, j, weight });
    }
  }
  sort<std::tuple<size_t, size_t, int>>(result, [](const auto& x, const auto& y) {
    return std::get<2>(x) > std::get<2>(y);
  });
  return result;
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
  auto node{ sortMatrix(weighted).getTop() };
  while (std::find(visited.begin(), visited.end(), false) != visited.end()) {
    const auto [row, col, min]{ node->value };
    node = node->next;  
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
