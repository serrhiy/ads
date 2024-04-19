#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include "matrix.hpp"

using matrix::matrix_t, matrix::row_t;

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