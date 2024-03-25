import math
import random
from config import seed
from utils import float_random, index_filter
from .operations import sum_row, sum_col

def adjacency_matrix(size, k):
  random.seed(seed)
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

def vertex_degree(matrix, i, directed):
  out = sum_row(matrix[i])
  incoming = sum_col(matrix, i) if directed else matrix[i][i]
  return out + incoming

def vertex_degrees(matrix, directed):
  result = []
  for i in range(len(matrix)):
    result.append(vertex_degree(matrix, i, directed))
  return result

vertex_degree_in = lambda matrix, i: sum_col(matrix, i)

vertex_degree_out = lambda matrix, i: sum_row(matrix[i])

vertex_degrees_in = lambda matrix: [
  sum_col(matrix, i) for i in range(len(matrix))
]

vertex_degrees_out = lambda matrix: [sum_row(row) for row in matrix]

def is_regular(degrees):
  degree = degrees[0]
  for i in range(1, len(degrees)):
    if degrees[i] != degree:
      return False
  return True

hanging_vertices = lambda degrees: index_filter(degrees, lambda x: x == 1)

isolated_vertices = lambda degrees: index_filter(degrees, lambda x: x == 0)

def exist_edge(path, v1, v2):
  for i in range(len(path) - 1):
    if path[i] == v1 and path[i + 1] == v2:
      return True
  return False

def wrap_route(matrix, start, end, length, possible, path, result):
  path.append(start)
  if length <= 1:
    if matrix[start][end] and not exist_edge(path, start, end):
      result.append((*path, end))
    return result
  for i in range(len(matrix)):
    if matrix[start][i] == 0 or exist_edge(path, start, i):
      continue
    if len(result) >= possible:
      return result
    wrap_route(matrix, i, end, length - 1, possible, path, result)
    path.pop()
  return result

def route(matrix, start, end, length, possible):
  return wrap_route(matrix, start, end, length, possible, [], [])

def routes(adjancy, matrix, length):
  result = []
  items = len(matrix)
  for i in range(items):
    for j in range(items):
      if matrix[i][j] == 0: continue
      paths = route(adjancy, i, j, length, matrix[i][j])
      result.extend(paths)
  return result
