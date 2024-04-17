from config import WIDTH, HEIGHT, VERTICES_COUNT, k, TITLE
from matrix import adjacency_matrix, print_matrix, to_indirected
from vertex import vertex_draw, vertex_line, vertex_arc, vertex_loop
from utils import (
  create_window,
  create_vertices,
  is_neighbors,
  in_one_line,
  split_int,
  partial,
  minmax,
)

def draw_graph(canvas, vertices, matrix, ranges, directed=True):
  length = len(vertices)
  one_line = partial(in_one_line, length, ranges)
  neighbors = partial(is_neighbors, length)
  for i in range(length):
    vertex = vertices[i]
    row = matrix[i]
    vertex_draw(canvas, vertex)
    count = length if directed else i + 1
    for j in range(count):
      if row[j] != 1: continue
      other_vertex = vertices[j]
      m, n = minmax(i, j)
      if m == n:
        vertex_loop(canvas, vertex, arrows=directed)
      elif not neighbors(m, n) and one_line(m, n):
        vertex_arc(canvas, vertex, other_vertex, arrows=directed)
      else:
        vertex_line(canvas, vertex, other_vertex, arrows=directed)

def main():
  root1, canvas1 = create_window(TITLE, WIDTH, HEIGHT)
  root2, canvas2 = create_window(TITLE, WIDTH, HEIGHT)

  ranges = split_int(VERTICES_COUNT, 4)
  vertices = create_vertices(ranges)

  adjacency = adjacency_matrix(VERTICES_COUNT, k)
  print('Directed graph: ')
  print_matrix(adjacency)
  draw_graph(canvas1, vertices, adjacency, ranges)

  print()

  matrix = to_indirected(adjacency)
  print('Indirected graph: ')
  print_matrix(matrix)
  draw_graph(canvas2, vertices, matrix, ranges, directed=False)
  
  root1.mainloop()
  root2.mainloop()

if __name__ == '__main__':
  main()
