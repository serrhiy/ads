import csv
from utils import partial, in_one_line, is_neighbors, minmax
from vertex import (
  get_vertex_closure, vertex_draw, vertex_loop, vertex_arc, vertex_line
)

def draw_graph(canvas, matrix, sides, directed=True):
  length = len(matrix)
  one_line = partial(in_one_line, length, sides)
  neighbors = partial(is_neighbors, length)
  get_vertex = get_vertex_closure(length, sides)
  for i in range(length):
    vertex = get_vertex(i)
    row = matrix[i]
    vertex_draw(canvas, vertex)
    count = length if directed else i + 1
    for j in range(count):
      if row[j] != 1: continue
      other_vertex = get_vertex(j)
      m, n = minmax(i, j)
      if m == n:
        vertex_loop(canvas, vertex, directed)
      elif not neighbors(m, n) and one_line(m, n):
        vertex_arc(canvas, vertex, other_vertex, directed)
      else:
        shift = j < i and matrix[j][i] and directed
        vertex_line(canvas, vertex, other_vertex, shift, directed)

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

def write_routes(filename, routes):
  with open(filename, 'w') as file:
    writer = csv.writer(file, lineterminator='\n')
    writer.writerow(('start', 'end', 'path'))
    for route in routes:
      writer.writerow((route[0], route[-1], route))
