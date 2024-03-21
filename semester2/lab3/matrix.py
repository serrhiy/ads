import random
import math

float_random = lambda min, max: random.random() * (max - min) + min

def print_matrix(matrix):
  width = 5
  intend = 3
  print(width * ' ', end='')
  length = len(matrix)
  for i in range(length):
    print(f'{i:> {width}}', end=' ')
  print('\n', width * ' ', end='')
  for _ in range(length):
    print('-' * (width + 1), end='')
  for i in range(length):
    print()
    print(f'{i:> {intend}}', end=' |')
    for j in range(length):
        print(f'{matrix[i][j]:> {width}}', end=' ')
  print()
  

def adjacency_matrix(size, k):
  random.seed(3112)
  matrix = []
  for _ in range(size):
    row = []
    for _ in range(size):
      val = math.floor(float_random(0, 2) * k)
      row.append(val)
    matrix.append(row)
  return matrix

def to_indirected(matrix):
  length = len(matrix)
  result = []
  for i in range(length):
    result.append([0] * length)
    for j in range(i + 1):
      value = matrix[i][j] | matrix[j][i]
      result[i][j] = value
      result[j][i] = value
  return result
