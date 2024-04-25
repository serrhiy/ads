#include <iostream>
#include <functional>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include "matrix.hpp"

using matrix::matrix_t, matrix::row_t, matrix::floatMatrix, matrix::float_row;

float random(float min, float max) {
  const auto r{ static_cast<float>(rand()) / (RAND_MAX + 1) };
  return r * (max - min) + min;
}

matrix_t matrix::adjacencyMatrix(int size, int seed, float k) {
  srand(seed);
  matrix_t result(size);
  for (size_t i{ 0 }; i < size; i++) {
    row_t row(size);
    for (size_t j{ 0 }; j < size; j++) {
      const auto value{ static_cast<int>(floor(random(0.f, 2.f) * k)) };
      row[j] = value;
    }
    result[i] = row;
  }
  return result;
}

matrix_t matrix::toUndirected(const matrix_t &matrix) {
  const auto size{ matrix.size() };
  matrix_t result(size);
  for (size_t i{ 0 }; i < size; i++) {
    row_t row(size);
    result[i] = row;
    for (size_t j{ 0 }; j < i + 1; j++) {
      result[i][j] = result[j][i] = matrix[i][j] || matrix[j][i];
    }
  }
  return result;
}

template<typename T, typename U>
std::vector<std::vector<U>> map(
  const std::vector<std::vector<T>>& matrix,
  const std::function<U(T, size_t, size_t)>& mapFn
) {
  const auto size{ matrix.size() };
  std::vector<std::vector<U>> result(size);
  for (size_t i{ 0 }; i < size; i++) {
    std::vector<U> row(size);
    for (size_t j{ 0 }; j < size; j++) {
      row[j] = mapFn(matrix[i][j], i , j);
    }
    result[i] = row;
  }
  return result;
}

std::vector<std::vector<float>> randomMatrix(size_t size) {
  std::vector<std::vector<float>> result(size);
  for (size_t i{ 0 }; i < size; i++) {
    std::vector<float> row(size);
    for (size_t j{ 0 }; j < size; j++) {
      row[j] = random(0.0f, 2.0f);
    }
    result[i] = row;
  }
  return result;
}

matrix_t matrix::weightedMatrix(const matrix_t& a, int seed) {
  const auto size{ a.size() };
  const auto b{ randomMatrix(size) };
  const auto c{ map<float, int>(b, [&a](const float& x, size_t i, size_t j) {
    return static_cast<int>(ceil(x * 100 * a[i][j]));
  }) };
  const auto d{ map<int, int>(c, [](const int& x, size_t i, size_t j) {
    return x != 0;
  }) };
  const auto h{ map<int, int>(d, [&d](const int& x, size_t i, size_t j) {
    return d[i][j] != d[j][i];
  }) };
  matrix_t upperTriangle(size);
  for (size_t i{ 0 }; i < size; i++) {
    row_t row(size);
    for (size_t j{ i }; j < size; j++) {
      row[j] = 1;
    }
    upperTriangle[i] = row;
  }
  matrix_t w(size);
  for (size_t i{ 0 }; i < size; i++) {
    w[i] = row_t(size);
    for (size_t j{ 0 }; j < i + 1; j++) {
      w[i][j] = w[j][i] = (d[i][j] + h[i][j] * upperTriangle[i][j]) * c[i][j];
    }
  }
  return w;
}

std::ostream& operator<<(std::ostream& os, const matrix_t& matrix) {
  const auto length{ matrix.size() };
  const auto indent{ std::to_string(length).length() };
  const auto width{ indent * 2 };
  os << std::setw(width) << ' ';
  for (int i = 0; i < length; ++i) {
    os << std::setw(width) << i << ' ';
  }
  os << std::endl << std::setw(width) << ' ';
  os << std::setw((width + 1) * length) << std::setfill('-') << '-';
  os << std::setfill(' ') << std::endl;
  for (int i = 0; i < length; ++i) {
    os << std::setw(indent) << i << " |";
    for (int j = 0; j < length; ++j) {
      os << std::setw(width) << matrix[i][j] << ' ';
    }
    os << std::endl;
  }
  return os;
}